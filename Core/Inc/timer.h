#ifndef __TIMER_H
#define __TIMER_H

#include <stdint.h>

void timer_init(void);
void timer_delay_ms(uint32_t ms);
uint32_t millis(void);
void timer_reset(void);
void timer_systick_callback(void);

#endif
