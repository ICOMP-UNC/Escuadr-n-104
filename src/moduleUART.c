#include "moduleUART.h"

/**
 * @brief Configura la UART.
 *
 * Inicializa la UART con los valores predeterminados para permitir
 * la comunicación serie.
 */
void conf_UART(void) {
    UART_CFG_Type UARTConfigStruct;
    UART_FIFO_CFG_Type UARTFIFOConfigStruct;

    UART_ConfigStructInit(&UARTConfigStruct); // Configuración predeterminada
    UART_Init(LPC_UART0, &UARTConfigStruct);  // Inicializar UART0

    UART_FIFOConfigStructInit(&UARTFIFOConfigStruct); // Configuración FIFO
    UART_FIFOConfig(LPC_UART0, &UARTFIFOConfigStruct);

    UART_TxCmd(LPC_UART0, ENABLE); // Habilitar transmisión
}

/**
 * @brief Envía un mensaje por UART.
 *
 * @param data Cadena de caracteres a enviar.
 */
void enviar_UART(volatile uint8_t *data) {
    UART_Send(LPC_UART0, data, strlen((const char *)data), BLOCKING); // Enviar datos
}

/**
 * @brief Envía el valor del ADC por UART.
 *
 * @param valor_adc Valor del ADC a enviar.
 */
void enviar_valor_ADC(uint16_t valor_adc) {
    char buffer[30];
    sprintf(buffer, "ADC: %u\n", valor_adc); // Formatear el mensaje
    enviar_UART((volatile uint8_t *)buffer);   // Enviar el mensaje
}

/**
 * @brief Envía el estado de los LEDs por UART.
 *
 * Informa si el sistema está en modo reversa o normal.
 */
void enviar_estado_leds(void) {
    char estado[50];
    sprintf(estado, "Modo reversa: %s\n", reverse_flag ? "Activado" : "Desactivado");
    enviar_UART((volatile uint8_t *)estado); // Enviar estado de LEDs
}

/**
 * @brief Notifica el estado del interruptor por UART.
 *
 * Indica si el interruptor está habilitado o deshabilitado.
 */
void notificar_estado_interruptor(void) {
    char mensaje[30];
    sprintf(mensaje, "Interruptor: %s\n", habilitar ? "Habilitado" : "Deshabilitado");
    enviar_UART((volatile uint8_t *)mensaje); // Enviar estado del interruptor
}

/**
 * @brief Envía el estado general del sistema por UART.
 *
 * Proporciona información sobre el modo de operación actual.
 */
void enviar_estado_sistema(void) {
    char estado[100];
    sprintf(estado, "Sistema: %s\n", reverse_flag ? "Reversa" : "Avanzando");
    enviar_UART((volatile uint8_t *)estado); // Enviar estado general
}
