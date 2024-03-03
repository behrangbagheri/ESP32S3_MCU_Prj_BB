//This code doesnt show anything on the LCD, how to fix it?
#include <driver/i2c.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdio.h>
#include "sdkconfig.h"
#include "HD44780.h"

#define LCD_ADDR 0x27
#define SDA_PIN  21
#define SCL_PIN  0
#define LCD_COLS 16
#define LCD_ROWS 2

void LCD_DemoTask(void* param)
{
    printf("I am at LCD_DemoTask() ...\n");
	char num[20];
    while (true) {
        LCD_home();
        LCD_clearScreen();
		printf("16x2 I2C LCD\n");
        LCD_writeStr("16x2 I2C LCD");
        vTaskDelay(3000 / portTICK_PERIOD_MS);
        LCD_clearScreen();
		printf("Lets Count 0-20!\n");
        LCD_writeStr("Lets Count 0-20!");
        vTaskDelay(3000 / portTICK_PERIOD_MS);
        LCD_clearScreen();
        for (int i = 0; i <= 20; i++) {
			printf("Counter is %d\n", i);
            LCD_setCursor(7, 1);
            sprintf(num, "%d", i);
            LCD_writeStr(num);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
		// LCD_clearScreen();
		// LCD_setCursor(0, 0);
		// LCD_writeStr("Count Finished!");
        // vTaskDelay(3000 / portTICK_PERIOD_MS);
  
    }
}

void app_main(void)
{
	printf("I am at app_main() ...\n");
    LCD_init(LCD_ADDR, SDA_PIN, SCL_PIN, LCD_COLS, LCD_ROWS);
    xTaskCreate(LCD_DemoTask, "Demo Task", 2048, NULL, 5, NULL);
    
}