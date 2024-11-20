#include "moduleEINT.h"

/**
 * @file moduleEINT.c
 * @brief Implementación de la configuración y manejo de interrupciones externas.
 *
 * Este archivo contiene las funciones necesarias para inicializar y manejar
 * la interrupción externa EINT0.
 */

// Variables globales para habilitación y control del sistema
volatile uint8_t habilitar = 1; ///< Indica si el sistema está habilitado (1) o deshabilitado (0).

/**
 * @brief Configura la interrupción externa EINT0.
 *
 * Esta función inicializa la interrupción externa EINT0, configurándola para que se dispare
 * en el flanco de bajada o cuando esté activa en bajo.
 */
void configure_external_interrupt(void)
{
    EXTI_InitTypeDef exti_cfg; /**< Estructura de configuración para la interrupción externa */
    exti_cfg.EXTI_Line = EXTI_EINT0; /**< Línea de interrupción externa EINT0 */
    exti_cfg.EXTI_Mode = EXTI_MODE_EDGE_SENSITIVE; /**< Modo de sensibilidad por flanco */
    exti_cfg.EXTI_polarity = EXTI_POLARITY_HIGH_ACTIVE_OR_RISING_EDGE; /**< Polaridad flanco de subida */
    EXTI_Config(&exti_cfg); /**< Configura la interrupción externa con los parámetros especificados */

    // Habilitar la interrupción en el NVIC
    NVIC_EnableIRQ(EINT0_IRQn);
}

/**
 * @brief Manejador de la interrupción externa EINT0.
 *
 * Alterna entre habilitar y deshabilitar el sistema al activarse la interrupción.
 * También controla el estado de los LEDs y del DAC.
 */

void EINT0_IRQHandler(void)
{
    EXTI_ClearEXTIFlag(EXTI_EINT0);
    if(habilitar == TRUE)
    {
        habilitar = FALSE;
        SYSTICK_IntCmd(DISABLE);
        GPIO_ClearValue(PINSEL_PORT_0, GREEN_LED_PIN);
        GPIO_ClearValue(PINSEL_PORT_0, RED_LED_PIN);
        DAC_UpdateValue(LPC_DAC, 0);
    } else {
        habilitar = TRUE;
        SYSTICK_IntCmd(ENABLE);
    }
}