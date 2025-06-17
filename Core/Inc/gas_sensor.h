#ifndef __GAS_SENSOR_H
#define __GAS_SENSOR_H

#include <stdint.h>

void gas_sensor_init(void);
void gas_sensor_calibrate(void);
uint16_t gas_sensor_read_ppm(void);

#endif
