/* Blink Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "led_strip.h"
#include "sdkconfig.h"

#define PIN_LED GPIO_NUM_2
#define PIN_SWITCH GPIO_NUM_13

void app_main(void)
{
    /* Configure the peripheral */
	gpio_set_direction(PIN_LED, GPIO_MODE_OUTPUT);
	gpio_set_direction(PIN_SWITCH, GPIO_MODE_INPUT);
	gpio_pulldown_en(PIN_SWITCH);
	gpio_pullup_dis(PIN_SWITCH);
		
    while (true) {
		int level = gpio_get_level(PIN_SWITCH);
		gpio_set_level(PIN_LED, level);
		
        /* Toggle the LED state */
        vTaskDelay(1);
    }
}
