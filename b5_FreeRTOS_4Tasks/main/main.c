#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "driver/gpio.h"
#include "driver/uart.h"

#define UART_NUM UART_NUM_1
#define TXD_PIN GPIO_NUM_4
#define RXD_PIN GPIO_NUM_5
#define LED_PIN GPIO_NUM_2
#define SWITCH_PIN GPIO_NUM_15

void uart_init() {
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };
    uart_param_config(UART_NUM, &uart_config);
    uart_set_pin(UART_NUM, TXD_PIN, RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    uart_driver_install(UART_NUM, 256, 0, 0, NULL, 0);
}	

SemaphoreHandle_t semSwitch = NULL;
SemaphoreHandle_t semUART = NULL;

static void Task1(void *pvParameters) {
	printf("I am at Task1 ...\n");
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = pdMS_TO_TICKS(100);

    while (1) {
        printf("Tsk1-P1 <-\n");
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
        printf("Tsk1-P1 ->\n");
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

static void Task2(void *pvParameters) {
	printf("I am at Task2 ...\n");
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = pdMS_TO_TICKS(10);	//10

    while (1) {
        printf("           Tsk2-P2 <-\n");
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
        printf("           Tsk2-P2 ->\n");
        vTaskDelay(pdMS_TO_TICKS(250));					//250
    }
}

static void Task3(void *pvParameters) {
    printf("I am at Task3 ...\n");
	char rx_data[1];
    esp_rom_gpio_pad_select_gpio(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

    while (1) {
        printf("                      Tsk3-P3 <-\n");
        xSemaphoreTake(semUART, portMAX_DELAY);
        uart_read_bytes(UART_NUM, rx_data, sizeof(rx_data), portMAX_DELAY);
        printf("Received character: %c\n", rx_data[0]);
        if (rx_data[0] == 'L' || rx_data[0] == 'l') {
            gpio_set_level(LED_PIN, 1);
            vTaskDelay(pdMS_TO_TICKS(50));
            gpio_set_level(LED_PIN, 0);
        }
        printf("                      Tsk3-P3 ->\n");
        xSemaphoreGive(semUART);
    }
}

static void Task4(void *pvParameters) {
    printf("I am at Task4 ...\n");
	esp_rom_gpio_pad_select_gpio(SWITCH_PIN);
    gpio_set_direction(SWITCH_PIN, GPIO_MODE_INPUT);
    gpio_set_pull_mode(SWITCH_PIN, GPIO_PULLUP_ONLY);

    while (1) {
        printf("                                 Tsk4-P4 <-\n");
        xSemaphoreTake(semSwitch, portMAX_DELAY);
        printf("Switch pressed\n");
        vTaskDelay(pdMS_TO_TICKS(10));
        printf("                                 Tsk4-P4 ->\n");
        xSemaphoreGive(semSwitch);
    }
}

void app_main() {
	printf("I am at app_main() ...\n");
    uart_init();
	
    semSwitch = xSemaphoreCreateBinary();
    semUART = xSemaphoreCreateMutex();

    xSemaphoreGive(semSwitch);
    xSemaphoreGive(semUART);

    xTaskCreate(Task1, "Task1", 2048, NULL, 1, NULL);
    xTaskCreate(Task2, "Task2", 2048, NULL, 2, NULL);
    xTaskCreate(Task3, "Task3", 2048, NULL, 3, NULL);
    xTaskCreate(Task4, "Task4", 2048, NULL, 4, NULL);
	

}

