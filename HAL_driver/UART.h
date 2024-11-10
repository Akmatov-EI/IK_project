#include <avr/io.h>
#define boud_9600 103
#define boud_115200 8
#define TX 0
#define RX 1
#define TXRX 2

#define MODE_8BIT 0
#define MODE_7BIT 1
#define MODE_6BIT 2

/// @brief структура для инициализации UART
typedef struct 
{
  uint16_t BoudRate; // скорость
  uint8_t ModeUart; // режим работы 
  uint8_t WordLength; //количистов бит данных
}UartInit;

void HAL_UartInit(UartInit *init);
void HAL_UART_Transmit(uint16_t number);
void UART_transmit(unsigned char data);
unsigned char HAL_UART_Receive(void);
