#include <avr/io.h>
#include <avr/interrupt.h>
//#include "main.h"

volatile uint32_t ticks = 0;

void Timer0_Init(void) {
  // Настройка таймера 0 для генерации прерывания каждые 1 мс
  TCCR0A = (1 << WGM01);   // Установка CTC (Clear Timer on Compare Match) режима
  TCCR0B = (1 << CS01) | (1 << CS00); // Предделитель на 64
  OCR0A = 249; // Настройка OCR0A (16MHz / 64 / 1000 - 1 = 249)

  TIMSK0 |= (1 << OCIE0A); // Разрешение прерывания по совпадению OCR0A
  sei(); // Глобальное разрешение прерываний
}

uint32_t HAL_GetTick() {
  uint32_t current_ticks;
  cli(); // Отключаем прерывания для атомарного чтения переменной
  current_ticks = ticks;
  sei(); // Включаем прерывания назад
  return current_ticks;
}

ISR(TIMER0_COMPA_vect) {
  ticks++; // Увеличиваем счетчик тиков каждую миллисекунду
}

