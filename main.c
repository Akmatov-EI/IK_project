#include <avr/io.h>
#include <avr/interrupt.h>
#include "main.h" // подлкючение основного файла с библиотеками
#define MAXSIZE 200
#define TIMER 1
#define SIZE_Bit 8
uint32_t MainTimer = 0;
uint16_t Count = 0;

uint8_t countHIGH = 0;
uint8_t countLOW = 0;
uint8_t buffer[MAXSIZE];
GPIO_Init pin;
GPIO_Init ReadIK;
UartInit uart1;
uint8_t StartRead();
int main(void)
{
    pin.Mode = OUTPUT;
    pin.Port = GPIO_PORTD;
    pin.num_pin = GPIO_PIN_5;
    pin.Reg = GPIOD;
    HAL_InitPin(&pin);

    ReadIK.Mode = INPUT;
    ReadIK.Port = GPIO_PORTD;
    ReadIK.num_pin = GPIO_PIN_4;
    ReadIK.Reg = GPIOD;
    ReadIK.Pull = INPUT_PULLUP;
    HAL_InitPin(&ReadIK);

    uart1.BoudRate = boud_9600;
    uart1.ModeUart = TX;
    uart1.WordLength = MODE_8BIT;
    HAL_UartInit(&uart1);

    Timer0_Init();
    while (1)
    {

        if (StartRead())
        {

            for (uint16_t i = 0; i < MAXSIZE; i++)
            {
                for (uint8_t j = 0; j < SIZE_Bit; j++)
                {
                    if (HAL_GPIO_ReadPin(STATUSD, GPIO_PIN_4) == 1)
                    {
                        buffer[i] |= (1 << j);
                        // HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, RESET);
                    }
                    else
                    {
                        buffer[i] &= ~(1 << j);
                        // HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, SET);
                    }
                    //_delay_us(0.1);
                    Count++;
                    _delay_us(100);
                }
            }
        }
if(buffer[0] != 0)
{
        for (uint16_t i = 0; i < MAXSIZE; i++)
        {
            for (uint8_t x = 0; x < SIZE_Bit; x++)
            {
                if ((buffer[i] >> x) & 1)
                {
                    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, RESET);
                }
                else
                {
                    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, SET);
                }
                _delay_us(100);
            }
        }
}
        Count = 0;
    }

    return 0;
}

uint8_t StartRead()
{
    static uint8_t Start = 0;
    static uint8_t timerCount = 0;
    static uint8_t flag = 0;
    if (HAL_GPIO_ReadPin(STATUSD, GPIO_PIN_4) == 0)
    {
        Start = 1;
        flag = 1;
    }
    if (HAL_GPIO_ReadPin(STATUSD, GPIO_PIN_4) == 1 && flag == 1)
    {
        if (HAL_GetTick() - MainTimer >= 1)
        {
            timerCount++;
            MainTimer = HAL_GetTick();
        }
        if (timerCount > 50)
        {
            Start = 0;
            flag = 0;
            timerCount = 0;
        }
    }

    return Start;
}
