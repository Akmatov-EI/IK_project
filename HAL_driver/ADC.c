#include "ADC.h"
/// @brief функция для инициализации АЦП
/// @param init указательна структуру ADC_INIT
void HAL_Init_Acp(ADC_INIT *init)
{
ADCSRA |= (1<<ADEN); // включение ацп
// выбор режима питания ацп
if (init->ADC_POWER == A_REF) 
{
    ADMUX&=~(1<<REFS0);//стандартное состояние
}
else if (init->ADC_POWER == A_VCC)
{
    ADMUX|=(1<<REFS0);
}

uint8_t step = init->ADC_PIN;  // выбор пина для ацп
uint8_t step_precaler = init->ADC_PREACALER; // делитель для ацп
switch (step)
{
 case ADC0:
            ADMUX &= ~((1 << MUX0) | (1 << MUX2) | (1 << MUX1));
            break;
        case ADC1:
            ADMUX = (ADMUX & ~((1 << MUX2) | (1 << MUX1))) | (1 << MUX0);
            break;
        case ADC2:
            ADMUX = (ADMUX & ~((1 << MUX2) | (1 << MUX0))) | (1 << MUX1);
            break;
        case ADC3:
            ADMUX = (ADMUX & ~(1 << MUX2)) | (1 << MUX0) | (1 << MUX1);
            break;
        case ADC4:
            ADMUX = (ADMUX & ~((1 << MUX1) | (1 << MUX0))) | (1 << MUX2);
            break;
        case ADC5:
            ADMUX = (ADMUX & ~(1 << MUX1)) | (1 << MUX0) | (1 << MUX2);
            break;
        default:
            // Обработка ошибок или дефолтное поведение
            break;
}

ADCSRA &= ~((1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0)); // Сброс прескалера
    switch (step_precaler) {
        case PRESCALER_2:
            ADCSRA |= (1 << ADPS0);
            break;
        case PRESCALER_4:
            ADCSRA |= (1 << ADPS1);
            break;
        case PRESCALER_8:
            ADCSRA |= (1 << ADPS0) | (1 << ADPS1);
            break;
        case PRESCALER_16:
            ADCSRA |= (1 << ADPS2);
            break;
        case PRESCALER_32:
            ADCSRA |= (1 << ADPS0) | (1 << ADPS2);
            break;
        case PRESCALER_64:
            ADCSRA |= (1 << ADPS2) | (1 << ADPS1);
            break;
        case PRESCALER_128:
            ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);
            break;
        default:
            // Обработка ошибок или дефолтное поведение
            break;
    }
}

/// @brief функция для чтения значения с ацп
/// @param  
/// @return возвращает значение с ацп
uint16_t HAL_ADC_Read(void) {
    // Запустить преобразование
    ADCSRA |= (1<<ADSC);
    // Ожидать завершения преобразования
    while (ADCSRA & (1<<ADSC));
    return ADC;
}