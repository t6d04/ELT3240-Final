#include "stm32f4xx.h"
#include "relay.h"

#define RELAY_PORT GPIOB
#define RELAY_PIN  12

static uint8_t relay_state = 0;

void relay_on(void) {
    RELAY_PORT->ODR |= (1 << RELAY_PIN);
    relay_state = 1;
}

void relay_off(void) {
    RELAY_PORT->ODR &= ~(1 << RELAY_PIN);
    relay_state = 0;
}

uint8_t relay_status(void) {
    return relay_state;
}
