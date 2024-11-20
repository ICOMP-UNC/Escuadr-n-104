#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#ifdef __USE_MCUEXPRESSO
#include <cr_section_macros.h> /* The cr_section_macros is specific to the MCUXpresso delivered toolchain */
#endif
#ifndef MODULE_PORT_H
#define MODULE_PORT_H

#include "lpc17xx_gpio.h"
#include "lpc17xx_pinsel.h"
#include <stdint.h>
#include <stddef.h>

#define INPUT 0
#define OUTPUT 1

#define MANUAL_MODO_PIN     ((uint32_t)(1 << 10)) /**< EINT0 en el pin 2.10, entrada - función 1 */
#define MOTION_SENSOR_PIN   ((uint32_t)(1 << 23)) /**< ADC en el pin 0.23, entrada - función 1 */

/** LEDs de asistencia para estacionamiento */
#define GREEN_LED_PIN       ((uint32_t)(1 << 4))  /**< LED verde controlado por Systick (continúe), pin 0.7, salida - función 0 */
#define RED_LED_PIN         ((uint32_t)(1 << 5))  /**< LED rojo controlado por Systick (deténgase), pin 0.8, salida - función 0 */

#define BUFFER_PIN          ((uint32_t)(1 << 26)) /**< DAC para bocina con dos tipos de pitidos, pin 0.26, salida - función 2 */

#define TX_PIN              ((uint32_t)(1 << 2))  /**< Pin de transmisión UART en 0.2, salida - función 1 */
#define RX_PIN            ((uint32_t)(1 << 3))  /**< Pin de recepción UART en 0.3, entrada - función 1 */


/**
 * @brief Configura los puertos necesarios para el funcionamiento del sistema.
 *
 * Esta función inicializa los pines utilizados en el proyecto, estableciendo
 * la dirección de cada pin (entrada o salida) y configurando las funciones
 * específicas según las necesidades del sistema, como LEDs, sensores, y
 * comunicación UART.
 *
 * @param Ninguno
 */
void configure_port(void);

#endif




