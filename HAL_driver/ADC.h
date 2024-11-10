#include <avr/io.h>

#define A_REF 0
#define A_VCC 1


enum
{
ADC0 = 0,
ADC1 = 1,
ADC2 = 2,
ADC3 = 3,
ADC4 = 4,
ADC5 = 5
};

enum 
{
PRESCALER_2 = 0,
PRESCALER_4 = 1,
PRESCALER_8 = 2,
PRESCALER_16 = 3,
PRESCALER_32 = 4,
PRESCALER_64 = 5,
PRESCALER_128 = 6
};

/// @brief структура для инициализации ацп
typedef struct 
{
    int16_t ADC_PIN; // номер пина для ацп
    int16_t ADC_POWER; // режим питания ацп
    int16_t ADC_PREACALER; // делитель ацп
}ADC_INIT;

void HAL_Init_Acp(ADC_INIT *init);
uint16_t HAL_ADC_Read(void);
