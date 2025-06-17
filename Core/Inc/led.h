#ifndef __LED_H
#define __LED_H

#include <stdint.h>

#define LED_PORT GPIOC

#define LED_POWER_PIN    0
#define LED_SAFE_PIN     1
#define LED_WARNING_PIN  2
#define LED_DANGER_PIN   3

void led_on(uint8_t pin);
void led_off(uint8_t pin);
void led_toggle(uint8_t pin);
void led_on_all(void);
void led_off_all(void);

void led_blink(uint8_t pin, int interval_ms);
void led_stop_blink(uint8_t pin);
void led_check(void);

#endif
