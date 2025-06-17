#include "stm32f4xx.h"
#include "buzzer.h"
#include "timer.h"

static uint32_t buzzer_start = 0;
static uint32_t buzzer_active = 0;
static uint32_t buzzer_duration = 0;

void buzzer_on(int duration) {
	GPIOB->ODR |= (1 << BUZZER_PIN);
	buzzer_active = 1;
	if (duration > 0) {
		buzzer_duration = duration;
		buzzer_start = millis();
	} else {
		buzzer_duration = 0;
	}
}

void buzzer_off(void) {
	GPIOB->ODR &= ~(1 << BUZZER_PIN);
	buzzer_active = 0;
	buzzer_duration = 0;
}

void buzzer_check(void) {
	if (buzzer_active && buzzer_duration > 0) {
		if ((millis() - buzzer_start) >= buzzer_duration) {
			buzzer_off();
		}
	}
}
