#include "stm32f4xx.h"
#include "timer.h"

static volatile uint32_t system_millis = 0;
static volatile uint32_t blocking_delay = 0;

void timer_systick_callback(void) {
    system_millis++;
    if (blocking_delay > 0) blocking_delay--;
}

void timer_init(void) {
    SysTick_Config(SystemCoreClock / 1000);
}

uint32_t millis(void) {
    return system_millis;
}

void timer_delay_ms(uint32_t ms) {
    blocking_delay = ms;
    while (blocking_delay > 0);
}

void timer_reset(void) {
    system_millis = 0;
}
