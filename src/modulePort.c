#include "modulePort.h"

/**
 * @file moduleport.c
 * @brief Implementación de la configuración de pines y puertos GPIO.
 *
 * Este archivo contiene la lógica para inicializar y configurar los pines
 * y puertos GPIO del sistema.
 */

/**
 * @brief Configura los pines del sistema.
 *
 * Realiza la configuración de los pines GPIO necesarios para:
 * - Interruptor externo (EINT0)
 * - LEDs (verde y rojo)
 * - UART (TX y RX)
 * - Otros periféricos como el DAC y ADC.
 */
void configure_port(void) {
    PINSEL_CFG_Type pin_cfg;

    // Configuración del pin para EINT0 (Interrupción externa 0)
    pin_cfg.Portnum = PINSEL_PORT_2;
    pin_cfg.Pinnum = PINSEL_PIN_10;
    pin_cfg.Funcnum = PINSEL_FUNC_1; // Función alternativa 1 para EINT0
    pin_cfg.Pinmode = PINSEL_PINMODE_PULLDOWN; // Resistencia pull-down
    pin_cfg.OpenDrain = PINSEL_PINMODE_NORMAL;
    PINSEL_ConfigPin(&pin_cfg);

    // Configuración de los pines para LEDs (verde y rojo)
    pin_cfg.Portnum = PINSEL_PORT_0;
    pin_cfg.Pinnum = PINSEL_PIN_4; // LED verde
    pin_cfg.Funcnum = PINSEL_FUNC_0; // Función GPIO
    pin_cfg.Pinmode = PINSEL_PINMODE_PULLDOWN; // Resistencia pull-down
    pin_cfg.OpenDrain = PINSEL_PINMODE_NORMAL;
    PINSEL_ConfigPin(&pin_cfg);

    pin_cfg.Pinnum = PINSEL_PIN_5; // LED rojo
    PINSEL_ConfigPin(&pin_cfg);

    GPIO_SetDir(PINSEL_PORT_0, GREEN_LED_PIN, OUTPUT);
    GPIO_SetDir(PINSEL_PORT_0, RED_LED_PIN, OUTPUT);

    // Configuración del pin UART0 TX (P0.2)
    pin_cfg.Pinnum = PINSEL_PIN_2;
    pin_cfg.Funcnum = PINSEL_FUNC_1; // UART TX
    pin_cfg.Pinmode = PINSEL_PINMODE_TRISTATE;
    pin_cfg.OpenDrain = PINSEL_PINMODE_NORMAL;
    PINSEL_ConfigPin(&pin_cfg);

    // Configuración del pin UART0 RX (P0.3)
    pin_cfg.Pinnum = PINSEL_PIN_3;
    pin_cfg.Funcnum = PINSEL_FUNC_1; // UART RX
    PINSEL_ConfigPin(&pin_cfg);

    // Configuración del pin ADC (P0.23)
    pin_cfg.Pinnum = PINSEL_PIN_23;
    pin_cfg.Funcnum = PINSEL_FUNC_1; // ADC
    pin_cfg.Pinmode = PINSEL_PINMODE_TRISTATE;
    PINSEL_ConfigPin(&pin_cfg);

    // Configuración del pin DAC (P0.26)
    pin_cfg.Pinnum = PINSEL_PIN_26;
    pin_cfg.Funcnum = PINSEL_FUNC_2; // DAC
    PINSEL_ConfigPin(&pin_cfg);
}

