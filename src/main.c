#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#ifdef __USE_MCUEXPRESSO
#include <cr_section_macros.h> /* Macros específicos del toolchain MCUXpresso */
#endif

#include "lpc17xx_adc.h"
#include "lpc17xx_dac.h"
#include "lpc17xx_exti.h"
#include "lpc17xx_gpdma.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_i2c.h"
#include "lpc17xx_nvic.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_systick.h"
#include "lpc17xx_timer.h"
#include "lpc17xx_uart.h"
#include <string.h> 

#include "modulePort.h"
#include "moduleEINT.h"
#include "moduleSystick.h"
#include "moduleADC.h"
#include "moduleDAC.h"
#include "moduleUART.h"

/**
 * @brief Función principal del sistema.
 * Configura los periféricos y entra en un bucle infinito utilizando DMA y bajo consumo.
 */
int main(void)
{
    SystemInit(); /*!< Inicializa el reloj del sistema */

    configure_port(); /*!< Configura los pines de la placa */

    configure_adc(); /*!< Configura el ADC */
    configure_timer_and_match(); /*!< Configura el Timer0 y sus coincidencias */
    start_timer(); /*!< Inicia el Timer0 */

    configure_systick(); /*!< Configura el temporizador SysTick */
    SYSTICK_IntCmd(ENABLE); /*!< Habilita la interrupción de SysTick */
    SYSTICK_Cmd(ENABLE); /*!< Habilita el contador de SysTick */

    configure_external_interrupt(); /*!< Configura la interrupción externa */
    NVIC_EnableIRQ(EINT0_IRQn); /*!< Habilita la interrupción EINT0 */

    configure_dac(); /*!< Configura el DAC */
    configure_dma_for_dac(table); /*!< Configura el DMA para salida continua de onda */
    GPDMA_ChannelCmd(CHANNEL_DMA_DAC, ENABLE); /*!< Habilita el canal DMA para el DAC */

    conf_UART(); /*!< Configura la comunicación UART */

    NVIC_SetPriority(EINT0_IRQn, 0); /*!< Establece prioridad para la interrupción EINT0 */
    NVIC_SetPriority(TIMER0_IRQn, 1); /*!< Establece prioridad para la interrupción Timer0 */
    NVIC_SetPriority(ADC_IRQn, 2); /*!< Establece prioridad para la interrupción ADC */
    NVIC_SetPriority(SysTick_IRQn, 3); /*!< Establece prioridad para la interrupción SysTick */

    /**
     * @brief Bucle infinito.
     * El sistema opera utilizando DMA y entra en modo de bajo consumo
     * mientras espera interrupciones.
     */
    while (TRUE)
    {
        __WFI(); /*!< Espera por una interrupción (reduce consumo de energía) */
    }

    return 0; /*!< Nunca debería alcanzarse este punto */
}