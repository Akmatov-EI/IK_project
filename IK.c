
#include "IK.h"
#include "main.h"
// #define MAXSIZE 300

// Timers
uint32_t ArrayTimers[MAXSIZE];
uint16_t countSignal = 0;

uint8_t buffer[MAXSIZE];

// Глобальная переменная для хранения общего количества тиков
volatile uint32_t ticks_total = 0;

/**
 * @brief Обработчик прерывания переполнения Timer1
 *
 * Каждый раз, когда Timer1 достигает 0xFFFF и переполняется, этот обработчик увеличивает общий счетчик ticks_total на 65536 тиков.
 */
ISR(TIMER1_OVF_vect)
{
    ticks_total += 65536;
}

/**
 * @brief Инициализация Timer1
 *
 * Настраивает Timer1 в нормальном режиме с предделителем 1 и разрешает прерывание по переполнению.
 */
void timer1_init(void)
{
    cli(); // Отключаем глобальные прерывания во время настройки

    // Сброс регистров управления Timer1
    TCCR1A = 0;
    TCCR1B = 0;

    // Устанавливаем Timer1 в нормальный режим (WGM13:0 = 0)
    // Дополнительные настройки режима не требуются

    // Устанавливаем предделитель равным 1 (CS12:0 = 0b001)
    TCCR1B |= (1 << CS10);

    // Обнуляем счетчик Timer1
    TCNT1 = 0;

    // Разрешаем прерывание по переполнению Timer1
    TIMSK1 |= (1 << TOIE1);

    sei(); // Включаем глобальные прерывания
}

/**
 * @brief Получение текущего количества тиков
 *
 * Эта функция возвращает текущую сумму тиков Timer1, учитывая переполнения.
 * Обеспечивает атомарное чтение переменных, связанных с прерываниями.
 *
 * @return uint32_t Общее количество тиков Timer1
 */
uint32_t hal_gettick(void)
{
    uint32_t ticks;
    uint16_t tcnt1;
    uint8_t sreg;

    // Сохраняем статус регистров (SREG содержит флаги состояния)
    sreg = SREG;
    cli(); // Отключаем прерывания для атомарного чтения

    ticks = ticks_total;
    tcnt1 = TCNT1;

    // Возвращаем статус регистров
    SREG = sreg;

    // Добавляем текущее значение счетчика к общему количеству тиков
    ticks += tcnt1;

    return ticks;
}

void ReadIK(Main_IK *p)
{
    timer1_init();
    static uint8_t step_position = 0;
    static uint8_t countArray = 0;
    switch (step_position)
    {
    case START_STATUS:
        if (HAL_GPIO_ReadPin(p->y.Port, p->y.Pin) == 0)
        {
            if (hal_gettick() - ArrayTimers[countArray] >= CONSTTIME)
            {
                countSignal++;
                ArrayTimers[countArray] = hal_gettick();
            }
        }
        else
        {
            p->x.BufferIK[countArray] = countSignal;
            countArray++;
            countSignal = 0;
            step_position = STATUS_HIGH;
        }
        break;
    case STATUS_HIGH:
        if (HAL_GPIO_ReadPin(p->y.Port, p->y.Pin) == 1)
        {
            if (hal_gettick() - ArrayTimers[countArray] >= CONSTTIME)
            {
                countSignal++;
                ArrayTimers[countArray] = hal_gettick();
            }
            if (countSignal >= 9000)
            {
                countSignal = 0;
                step_position = 0;
                countArray = 0;
                return;
            }
        }
        else
        {
            p->x.BufferIK[countArray] = countSignal;
            countArray++;
            countSignal = 0;
            step_position = STATUS_LOW;
        }
        break;

    case STATUS_LOW:
        if (HAL_GPIO_ReadPin(p->y.Port, p->y.Pin) == 0)
        {
            if (hal_gettick() - ArrayTimers[countArray] >= CONSTTIME)
            {
                countSignal++;
                ArrayTimers[countArray] = hal_gettick();
            }
            if (countSignal >= 9000)
            {
                step_position = 0;
                countSignal = 0;
                countArray = 0;
                return;
            }
        }
        else
        {
            p->x.BufferIK[countArray] = countSignal;
            countArray++;
            countSignal = 0;
            step_position = STATUS_HIGH;
        }
        break;

    default:
        break;
    }
}