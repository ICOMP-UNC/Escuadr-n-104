#ifndef MODULEADC_H
#define MODULEADC_H

#include "lpc17xx_adc.h"
#include "lpc17xx_nvic.h"
#include "lpc17xx_timer.h"
#include "moduleDAC.h"
#include "moduleSystick.h"
#include <stddef.h>
#include <stdint.h>

/** Constantes y definiciones relacionadas con la configuración del ADC.
 *  @{
 */
#define SECOND                     10000
#define ADC_FREQ                   100000
#define MAX_APROXIMACION_PERMITIDA 2048
#define NUM_SAMPLES                4

extern volatile uint32_t table[NUM_SAMPLES];

extern volatile uint32_t adc_read_value; ///< Último valor leído del ADC.
// extern volatile uint8_t reverse_flag;    ///< Indica el modo de operación: 1 (reversa) o 0 (normal).

/**
 * @file moduleADC.h
 * @brief Configuración y manejo del ADC para el sistema.
 *
 * Este módulo configura el ADC (Convertidor Analógico-Digital) y su interacción
 * con un temporizador para realizar lecturas periódicas.
 */

/**
 * @brief Configura el temporizador y el sistema de coincidencias para el ADC.
 *
 * Inicializa el temporizador que controla la frecuencia de muestreo del ADC.
 */
void configure_timer_and_match(void);

/**
 * @brief Inicia el temporizador del ADC.
 *
 * Activa el temporizador que genera las señales para las conversiones del ADC.
 */
void start_timer(void);

/**
 * @brief Configura el ADC del sistema.
 *
 * Inicializa el ADC con las configuraciones necesarias para realizar
 * conversiones en un canal específico.
 */
void configure_adc(void);

/**
 * @brief Manejador de la interrupción del temporizador (TIMER0).
 *
 * Inicia una conversión ADC cuando el temporizador genera una interrupción.
 */
void TIMER0_IRQHandler(void);

/**
 * @brief Manejador de la interrupción del ADC.
 *
 * Procesa los datos convertidos por el ADC y actualiza el estado del sistema.
 */
void ADC_IRQHandler(void);

/**
 * @brief Continúa el manejo del estado del sistema basado en el valor del ADC.
 *
 * Determina si el sistema debe operar en modo normal o en reversa
 * según el valor del ADC leído.
 */
void continue_reverse(void);

void swap_table(volatile uint32_t* table);

#endif // MODULEADC_H
