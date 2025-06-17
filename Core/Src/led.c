#include "stm32f4xx.h"
#include "led.h"
#include "timer.h"

typedef struct {
    uint8_t pin;
    uint8_t active;
    uint32_t last_toggle;
    uint32_t interval;
    uint8_t blinking;
} Led;

static Led leds[] = {
    {LED_POWER_PIN,   0, 0, 0, 0},
    {LED_SAFE_PIN,    0, 0, 0, 0},
    {LED_WARNING_PIN, 0, 0, 0, 0},
    {LED_DANGER_PIN,  0, 0, 0, 0},
};

#define NUM_LEDS (sizeof(leds) / sizeof(leds[0]))

void led_on(uint8_t pin) {
    for (int i = 0; i < NUM_LEDS; i++) {
        if (leds[i].pin == pin) {
            leds[i].active = 1;
            leds[i].blinking = 0;
            LED_PORT->ODR |= (1 << pin);
        }
    }
}

void led_off(uint8_t pin) {
    for (int i = 0; i < NUM_LEDS; i++) {
        if (leds[i].pin == pin) {
            leds[i].active = 0;
            leds[i].blinking = 0;
            LED_PORT->ODR &= ~(1 << pin);
        }
    }
}

void led_toggle(uint8_t pin) {
    for (int i = 0; i < NUM_LEDS; i++) {
        if (leds[i].pin == pin) {
            LED_PORT->ODR ^= (1 << pin);
        }
    }
}

void led_on_all(void) {
    for (int i = 1; i < NUM_LEDS; i++) {
        leds[i].active = 1;
        leds[i].blinking = 0;
        LED_PORT->ODR |= (1 << leds[i].pin);
    }
}

void led_off_all(void) {
    for (int i = 1; i < NUM_LEDS; i++) {
        leds[i].active = 0;
        leds[i].blinking = 0;
        LED_PORT->ODR &= ~(1 << leds[i].pin);
    }
}

void led_blink(uint8_t pin, int interval_ms) {
    for (int i = 0; i < NUM_LEDS; i++) {
        if (leds[i].pin == pin) {
            leds[i].blinking = 1;
            leds[i].interval = interval_ms;
            leds[i].last_toggle = millis();
            leds[i].active = 1;
        }
    }
}

void led_stop_blink(uint8_t pin) {
    for (int i = 0; i < NUM_LEDS; i++) {
        if (leds[i].pin == pin) {
            leds[i].blinking = 0;
            leds[i].active = 0;
            LED_PORT->ODR &= ~(1 << pin);
        }
    }
}

void led_check(void) {
    uint32_t now = millis();
    for (int i = 0; i < NUM_LEDS; i++) {
        if (leds[i].blinking && (now - leds[i].last_toggle >= leds[i].interval)) {
            LED_PORT->ODR ^= (1 << leds[i].pin);
            leds[i].last_toggle = now;
        }
    }
}
