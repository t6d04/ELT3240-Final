#ifndef __UART_TX_SCHEDULER_H
#define __UART_TX_SCHEDULER_H

#include <stdint.h>
#include "state_machine.h"

void scheduler_update(uint16_t ppm, GasAlertLevel level);
void send_data(uint16_t ppm, GasAlertLevel level);

#endif
