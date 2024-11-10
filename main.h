#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "HAL_driver/GPIO.h"
#include "HAL_driver/ADC.h"
#include "HAL_driver/UART.h"
void Timer0_Init(void);
uint32_t HAL_GetTick();
ISR(TIMER0_COMPA_vect);