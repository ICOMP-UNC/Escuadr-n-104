#ifndef MODULEADC_H
#define MODULEADC_H

#include "lpc17xx_adc.h"
#include "lpc17xx_nvic.h"
#include "lpc17xx_timer.h"
#include "moduleDAC.h"
#include "moduleSystick.h"
#include <stddef.h>
#include <stdint.h>

/**
 * @file moduleADC.h
 * @brief Configuración y manejo del ADC para el sistema.
 *
 * Este módulo configura el ADC (Convertidor Analógico-Digital) y su interacción
 * con un temporizador para realizar lecturas periódicas.
 */

/**
 * @defgroup ADC_Constants Constantes del módulo ADC
 * @brief Constantes y definiciones relacionadas con la configuración del ADC.
 * @{
 */
#define SECOND                     10000  ///< Número de ciclos para un segundo en el temporizador.
#define ADC_FREQ                   100000 ///< Frecuencia de muestreo del ADC en Hz.
#define MAX_APROXIMACION_PERMITIDA 2048   ///< Valor máximo permitido en el ADC para la lógica del sistema.
#define NUM_SAMPLES                4      ///< Número de muestras utilizadas en la tabla.
/** @} */                                 // End of ADC_Constants

/// Tabla de valores utilizada en el procesamiento del sistema.
extern volatile uint32_t table[NUM_SAMPLES];

/// Último valor leído del ADC.
extern volatile uint32_t adc_read_value;

// extern volatile uint8_t reverse_flag; ///< Indica el modo de operación: 1 (reversa) o 0 (normal).

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

/**
 * @brief Actualiza los valores en la tabla según el modo de operación.
 *
 * Esta función modifica los valores de la tabla `table` en función de la bandera global `reverse_flag`.
 * Si `reverse_flag` está activa, la tabla se invierte; de lo contrario, permanece sin cambios.
 *
 * @param table Puntero a un arreglo de 32 bits que se actualizará.
 *              Este puntero debe apuntar a una tabla válida previamente inicializada.
 *
 * @note La función no verifica el tamaño de la tabla ni la validez del puntero,
 *       por lo que es responsabilidad del usuario garantizar que estos sean correctos.
 */
void swap_table(volatile uint32_t* table);

#endif // MODULEADC_H
