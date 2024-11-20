#include "moduleDAC.h"

volatile uint32_t dac_counter = 0;
volatile uint32_t dac_value[NUM_SAMPLES] = {1000, 700, 400, 0};
volatile uint32_t dac_value1[NUM_SAMPLES] = {1000, 700, 400, 0};
volatile uint32_t dac_value2[NUM_SAMPLES] = {800, 800, 800, 800};
/**
 * @brief Configura el DAC para generar una onda periódica.
 *
 * Configura el DAC para operar en modo de contador con DMA habilitado,
 * utilizando un intervalo calculado para generar una señal de frecuencia deseada.
 */
void configure_dac(void)
{
    DAC_CONVERTER_CFG_Type DAC_Struct; /**< Estructura de configuración del DAC */
    uint32_t update_interval;          /**< Intervalo de actualización entre muestras */

    // Configuración del DAC
    DAC_Struct.DBLBUF_ENA = RESET; /**< Deshabilitar doble buffer */
    DAC_Struct.CNT_ENA = SET;      /**< Habilitar modo contador del DAC (modo timeout) */
    DAC_Struct.DMA_ENA = SET;      /**< Habilitar modo DMA del DAC */
    DAC_Init(LPC_DAC);             /**< Inicializar el DAC */

    // Calcular el intervalo de actualización para la frecuencia de la onda deseada
    update_interval = (CLOCK_DAC_MHZ * 1000000) / (WAVE_FREQUENCY * NUM_SAMPLES);
    DAC_SetDMATimeOut(LPC_DAC, update_interval); /**< Establecer el intervalo de timeout entre muestras */

    // Aplicar la configuración del DAC
    DAC_ConfigDAConverterControl(LPC_DAC, &DAC_Struct);
}

/**
 * @brief Configura el DMA para transferir datos al DAC.
 *
 * Configura el DMA para realizar transferencias continuas desde una tabla
 * de datos a través del canal del DAC, utilizando una estructura de lista
 * enlazada para transferencia continua.
 *
 * @param[in] table Puntero a la tabla de datos que contiene las muestras de la onda.
 */
void configure_dma_for_dac(volatile uint32_t* table)
{
    GPDMA_LLI_Type DMA_LLI_Struct; /**< Elemento de lista enlazada DMA para transferencia continua */

    // Configurar la lista enlazada DMA para transferencia continua
    DMA_LLI_Struct.SrcAddr = (uint32_t)table;              /**< Dirección fuente: tabla de la onda */
    DMA_LLI_Struct.DstAddr = (uint32_t) & (LPC_DAC->DACR); /**< Dirección destino: registro del DAC */
    DMA_LLI_Struct.NextLLI = (uint32_t)&DMA_LLI_Struct;    /**< Enlace al mismo elemento para transferencia continua */
    DMA_LLI_Struct.Control = DMA_SIZE                      /**< Tamaño de la transferencia */
                             | (2 << 18)                   /**< Ancho de origen: 32 bits */
                             | (2 << 21)                   /**< Ancho de destino: 32 bits */
                             | (1 << 26);                  /**< Incrementar la dirección de origen */

    // Inicializar el módulo DMA
    GPDMA_Init();

    GPDMA_Channel_CFG_Type GPDMACfg; /**< Estructura de configuración del canal DMA */

    // Configuración del canal DMA para transferencia memoria a periférico
    GPDMACfg.ChannelNum = CHANNEL_DMA_DAC;          /**< Canal 0 */
    GPDMACfg.SrcMemAddr = (uint32_t)table;          /**< Dirección fuente: tabla de la onda */
    GPDMACfg.DstMemAddr = 0;                        /**< Sin dirección destino en memoria (periférico) */
    GPDMACfg.TransferSize = DMA_SIZE;               /**< Tamaño de la transferencia: 60 muestras */
    GPDMACfg.TransferWidth = 0;                     /**< No se utiliza */
    GPDMACfg.TransferType = GPDMA_TRANSFERTYPE_M2P; /**< Transferencia memoria a periférico */
    GPDMACfg.SrcConn = 0;                           /**< Fuente es memoria */
    GPDMACfg.DstConn = GPDMA_CONN_DAC;              /**< Destino: conexión del DAC */
    GPDMACfg.DMALLI = (uint32_t)&DMA_LLI_Struct;    /**< Lista enlazada para transferencia continua */

    // Aplicar la configuración del DMA
    GPDMA_Setup(&GPDMACfg);
}
void actualizar_dac(volatile uint32_t* dac_value)
{
    dac_counter++;
    if (reverse_flag == TRUE)
    {
        dac_value = dac_value1;
    }
    else
    {
        dac_value = dac_value2;
    }
}