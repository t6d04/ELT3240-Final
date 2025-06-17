#include "state_machine.h"
#include "led.h"
#include "buzzer.h"
#include "i2c.h"
#include "lcd.h"
#include "timer.h"
#include <stdio.h>
#include "stm32f4xx.h"

static uint32_t lcd_last_update = 0;
static uint8_t lcd_paused_displayed = 0;
static uint32_t led_danger_last_toggle = 0;
static uint8_t led_danger_on = 0;

static SystemState system_state = SYSTEM_STOPPED;
static GasAlertLevel gas_alert_level = GAS_SAFE;

SystemState get_system_state(void)
{
    return system_state;
}

GasAlertLevel get_alert_level(void)
{
    return gas_alert_level;
}

void state_machine_toggle(void)
{
    if (system_state == SYSTEM_STOPPED)
    {
        system_state = SYSTEM_RUNNING;
    }
    else
    {
        system_state = SYSTEM_STOPPED;
    }
}

void state_machine_reset(void)
{
//    system_state = SYSTEM_STOPPED;
//    gas_alert_level = GAS_SAFE;
    NVIC_SystemReset();
}

void state_machine_update(uint16_t ppm)
{
	buzzer_check();
	led_check();
	if (system_state == SYSTEM_STOPPED)
	{
	    led_off_all();
	    led_off(LED_POWER_PIN);
	    buzzer_off();
	    if (!lcd_paused_displayed)
		{
	    	lcd_command(0x01);
			lcd_print("DISABLED");
			lcd_paused_displayed = 1;
		}
	    return;
	}
	else
	{
	    led_on(LED_POWER_PIN); // bật lại sau khi all_off
	}

	lcd_paused_displayed = 0;

    if (ppm < 200)
    {
        gas_alert_level = GAS_SAFE;
    }
    else if (ppm < 350)
    {
        gas_alert_level = GAS_LOW;
    }
    else if (ppm < 500)
    {
        gas_alert_level = GAS_HIGH;
    }
    else
    {
        gas_alert_level = GAS_DANGEROUS;
    }
    uint32_t now = millis();
    switch (gas_alert_level)
    {
        case GAS_SAFE:
            led_off_all();
            led_on(LED_SAFE_PIN);
            buzzer_off();
            break;

        case GAS_LOW:
            led_off_all();
            led_on(LED_WARNING_PIN);
            buzzer_off();
            break;

        case GAS_HIGH:
            led_off_all();

			if (now - led_danger_last_toggle >= 1000) {
				led_danger_last_toggle = now;

				if (led_danger_on) {
					led_off(LED_DANGER_PIN);
					led_danger_on = 0;
				} else {
					led_on(LED_DANGER_PIN);
					led_danger_on = 1;
				}
			}
            buzzer_off();
            break;

        case GAS_DANGEROUS:
            led_off_all();
            buzzer_on(0);
			if (now - led_danger_last_toggle >= 200) {
				led_danger_last_toggle = now;

				if (led_danger_on) {
					led_off(LED_DANGER_PIN);
					led_danger_on = 0;
				} else {
					led_on(LED_DANGER_PIN);
					led_danger_on = 1;
				}
			}
            break;
    }

//    uint32_t now = millis();
    if (now - lcd_last_update >= 500) {
        lcd_last_update = now;

        char buf[20];
        lcd_command(0x01);
        sprintf(buf, "Gas: %u ppm", ppm);
        lcd_print(buf);
        lcd_command(0xC0);

        switch (gas_alert_level)
        {
            case GAS_SAFE: lcd_print("Safe"); break;
            case GAS_LOW: lcd_print("Low"); break;
            case GAS_HIGH: lcd_print("High"); break;
            case GAS_DANGEROUS: lcd_print("DANGER"); break;
        }
    }
}
