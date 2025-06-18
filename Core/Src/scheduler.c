#include "scheduler.h"
#include "uart.h"
#include "timer.h"
#include <stdio.h>

static uint32_t last_sent_time = 0;

#define DELAY	1000

void scheduler_update(uint16_t ppm, GasAlertLevel level) {
    uint32_t now = millis();

    if (now - last_sent_time >= DELAY) {
        send_data(ppm, level);
        last_sent_time = now;
    }
}

void send_data(uint16_t ppm, GasAlertLevel level) {
    char buffer[64];
    sprintf(buffer, "{\"ppm\":%u,\"state\":%u}\n", ppm, (uint8_t)level);
    uart1_send_string(buffer);
}
