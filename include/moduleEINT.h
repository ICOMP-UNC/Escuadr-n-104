#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#ifdef __USE_MCUEXPRESSO
#include <cr_section_macros.h> /* The cr_section_macros is specific to the MCUXpresso delivered toolchain */
#endif

#ifndef MODULE_EINT_H
#define MODULE_EINT_H

#include "lpc17xx_dac.h"
#include "lpc17xx_exti.h"
#include "lpc17xx_gpdma.h"
#include "lpc17xx_nvic.h"
#include "lpc17xx_systick.h"
#include "lpc17xx_timer.h"
#include "modulePort.h"
#include <stddef.h>
#include <stdint.h>

extern volatile uint8_t habilitar;

/**
 * @brief Configura la interrupción externa en EINT0.
 *
 * Esta función inicializa y habilita la interrupción externa (EINT0) en la
 * LPC1769, estableciendo los parámetros necesarios para activar una interrupción
 * cuando cambia el estado del pin especificado. EINT0 se usa típicamente para
 * manejar eventos externos como pulsaciones de botones.
 *
 * @param Ninguno
 */
void configure_external_interrupt(void);

/**
 * @brief Manejador de la interrupción externa para EINT0.
 *
 * Esta función maneja la interrupción EINT0 cuando se activa. Contiene el código
 * para gestionar la respuesta al evento externo asociado con EINT0. En el
 * manejador, se pueden implementar acciones como alternar un LED o iniciar un
 * proceso en respuesta a la señal externa.
 *
 * @param Ninguno
 */
void EINT0_IRQHandler(void);

#endif // MODULE_EINT_H
