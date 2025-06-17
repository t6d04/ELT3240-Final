#ifndef __STATE_MACHINE_H
#define __STATE_MACHINE_H

#include <stdint.h>

typedef enum {
    SYSTEM_STOPPED = 0,
    SYSTEM_RUNNING = 1
} SystemState;

typedef enum {
    GAS_SAFE = 0,
    GAS_LOW = 1,
    GAS_HIGH = 2,
    GAS_DANGEROUS = 3
} GasAlertLevel;

void state_machine_update(uint16_t ppm);
void state_machine_toggle(void);
void state_machine_reset(void);
SystemState get_system_state(void);
GasAlertLevel get_alert_level(void);

#endif
