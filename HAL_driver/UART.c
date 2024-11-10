#include "UART.h"

/// @brief Функция инициализаци UART
/// @param init указываются данные с структуры UartInit
void HAL_UartInit(UartInit *init)
{
    uint16_t ubrr_value = init->BoudRate; // скорость пердачи данных 
    UBRR0H = (uint8_t)(ubrr_value >> 8);
    UBRR0L = (uint8_t)(ubrr_value);
    if (init->ModeUart==TX) //  проверка условия на режим работы TX
    {
        UCSR0B = (1<<TXEN0);
    }
    else if (init->ModeUart==RX) //  проверка условия на режим работы TX
    {
        UCSR0B = (1<<RXEN0);
    }
    else if (init->ModeUart==TXRX) //  проверка условия на режим работы TX
    {
        UCSR0B = (1<<RXEN0) | (1<<TXEN0);
    }
    
    if (init->WordLength == MODE_8BIT) // установка 8 бит данных
    {
        UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);
    }
    else if (init->WordLength == MODE_7BIT) // установка 8 бит данных
    {
        UCSR0C = (1<<UCSZ01);
    }
    else if (init->WordLength == MODE_6BIT) // установка 8 бит данных
    {
        UCSR0C = (1<<UCSZ00);
    }
    
     
}

void UART_transmit(unsigned char data) {
    // Ожидать очистки регистра передачи
    while (!( UCSR0A & (1<<UDRE0)));
    // Поместить данные в буфер, отправка начнется автоматически
    UDR0 = data;
}

/// @brief функция для отправки данных по uart
/// @param number число которое нужно отправить по UART
void HAL_UART_Transmit(uint16_t number) {
    // Преобразовать число в строку и отправить по UART
    char buffer[5];
    itoa(number, buffer, 10);
    for (int i = 0; buffer[i] != '\0'; i++) {
        UART_transmit(buffer[i]);
    }
}

/// @brief фуекция для чтения данных по UART 
/// @param  
/// @return возвращает данные по UART
unsigned char HAL_UART_Receive(void) {
    // Ожидание, пока не появится данные в регистре приемника
    while (!(UCSR0A & (1<<RXC0)));
    // Чтение и возврат данных из буфера приемника
    return UDR0;
}