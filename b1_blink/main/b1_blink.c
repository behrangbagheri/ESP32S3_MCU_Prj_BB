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

void app_main(void)
{
    /* Configure the peripheral */
	gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);
	int isOn = 0;
    while (true) {
        isOn = !isOn;
		gpio_set_level(GPIO_NUM_2, isOn);
		
        /* Toggle the LED state */
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}
