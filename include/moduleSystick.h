#ifndef SYSTICK_H
#define SYSTICK_H

#include "lpc17xx_dac.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_systick.h"
#include "moduleDAC.h"
#include "modulePort.h"
#include "moduleUART.h"
#include <stddef.h>
#include <stdint.h>

/**
 * @file moduleSystick.h
 * @brief Archivo de cabecera para la configuración y manejo del SysTick.
 *
 * Este módulo proporciona funcionalidades para configurar y manejar el temporizador SysTick
 * para realizar tareas periódicas, como el cambio de estado de los LEDs y el envío de datos por UART.
 */

/** Periodo del SysTick en milisegundos */
#define SYSTICK_TIME 50

/** Contadores de cambio de estado de los LEDs */
#define MAX_GREEN_LED_COUNTER 10
#define MAX_RED_LED_COUNTER   10
#define MAX_TOGGLE            1

/** Definiciones de pines GPIO */
#define GREEN_LED_PIN ((uint32_t)(1 << 4))
#define RED_LED_PIN   ((uint32_t)(1 << 5))

/** Variables globales del SysTick */
extern volatile uint32_t systick_counter;   ///< Contador global del SysTick
extern volatile uint16_t red_led_counter;   ///< Contador para el cambio del LED rojo
extern volatile uint16_t green_led_counter; ///< Contador para el cambio del LED verde
extern volatile uint8_t toggle;             ///< Variable de estado de alternancia
extern volatile uint8_t reverse_flag;       ///< Bandera de modo reversa

/**
 * @brief Configura el temporizador SysTick.
 *
 * Esta función inicializa el temporizador SysTick con el periodo especificado
 * y habilita sus interrupciones.
 */
void configure_systick(void);

/**
 * @brief Manejador de interrupción del SysTick.
 *
 * Maneja las tareas periódicas, como el cambio de estado de los LEDs y la transmisión de datos por UART.
 * Limpia la bandera de interrupción del SysTick al finalizar.
 */
// void SysTick_Handler(void);

/**
 * @brief Cambia el estado del LED verde.
 *
 * Esta función cambia el estado del LED verde, alternando entre encendido y apagado
 * en función del contador de alternancia.
 */
void green_led(void);

/**
 * @brief Cambia el estado del LED rojo.
 *
 * Esta función cambia el estado del LED rojo, alternando entre encendido y apagado
 * en función del contador de alternancia.
 */
void red_led(void);

#endif // SYSTICK_H
