/* Blink Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"

#define LED_PIN 2
#define SWITCH_PIN 13


int state = 0;
QueueHandle_t interputQueue;

static void IRAM_ATTR gpio_interrupt_handler(void *args)
{
    int pinNumber = (int)args;
    xQueueSendFromISR(interputQueue, &pinNumber, NULL);
}


void LED_Control_Task(void *params)
{
    int pinNumber, count = 0;
    while (true)
    {
        if (xQueueReceive(interputQueue, &pinNumber, portMAX_DELAY))
        {
            printf("GPIO %d was pressed %d times. The state is %d\n", pinNumber, count++, gpio_get_level(SWITCH_PIN));
            gpio_set_level(LED_PIN, gpio_get_level(SWITCH_PIN));
        }
    }
}


void app_main()
{
	esp_rom_gpio_pad_select_gpio(LED_PIN);	
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

	esp_rom_gpio_pad_select_gpio(SWITCH_PIN);
    gpio_set_direction(SWITCH_PIN, GPIO_MODE_INPUT);
    gpio_pulldown_en(SWITCH_PIN);
    gpio_pullup_dis(SWITCH_PIN);
    gpio_set_intr_type(SWITCH_PIN, GPIO_INTR_POSEDGE);

    interputQueue = xQueueCreate(10, sizeof(int));
    xTaskCreate(LED_Control_Task, "LED_Control_Task", 2048, NULL, 1, NULL);

    gpio_install_isr_service(0);
    gpio_isr_handler_add(SWITCH_PIN, gpio_interrupt_handler, (void *)SWITCH_PIN);
}





// #include <stdio.h>
// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"
// #include "driver/gpio.h"
// #include "esp_log.h"
// #include "led_strip.h"
// #include "sdkconfig.h"

// #define PIN_LED GPIO_NUM_2
// #define PIN_SWITCH GPIO_NUM_13


// static void IRAM_ATTR gpio_interrupt_handler(void *args)
// {
    // int pinNumber = (int)args;
	// static RTC_RODATA_ATTR const char fmt_str[] = 
		// "Hello from %d\n";
	// esp_rom_printf(fmt_str, pinNumber);
// }


// void app_main(void)
// {
    // /* Configure the peripheral */
	// esp_rom_gpio_pad_select_gpio(PIN_SWITCH);
	// gpio_set_direction(PIN_SWITCH, GPIO_MODE_OUTPUT);
	// gpio_pulldown_en(PIN_SWITCH);
	// gpio_pullup_dis(PIN_SWITCH);
	// gpio_set_intr_type(PIN_SWITCH, GPIO_INTR_POSEDGE);
	// gpio_install_isr_service(0);
	// gpio_isr_handler_add(PIN_SWITCH, gpio_interrupt_handler, (void *)PIN_SWITCH);	
	
	// /*	
    // while (true) {
		// int level = gpio_get_level(PIN_SWITCH);
		// gpio_set_level(PIN_LED, level);
		
        // // Toggle the LED state
        // vTaskDelay(1);
    // }
	// */
// }