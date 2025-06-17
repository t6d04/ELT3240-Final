#include "gas_sensor.h"
#include "adc.h"
#include <math.h>

#define RL 10000.0f
#define VCC 3.3f
static float R0 = 10000.0f;

static float rs_from_adc(uint16_t adc)
{
    float vout = ((float)adc / 4095.0f) * VCC;
    if (vout < 0.01f) vout = 0.01f;
    float rs = (VCC - vout) * RL / vout;
    return rs;
}

void gas_sensor_init(void)
{
    adc_init();
}

void gas_sensor_calibrate(void)
{
    uint32_t sum = 0;
    for (int i = 0; i < 100; i++) {
        sum += adc_read();
    }
    uint16_t avg_adc = sum / 100;
    float rs = rs_from_adc(avg_adc);
    R0 = rs / 1.0f;
}

uint16_t gas_sensor_read_ppm(void)
{
    uint16_t adc = adc_read();
    float rs = rs_from_adc(adc);
    float ratio = rs / R0;

    float log_ppm = (log10f(ratio) - 0.32f) / -0.47f;
    float ppm = powf(10.0f, log_ppm);
    if (ppm > 10000.0f) ppm = 10000.0f;

    return (uint16_t)ppm;
}
