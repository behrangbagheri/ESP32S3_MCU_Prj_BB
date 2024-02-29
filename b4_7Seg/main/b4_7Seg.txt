/* Blink Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
// #include <stdio.h>
// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"
// #include "driver/gpio.h"
// #include "esp_log.h"
// #include "led_strip.h"
// #include "sdkconfig.h"

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"

#define SSeg_A 4
#define SSeg_B 5
#define SSeg_C 6
#define SSeg_D 7
#define SSeg_E 15
#define SSeg_F 16
#define SSeg_G 17

#define SWITCH_PIN 18

void Initialization(void);
void SSeg_driver(int data);

/*
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
*/

void app_main()
{
	Initialization();	
		
	while(1){
		for (int i = 0 ; i <= 9 ; i++){
			SSeg_driver(i);
			printf("7-Segment is displaying %d now ...\n", i);
			vTaskDelay(1000 / portTICK_PERIOD_MS);
		}
	}
	/*	
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
	*/
}


void Initialization(void)
{
	esp_rom_gpio_pad_select_gpio(SSeg_A);	
    gpio_set_direction(SSeg_A, GPIO_MODE_OUTPUT);
	esp_rom_gpio_pad_select_gpio(SSeg_B);	
    gpio_set_direction(SSeg_B, GPIO_MODE_OUTPUT);
	esp_rom_gpio_pad_select_gpio(SSeg_C);	
    gpio_set_direction(SSeg_C, GPIO_MODE_OUTPUT);
	esp_rom_gpio_pad_select_gpio(SSeg_D);	
    gpio_set_direction(SSeg_D, GPIO_MODE_OUTPUT);
	esp_rom_gpio_pad_select_gpio(SSeg_E);	
    gpio_set_direction(SSeg_E, GPIO_MODE_OUTPUT);
	esp_rom_gpio_pad_select_gpio(SSeg_F);	
    gpio_set_direction(SSeg_F, GPIO_MODE_OUTPUT);
	esp_rom_gpio_pad_select_gpio(SSeg_G);	
    gpio_set_direction(SSeg_G, GPIO_MODE_OUTPUT);
}

void SSeg_driver(int data)
{
	int isOFF = 1;
	int isON = 0;
	int Data_SegA, Data_SegB, Data_SegC, Data_SegD, Data_SegE, Data_SegF, Data_SegG = 0;
	
	switch(data) 
	{
		case 0:	
			Data_SegA = isON, Data_SegB = isON, Data_SegC = isON, Data_SegD = isON,	Data_SegE = isON, Data_SegF = isON, Data_SegG = isOFF;			
		break;
		case 1:	
			Data_SegA = isOFF, Data_SegB = isON, Data_SegC = isON, Data_SegD = isOFF, Data_SegE = isOFF, Data_SegF = isOFF, Data_SegG = isOFF;		
		break;	
		case 2:	
			Data_SegA = isON, Data_SegB = isON, Data_SegC = isOFF, Data_SegD = isON, Data_SegE = isON, Data_SegF = isOFF, Data_SegG = isON;	
		break;
		case 3:	
			Data_SegA = isON, Data_SegB = isON, Data_SegC = isON, Data_SegD = isON,	Data_SegE = isOFF, Data_SegF = isOFF, Data_SegG = isON;		
		break;
		case 4:	
			Data_SegA = isOFF, Data_SegB = isON, Data_SegC = isON, Data_SegD = isOFF, Data_SegE = isOFF, Data_SegF = isON, Data_SegG = isON;			
		break;
		case 5:	
			Data_SegA = isON, Data_SegB = isOFF, Data_SegC = isON, Data_SegD = isON, Data_SegE = isOFF, Data_SegF = isON, Data_SegG = isON;		
		break;
		case 6:	
			Data_SegA = isON, Data_SegB = isOFF, Data_SegC = isON, Data_SegD = isON, Data_SegE = isON, Data_SegF = isON, Data_SegG = isON;			
		break;
		case 7:	
			Data_SegA = isON, Data_SegB = isON, Data_SegC = isON, Data_SegD = isOFF, Data_SegE = isOFF, Data_SegF = isOFF, Data_SegG = isOFF;		
		break;
		case 8:	
			Data_SegA = isON, Data_SegB = isON, Data_SegC = isON, Data_SegD = isON,	Data_SegE = isON, Data_SegF = isON, Data_SegG = isON;		
		break;	
		case 9:	
			Data_SegA = isON, Data_SegB = isON, Data_SegC = isON, Data_SegD = isON,	Data_SegE = isOFF, Data_SegF = isON, Data_SegG = isON;		
		break;		
		default:	
			Data_SegA = isON, Data_SegB = isON, Data_SegC = isON, Data_SegD = isON,	Data_SegE = isON, Data_SegF = isON, Data_SegG = isOFF;
	}
	gpio_set_level(SSeg_A, Data_SegA);	
	gpio_set_level(SSeg_B, Data_SegB);	
	gpio_set_level(SSeg_C, Data_SegC);	
	gpio_set_level(SSeg_D, Data_SegD);	
	gpio_set_level(SSeg_E, Data_SegE);	
	gpio_set_level(SSeg_F, Data_SegF);	
	gpio_set_level(SSeg_G, Data_SegG);	
}

