#include "moduleSystick.h"

/**
 * @file systick.c
 * @brief Implementación de la configuración y manejo del SysTick.
 *
 * Este archivo contiene la configuración del temporizador SysTick y el manejador
 * de interrupción que realiza tareas periódicas del sistema.
 */

// Variables globales
volatile uint32_t systick_counter = 0; ///< Contador global del SysTick
volatile uint16_t red_led_counter = MAX_RED_LED_COUNTER; ///< Contador para el cambio del LED rojo
volatile uint16_t green_led_counter = MAX_GREEN_LED_COUNTER; ///< Contador para el cambio del LED verde
volatile uint8_t toggle = MAX_TOGGLE; ///< Variable de estado de alternancia
volatile uint8_t reverse_flag = 1; ///< Bandera de modo reversa (TRUE por defecto)

/**
 * @brief Configura el temporizador SysTick.
 *
 * Configura el temporizador SysTick para generar una interrupción en un intervalo fijo definido
 * por `SYSTICK_TIME`. Habilita el temporizador y sus interrupciones.
 */
void configure_systick(void) {
  SYSTICK_InternalInit(SYSTICK_TIME); // Inicializa el SysTick con el tiempo especificado
  SYSTICK_IntCmd(ENABLE);            // Habilita las interrupciones del SysTick
  SYSTICK_Cmd(ENABLE);               // Habilita el temporizador SysTick
}

/**
 * @brief Manejador de interrupción del SysTick.
 *
 * Este manejador realiza las siguientes tareas:
 * - Cambia el estado de los LEDs según el estado de `reverse_flag`.
 * - Gestiona la transmisión periódica de datos por UART.
 * - Reinicia la bandera de interrupción del SysTick.
 */
void SysTick_Handler(void)
{
    // Alternar LEDs en función del estado de reverse_flag
    if (reverse_flag == TRUE) {
        green_led();  // LED verde para modo reversa
    } else {
        red_led();  // LED rojo para modo normal
    }

    // Incrementar el contador del SysTick
    systick_counter++;

    // Cada 1 segundo (suponiendo un SysTick cada 10 ms)
    if (systick_counter >= 100) {
        systick_counter = 0;  // Reiniciar el contador

        // Enviar información por UART
        //enviar_valor_ADC(leer_ADC());         // Enviar el valor del ADC
        enviar_estado_leds();                // Enviar el estado de los LEDs
        notificar_estado_interruptor();      // Enviar el estado del interruptor
        enviar_estado_sistema();             // Enviar el estado general del sistema
    }

    // Limpiar la bandera del SysTick
    SYSTICK_ClearCounterFlag();
}


void green_led(void)
{
    GPIO_ClearValue(PINSEL_PORT_0, RED_LED_PIN);

    if (green_led_counter > 0) {
        green_led_counter--;
    }

    if (green_led_counter == 0) {
        if (GPIO_ReadValue(PINSEL_PORT_0) & GREEN_LED_PIN) {
            GPIO_ClearValue(PINSEL_PORT_0, GREEN_LED_PIN);
        } else {
            GPIO_SetValue(PINSEL_PORT_0, GREEN_LED_PIN);
        }
        green_led_counter = MAX_GREEN_LED_COUNTER;
        actualizar_dac(dac_value[1]);
        toggle--;
    }

    if (toggle == 0) {
        toggle = MAX_TOGGLE;
    }
}

void red_led(void)
{
    GPIO_ClearValue(PINSEL_PORT_0, GREEN_LED_PIN);

    if (red_led_counter > 0) {
        red_led_counter--;
    }

    if (red_led_counter == 0) {
        if (GPIO_ReadValue(PINSEL_PORT_0) & RED_LED_PIN) {
            GPIO_ClearValue(PINSEL_PORT_0, RED_LED_PIN);
        } else {
            GPIO_SetValue(PINSEL_PORT_0, RED_LED_PIN);
        }
        red_led_counter = MAX_RED_LED_COUNTER;
        actualizar_dac(dac_value[1]);
        toggle--;
    }

    if (toggle == 0) {
        toggle = MAX_TOGGLE;
    }
}