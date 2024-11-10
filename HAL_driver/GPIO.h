#include <avr/io.h>
#define GPIOC &DDRC
#define GPIOD &DDRD
#define GPIOB &DDRB
#define STATUSB &PINB
#define STATUSC &PINC
#define STATUSD &PIND
#define OUTPUT 11
#define INPUT 22
#define INPUT_PULLUP 13
#define SET 1
#define RESET 0
#define GPIO_PORTC &PORTC
#define GPIO_PORTB &PORTB
#define GPIO_PORTD &PORTD
enum
{
GPIO_PIN_0 = 0,
GPIO_PIN_1 = 1,
GPIO_PIN_2 = 2,
GPIO_PIN_3 = 3,
GPIO_PIN_4 = 4,
GPIO_PIN_5 = 5,
GPIO_PIN_6 = 6,
GPIO_PIN_7 = 7
};

enum
{
GPIO_REG_0 = 0,
GPIO_REG_1 = 1,
GPIO_REG_2 = 2,
GPIO_REG_3 = 3,
GPIO_REG_4 = 4,
GPIO_REG_5 = 5,
GPIO_REG_6 = 6,
GPIO_REG_7 = 7
};

/// @brief структтура для инициализации GPIO
typedef struct 
{
volatile uint8_t *Reg; // регистр DDR
volatile uint8_t *Port; // регистр PORT 
uint8_t Mode; // режим работы вход/выход
uint8_t Pull; // состояние ножки pullup
uint8_t num_pin; // номер пина
}GPIO_Init;

void HAL_GPIO_WritePin(volatile uint8_t *port, uint8_t pin, uint8_t status);
void HAL_InitPin(GPIO_Init *init);
uint8_t  HAL_GPIO_ReadPin(volatile uint8_t *port, uint8_t pin);
void HAL_GPIO_Togglepin(volatile uint8_t *port, uint8_t pin);
