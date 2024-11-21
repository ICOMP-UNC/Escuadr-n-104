#include "modulePort.h"

/**
 * @file modulePort.c
 * @brief Implementación de la configuración de pines y puertos GPIO.
 *
 * Este archivo contiene la lógica para inicializar y configurar los pines
 * y puertos GPIO del sistema. Se configura la funcionalidad de los pines
 * para diversos periféricos como interrupciones externas, LEDs, UART, ADC y DAC.
 */

/**
 * @brief Configura los pines del sistema.
 *
 * Realiza la configuración de los pines GPIO necesarios para diversos
 * periféricos, incluyendo:
 * - Interruptor externo (EINT0)
 * - LEDs (verde y rojo)
 * - UART (TX y RX)
 * - ADC (Entrada de Conversión Analógica a Digital)
 * - DAC (Conversión Digital a Analógica)
 *
 * Configura los pines con las funciones correspondientes, así como los modos
 * de resistencia (pull-up, pull-down, etc.) y las direcciones de entrada/salida.
 */
void configure_port(void)
{
    PINSEL_CFG_Type pin_cfg;

    // Configuración del pin para EINT0 (Interrupción externa 0)
    pin_cfg.Portnum = PINSEL_PORT_2;           /**< Puerto donde se configura el pin */
    pin_cfg.Pinnum = PINSEL_PIN_10;            /**< Pin específico para EINT0 */
    pin_cfg.Funcnum = PINSEL_FUNC_1;           /**< Función alternativa 1 para EINT0 */
    pin_cfg.Pinmode = PINSEL_PINMODE_PULLDOWN; /**< Resistencia pull-down */
    pin_cfg.OpenDrain = PINSEL_PINMODE_NORMAL; /**< Modo normal */
    PINSEL_ConfigPin(&pin_cfg);                /**< Configura el pin según la configuración proporcionada */

    // Configuración de los pines para LEDs (verde y rojo)
    pin_cfg.Portnum = PINSEL_PORT_0;           /**< Puerto de los LEDs */
    pin_cfg.Pinnum = PINSEL_PIN_4;             /**< Pin para el LED verde */
    pin_cfg.Funcnum = PINSEL_FUNC_0;           /**< Función GPIO */
    pin_cfg.Pinmode = PINSEL_PINMODE_PULLDOWN; /**< Resistencia pull-down */
    pin_cfg.OpenDrain = PINSEL_PINMODE_NORMAL; /**< Modo normal */
    PINSEL_ConfigPin(&pin_cfg);                /**< Configura el pin para el LED verde */

    pin_cfg.Pinnum = PINSEL_PIN_5; /**< Pin para el LED rojo */
    PINSEL_ConfigPin(&pin_cfg);    /**< Configura el pin para el LED rojo */

    GPIO_SetDir(PINSEL_PORT_0, GREEN_LED_PIN, OUTPUT); /**< Configura el pin del LED verde como salida */
    GPIO_SetDir(PINSEL_PORT_0, RED_LED_PIN, OUTPUT);   /**< Configura el pin del LED rojo como salida */

    // Configuración del pin UART0 TX (P0.2)
    pin_cfg.Pinnum = PINSEL_PIN_2;             /**< Pin para UART TX */
    pin_cfg.Funcnum = PINSEL_FUNC_1;           /**< Función UART TX */
    pin_cfg.Pinmode = PINSEL_PINMODE_TRISTATE; /**< Modo tristate */
    pin_cfg.OpenDrain = PINSEL_PINMODE_NORMAL; /**< Modo normal */
    PINSEL_ConfigPin(&pin_cfg);                /**< Configura el pin para UART TX */

    // Configuración del pin UART0 RX (P0.3)
    pin_cfg.Pinnum = PINSEL_PIN_3;   /**< Pin para UART RX */
    pin_cfg.Funcnum = PINSEL_FUNC_1; /**< Función UART RX */
    PINSEL_ConfigPin(&pin_cfg);      /**< Configura el pin para UART RX */

    // Configuración del pin ADC (P0.23)
    pin_cfg.Pinnum = PINSEL_PIN_23;            /**< Pin para ADC */
    pin_cfg.Funcnum = PINSEL_FUNC_1;           /**< Función ADC */
    pin_cfg.Pinmode = PINSEL_PINMODE_TRISTATE; /**< Modo tristate */
    PINSEL_ConfigPin(&pin_cfg);                /**< Configura el pin para ADC */

    // Configuración del pin DAC (P0.26)
    pin_cfg.Pinnum = PINSEL_PIN_26;  /**< Pin para DAC */
    pin_cfg.Funcnum = PINSEL_FUNC_2; /**< Función DAC */
    PINSEL_ConfigPin(&pin_cfg);      /**< Configura el pin para DAC */
}
