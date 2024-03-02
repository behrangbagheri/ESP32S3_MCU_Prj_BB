// I have this code for esp32s3 uart, please add code and comment to read letters from keyboard 

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "driver/gpio.h"
#include "driver/uart.h"
#include <string.h>

#define UART_NUM 		UART_NUM_1
#define TXD_PIN 		GPIO_NUM_4
#define RXD_PIN 		GPIO_NUM_5
#define RX_BUF_SIZE 	1024

void uart_init() {
	printf("I am at uart_init() ...\n");
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };
    uart_param_config(UART_NUM, &uart_config);
    uart_set_pin(UART_NUM, TXD_PIN, RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    uart_driver_install(UART_NUM, RX_BUF_SIZE, 0, 0, NULL, 0);
}

//void uart_task_tx(const char *data) {
void uart_tx() {
	printf("I am at uart_tx() ...\n");
	char data[] = "ping";
	printf("Sending: %s\n", data);
	uart_write_bytes(UART_NUM, data, sizeof(data));	
}

void uart_rx() {
	printf("I am at uart_rx() ...\n");
	char data[RX_BUF_SIZE];
	memset(data, 0, sizeof(data));
	uart_read_bytes(UART_NUM, (uint8_t *) data, RX_BUF_SIZE, pdMS_TO_TICKS(500));
    printf("Received: %s\n", data);	
}

void app_main() {
	printf("I am at app_main() ...\n");
    
	uart_init();
	uart_tx();
	uart_rx();
}


	











/*
	char input_char;
	printf("Press any key to continue...\n");
	while (1) { // Continuously read characters from the keyboard

		input_char = getchar();
		
		if(input_char != '\n')
			printf("You entered: %c\n", input_char);
			continue;
		
		//scanf("%c", &input_char); // Read a character from the keyboard
		//printf("Received: %c\n", input_char);	
		//uart_write_bytes(UART_NUM, &input_char, 1); // Send the character over UART
		
	}
	
	//char input_char;
    //printf("Enter a letter: ");
    //scanf("%c", &input_char); // Read a character from the keyboard
	
   // printf("You entered: %c\n", input_char); // Print the entered character
   
    char input_char;

    do {
        printf("Press any key to continue (or 'q' to quit): ");
        input_char = getchar(); // Read a character from the keyboard
        getchar(); // Consume newline character

        printf("You pressed: %c\n", input_char); // Print the pressed character

    } while (input_char != 'q'); // Continue looping until 'q' is pressed

    printf("Exiting the program.\n");
*/


