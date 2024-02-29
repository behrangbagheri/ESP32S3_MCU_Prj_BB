#include <stdio.h>
#include <stdlib.h> 
#include <time.h>   
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"

// Define task handles
TaskHandle_t movement_task_handle;
TaskHandle_t sensor_task_handle;

// Define semaphore for task synchronization (block or unblock a task)
SemaphoreHandle_t movement_semaphore;

// Define queue for communication between tasks (pass data from one task to another)
QueueHandle_t movement_queue;

// Function prototypes
void movement_task(void *pvParameters);
void sensor_task(void *pvParameters);
void stop_movement();
void move_forward();
void move_backward();
void read_camera();

void app_main()
{
    // Create semaphore
    movement_semaphore = xSemaphoreCreateBinary();
    
    // Create queue
    movement_queue = xQueueCreate(1, sizeof(int));

    // Create movement task
    xTaskCreate(movement_task, "Movement Task", 2048, NULL, 2, &movement_task_handle);

    // Create sensor task
    xTaskCreate(sensor_task, "Sensor Task", 2048, NULL, 3, &sensor_task_handle);
}

void movement_task(void *pvParameters)
{
    int command;

    while (1)
    {
        // Read camera every 100ms
        read_camera();
        vTaskDelay(100 / portTICK_PERIOD_MS);

        // Wait for semaphore to be available
        if (xSemaphoreTake(movement_semaphore, portMAX_DELAY) == pdTRUE)
        {
            // Receive command from the queue
            if (xQueueReceive(movement_queue, &command, portMAX_DELAY) == pdTRUE)
            {
                switch (command)
                {
                case 1:
                    move_forward();
                    break;
                case 2:
                    move_backward();
                    break;
                case 3:
                    stop_movement();
                    break;
                default:
                    printf("Invalid command\n");
                }
            }
        }
    }
}

void sensor_task(void *pvParameters)
{
    while (1)
    {
        // Generate a random delay between 2 and 5 seconds
        int delay_ms = (rand() % 3000) + 2000;
        vTaskDelay(delay_ms / portTICK_PERIOD_MS);

        // Trigger stop movement function
        stop_movement();
    }
}

void stop_movement()
{
    // Send stop command to movement task through queue
    int stop_command = 3;
    xQueueSend(movement_queue, &stop_command, portMAX_DELAY);

    // Give semaphore to movement task
    xSemaphoreGive(movement_semaphore);
}

void move_forward()
{
    // Send move forward command to movement task through queue
    int forward_command = 1;
    xQueueSend(movement_queue, &forward_command, portMAX_DELAY);

    // Give semaphore to movement task
    xSemaphoreGive(movement_semaphore);
}

void move_backward()
{
    // Send move backward command to movement task through queue
    int backward_command = 2;
    xQueueSend(movement_queue, &backward_command, portMAX_DELAY);

    // Give semaphore to movement task
    xSemaphoreGive(movement_semaphore);
}

void read_camera()
{
    // Simulated camera reading
    printf("Reading camera...\n");
}
