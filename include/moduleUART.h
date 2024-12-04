#ifndef MODULEUART_H
#define MODULEUART_H

#include "lpc17xx_uart.h"
#include "moduleEINT.h"
#include "moduleSystick.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/**
 * @file moduleUART.h
 * @brief Configuración y funciones para la comunicación UART.
 *
 * Este módulo permite configurar y manejar la comunicación UART, así como
 * enviar datos y notificaciones específicas del sistema.
 */

/**
 * @brief Configura la UART.
 *
 * Inicializa la UART con la configuración predeterminada.
 */
void conf_UART(void);

/**
 * @brief Envía un mensaje por UART.
 *
 * @param data Cadena de caracteres a enviar.
 */
void enviar_UART(volatile uint8_t* data);

/**
 * @brief Envía el valor del ADC por UART.
 *
 * @param valor_adc Valor del ADC a enviar.
 */
void enviar_valor_ADC(uint16_t valor_adc);

/**
 * @brief Envía el estado de los LEDs por UART.
 *
 * Informa si el sistema está en modo reversa o normal.
 */
void enviar_estado_leds(void);

/**
 * @brief Notifica el estado del interruptor por UART.
 *
 * Indica si el interruptor está habilitado o deshabilitado.
 */
void notificar_estado_interruptor(void);

/**
 * @brief Envía el estado general del sistema por UART.
 *
 * Proporciona información sobre el modo de operación actual.
 */
void enviar_estado_sistema(void);

#endif // MODULEUART_H
