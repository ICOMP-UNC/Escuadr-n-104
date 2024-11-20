# Proyecto LPC1769: Sistema de Control y Monitoreo

## Descripción
Este proyecto implementa un sistema de control y monitoreo basado en la placa **LPC1769 (Rev C)**, utilizando diversos periféricos para interactuar con el usuario, como LEDs, un potenciómetro, y una bocina. La comunicación entre el microcontrolador LPC1769 y la computadora se realiza mediante UART a través de un adaptador **PL2303**.

## Requisitos de Hardware

### Placa Base
- **LPC1769 (Rev C)**
- **Microcontrolador**: ARM Cortex-M3 a 120 MHz
- **Memoria Flash**: 512 KB
- **Memoria SRAM**: 64 KB
- **Puertos GPIO**: Para interactuar con sensores, LEDs, botones, etc.
- **Comunicación Serial (UART)**: Para la transmisión de datos hacia la computadora.

### Componentes Adicionales
- **Adaptador UART (PL2303 o similar)**: Para la comunicación entre la LPC1769 y la computadora mediante USB.
- **Sensores de Proximidad**: Sustituido por un potenciómetro que proporciona valores analógicos continuos.
- **LEDs**: Indicadores visuales para representar el estado del sistema.
- **Buzzer**: Para emitir alertas audibles.
- **Pantalla LCD (opcional)**: Para mostrar el estado del sistema (por ejemplo, valores de sensores).
- **Botones/Switches**: Para controlar modos del sistema.

### Conexiones y Cableado
- **Cable USB**: Para conectar la placa LPC1769 a la computadora.
- **Cables Jumper**: Para conectar periféricos adicionales (sensores, LEDs, buzzer).
- **Resistencias**: Para controlar la corriente en algunos periféricos.

---

## Requisitos de Software

### Herramientas Necesarias
- **MCUXpresso IDE**: Para compilar y cargar el código en la LPC1769.
- **Python 3.x**: Para ejecutar la interfaz gráfica que se comunica mediante UART.
- **Drivers de UART (PL2303)**: Para asegurar la correcta comunicación entre la LPC1769 y la computadora.
- **Visual Studio Code** (opcional): Para ejecutar el script de Python.

---

## Instalación y Configuración

### Requisitos Previos
Antes de comenzar con la compilación y programación, asegúrese de tener instalados y configurados los siguientes elementos:

1. **MCUXpresso IDE**: Para compilar y cargar el código.
2. **Python 3.x**: Para ejecutar la interfaz UART.
3. **Drivers de UART (PL2303)**: Para asegurar la comunicación.
4. **Visual Studio Code** (opcional): Para ejecutar el script de Python.

### Pasos de Instalación

#### 1. Instalación de MCUXpresso IDE
- Descargue e instale **MCUXpresso IDE** desde el [sitio oficial de NXP](https://www.nxp.com/).
- Durante la instalación, seleccione las opciones por defecto.

#### 2. Instalación de Drivers de UART
- Instale los drivers adecuados para el adaptador **PL2303**.
- Los drivers pueden descargarse desde el [sitio oficial del fabricante](http://www.prolific.com.tw/US/ShowProduct.aspx?p_id=225&pcid=41).
- Siga las instrucciones de instalación.

#### 3. Configuración del Entorno en MCUXpresso IDE
- **Importación de librerías**: Asegúrese de que las librerías necesarias para el LPC1769 estén correctamente importadas en el IDE.
- **Importar el Proyecto**: Abra MCUXpresso IDE y use la opción "Import Project" para agregar el proyecto.
- **Compilación y carga del proyecto**: Siga los pasos descritos en la sección **Compilación y Programación**.

#### 4. Comunicación UART con Python

##### 4.1. Conectar el Adaptador UART
- Conecte el adaptador **PL2303** a la LPC1769 y a la computadora.
- Asegúrese de conectar correctamente los pines **TX/RX** entre la LPC1769 y el adaptador.

##### 4.2. Verificar el Puerto COM
- En **Administrador de Dispositivos** de Windows, verifique qué puerto COM se ha asignado al adaptador UART. Este puerto será utilizado por la interfaz en Python.

##### 4.3. Instalar Drivers de UART
- Asegúrese de que los drivers del adaptador **PL2303** estén instalados correctamente y que el puerto UART sea reconocido por la computadora.

##### 4.4. Ejecutar la Interfaz en Python

- **Instalar las dependencias**: Asegúrese de tener **Python 3.x** instalado. Luego instale las dependencias necesarias ejecutando:

  ```bash
  pip install pyserial customtkinter
