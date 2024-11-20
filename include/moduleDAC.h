#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#ifdef __USE_MCUEXPRESSO
#include <cr_section_macros.h> /**< Macros específicos de la herramienta MCUXpresso */
#endif

#include <stdint.h>
#include <stddef.h>

#ifndef MODULE_DAC_H
#define MODULE_DAC_H

#include "lpc17xx_dac.h"   /**< Librería de control para el DAC */
#include "lpc17xx_gpdma.h" /**< Librería de control para el DMA */
#include "moduleSystick.h"
/** @defgroup Configuración del DAC y DMA 
 *  Constantes y definiciones relacionadas con la configuración del DAC y DMA.
 *  @{
 */
#define DMA_SIZE         60 /**< Tamaño de la transferencia DMA en muestras */
#define NUM_SAMPLES      4  /**< Total de muestras para la onda completa */
#define WAVE_FREQUENCY   60 /**< Frecuencia de la onda senoidal: 60 Hz */
#define CLOCK_DAC_MHZ    25 /**< Frecuencia del reloj del DAC: 25 MHz (CCLK dividido por 4) */

extern volatile uint32_t dac_value[NUM_SAMPLES];
extern volatile uint32_t dac_value1[NUM_SAMPLES];
extern volatile uint32_t dac_value2[NUM_SAMPLES];
extern volatile uint32_t dac_counter;

#define CHANNEL_DMA_DAC  0  /**< Canal DMA usado para el DAC */
/** @} */

/**
 * @brief Configura el DAC para generar una onda periódica.
 *
 * Inicializa el DAC y establece su intervalo de actualización basado en la frecuencia de la onda deseada.
 */
void configure_dac(void);

/**
 * @brief Configura el DMA para transferir datos al DAC.
 *
 * Configura el DMA para realizar transferencias continuas desde una tabla
 * de datos que contiene muestras de la onda hacia el registro del DAC.
 *
 * @param[in] table Puntero a la tabla de muestras de la onda.
 */
void configure_dma_for_dac(volatile uint32_t *table);

void actualizar_dac(volatile uint32_t *dac_value);

#endif /* MODULE_DAC_H */