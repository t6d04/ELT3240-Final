#include "stm32f4xx.h"
#include "gpio.h"
#include "timer.h"
#include "buzzer.h"
#include "led.h"
#include "state_machine.h"
#include "i2c.h"
#include "lcd.h"
#include "adc.h"
#include "gas_sensor.h"
#include "button.h"
#include <stdio.h>
#include "uart.h"
#include "scheduler.h"
#include "relay.h"

int main(void){
	timer_init();
	gpio_init();
	button_init();

	i2c2_init();
	lcd_init();

	uart1_init();

    gas_sensor_init();
    gas_sensor_calibrate();

//    led_on(LED_DANGER_PIN);
//
	while(1){

		uint16_t ppm = gas_sensor_read_ppm();
		state_machine_update(ppm);
		if(get_system_state() == 1){
			scheduler_update(ppm, get_alert_level());
		}
	}

}
