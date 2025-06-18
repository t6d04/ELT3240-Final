#ifndef __RELAY_H
#define __RELAY_H

#include <stdint.h>

void relay_init(void);
void relay_on(void);
void relay_off(void);
uint8_t relay_status(void);

#endif
