#include "moduleADC.h"

/// Tabla de valores iniciales para el procesamiento de datos.
volatile uint32_t table[NUM_SAMPLES] = {1000, 700, 400, 0};

/// Último valor leído del ADC.
volatile uint32_t adc_read_value = 0;

/**
 * @brief Configura el temporizador y su coincidencia (match).
 *
 * Esta función inicializa el temporizador TIMER0 con un prescaler de 100 µs
 * y configura el registro de coincidencia para generar una interrupción cada
 * 60 segundos.
 */
void configure_timer_and_match(void)
{
    TIM_TIMERCFG_Type timer_cfg_struct; /**< Estructura para almacenar la configuración del temporizador. */

    timer_cfg_struct.PrescaleOption = TIM_PRESCALE_USVAL; /**< Prescaler en microsegundos. */
    timer_cfg_struct.PrescaleValue = 100;                 /**< Valor del prescaler, resolución de tiempo ~1.01 µs. */

    TIM_Init(LPC_TIM0, TIM_TIMER_MODE, &timer_cfg_struct); /**< Inicializa el temporizador TIMER0. */

    TIM_MATCHCFG_Type match_cfg_struct; /**< Estructura para almacenar la configuración de la coincidencia (match). */

    match_cfg_struct.MatchChannel = 0;                          /**< Canal de coincidencia 0. */
    match_cfg_struct.IntOnMatch = ENABLE;                       /**< Habilita la interrupción en coincidencia. */
    match_cfg_struct.StopOnMatch = DISABLE;                     /**< No detiene el temporizador en coincidencia. */
    match_cfg_struct.ResetOnMatch = ENABLE;                     /**< Reinicia el temporizador en coincidencia. */
    match_cfg_struct.ExtMatchOutputType = TIM_EXTMATCH_NOTHING; /**< Sin salida de coincidencia externa. */
    match_cfg_struct.MatchValue = (uint32_t)(SECOND);           /**< Valor de coincidencia para 60 segundos. */

    TIM_ConfigMatch(LPC_TIM0, &match_cfg_struct); /**< Configura la coincidencia. */
}

/**
 * @brief Inicia el temporizador.
 *
 * Activa el temporizador TIMER0 y habilita su interrupción.
 */
void start_timer(void)
{
    TIM_Cmd(LPC_TIM0, ENABLE);   /**< Habilita el temporizador. */
    NVIC_EnableIRQ(TIMER0_IRQn); /**< Habilita la interrupción para TIMER0. */
}

/**
 * @brief Configura el ADC para realizar conversiones periódicas.
 *
 * Inicializa el ADC con una frecuencia de muestreo de 100 kHz y habilita el
 * canal 0 del ADC con interrupción.
 */
void configure_adc(void)
{
    ADC_Init(LPC_ADC, ADC_FREQ);                    /**< Frecuencia de 100 kHz. */
    ADC_ChannelCmd(LPC_ADC, ADC_CHANNEL_0, ENABLE); /**< Activar canal 0. */
    ADC_BurstCmd(LPC_ADC, DISABLE);                 /**< Desactivar modo ráfaga. */
    ADC_IntConfig(LPC_ADC, ADC_CHANNEL_0, ENABLE);  /**< Interrupción en canal 0. */
    NVIC_EnableIRQ(ADC_IRQn);                       /**< Habilitar interrupción del ADC. */
}

/**
 * @brief Manejador de interrupciones para TIMER0.
 *
 * Esta función se ejecuta cuando se produce una interrupción en TIMER0.
 * Limpia el flag de interrupción y comienza una conversión en el ADC.
 */
void TIMER0_IRQHandler(void)
{
    TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT); /**< Limpia el flag de interrupción. */
    ADC_StartCmd(LPC_ADC, ADC_START_NOW);       /**< Inicia la conversión del ADC. */
}

/**
 * @brief Manejador de interrupciones para el ADC.
 *
 * Esta función se ejecuta cuando se completa una conversión en el ADC.
 * Lee el valor de la conversión y llama a la función @ref continue_reverse.
 */
void ADC_IRQHandler(void)
{
    NVIC_DisableIRQ(ADC_IRQn); /**< Deshabilita la interrupción del ADC temporalmente. */
    adc_read_value = ADC_ChannelGetData(LPC_ADC, ADC_CHANNEL_0); /**< Lee el valor de la conversión del ADC. */
    continue_reverse();
    swap_table(table);
    NVIC_EnableIRQ(ADC_IRQn); /**< Habilita la interrupción del ADC nuevamente. */
}

/**
 * @brief Controla la bandera para la inversión.
 *
 * Esta función evalúa el valor de `adc_read_value` y ajusta `reverse_flag`
 * en función de si cumple con los límites permitidos.
 */
void continue_reverse(void)
{
    if (adc_read_value < MAX_APROXIMACION_PERMITIDA)
    {
        reverse_flag = TRUE;
    }
    else
    {
        reverse_flag = FALSE;
    }
}

/**
 * @brief Actualiza los valores en la tabla dependiendo del modo de operación.
 *
 * Reconfigura la tabla `table` basada en el valor de la bandera `reverse_flag`.
 * Si está activa, modifica los valores de la tabla para reflejar el modo inverso.
 *
 */
void swap_table(volatile uint32_t* table)
{
    for (uint32_t i = 0; i < NUM_SAMPLES / 2; i++)
    {
        table[i] = 1;
    }
    for (uint32_t i = NUM_SAMPLES / 2; i < NUM_SAMPLES; i++)
    {
        if (reverse_flag)
        {
            table[i] = 0;
        }
        else
        {
            table[i] = 1;
        }
    }
}
