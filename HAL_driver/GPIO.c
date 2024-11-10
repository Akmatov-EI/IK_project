#include "GPIO.h"

/// @brief функция для инициализации GPIO
/// @param init указатель на структуру GPIO_Init
void HAL_InitPin(GPIO_Init *init)
{
    // проверка условия на режим работы пина
    if(init->Mode==OUTPUT) 
    {
        *init->Reg |=(1 << init->num_pin);
    }
    else if(init->Mode==INPUT)
    {
        *init->Reg &=~(1 << init->num_pin);
        //*init->Port&=~(1<<init->num_pin);
    }
    else if(init->Mode==INPUT_PULLUP)
    {
        *init->Reg &=~(1 << init->num_pin);
        *init->Port|=(1<<init->num_pin);
    }
    
}

/// @brief Функция для установки пина в высокое/низкое состояние
/// @param port указывается порт пина
/// @param pin указывается номер пина
/// @param status указывается состояние пина
void HAL_GPIO_WritePin(volatile uint8_t *port, uint8_t pin, uint8_t status)
{
    if(status == SET)
    {
        *port |= (1<<pin);
    }
    else if(status == RESET)
    {
        *port &= ~(1<<pin);
    }
    //return port;
}

void HAL_GPIO_Togglepin(volatile uint8_t *port, uint8_t pin)
{
*port ^= (1<<pin);
}

/// @brief функция для чтения данных с пина
/// @param port указывается порт пина
/// @param pin указывается номер пина
/// @return возвращает сосотояние пина
uint8_t HAL_GPIO_ReadPin(volatile uint8_t *port, uint8_t pin)
{
    //*port|=(1<<pin);
uint8_t status_pin = (*port & (1<<pin))?1:0;
return status_pin;
}