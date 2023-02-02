/************************************************************
Author: Katuri Keerthana
PG- DESD
Roll No : 220950330005
Question1
*************************************************************/

//Headers
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

//Macro definitions
#define MSG_QUEUELENGTH 4
#define MSG_SIZE 64

//Global variable declarations i.e., handles
TaskHandle_t task1_handle;
TaskHandle_t task2_handle;
TaskHandle_t task3_handle;
TaskHandle_t task4_handle;
TaskHandle_t task5_handle;
QueueHandle_t Queuehandle;

static int taskcore =1;

//Task definitions
void task1(void *data)
{
    printf("In task1\n");
    vTaskDelay(pdMS_TO_TICKS(1000));
    // To check the periodicity of task1
    for(;;)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
        printf("task1 again\n");
    }
    vTaskDelete(task1_handle);
}

void task2(void *data)
{
    printf("In task2\n");
    vTaskDelay(pdMS_TO_TICKS(2000));
    // To check the periodicity of task2
    for(;;)
    {
        vTaskDelay(pdMS_TO_TICKS(2000));
        printf("task2 again\n");
    }
    vTaskDelete(task2_handle);
}

void task3(void *data)
{
    printf("In task3\n");
    vTaskDelay(pdMS_TO_TICKS(5000));
    // To check the periodicity of task3
    for(;;)
    {
        vTaskDelay(pdMS_TO_TICKS(5000));
        printf("task3 again\n");
    }
    vTaskDelete(task3_handle);
}
void task4(void *data)
{
    int k = 1;
    printf("In task4\n");
    vTaskDelay(pdMS_TO_TICKS(500));
    // Sending 100 numbers into message queue
    while(1)
    {
        // Sending messages into the created message queue
        xQueueSend(Queuehandle, &k, pdMS_TO_TICKS(100));
        vTaskDelay(pdMS_TO_TICKS(100));
        k++;
    }
    vTaskDelete(task4_handle);
}

void task5(void *data)
{
    int pvBuffer;

    printf("In task5\n");
    vTaskDelay(pdMS_TO_TICKS(500));
    // Receiving messages from the message queue
    while(xQueueReceive( Queuehandle,&pvBuffer,portMAX_DELAY) == pdPASS)
    {
        //Monitoring the messages received
        printf("Received message = %d\n",pvBuffer);
    }
    
    vTaskDelete(task5_handle);
}  

void app_main(void)
{
    BaseType_t res;// To check whether the task is created successsfully

    printf("In main function\n");

    // Creating tasks which will be executed in same processor core
    res = xTaskCreatePinnedToCore(task1,"t1",2048,NULL,5,&task1_handle,taskcore);
    if(res == pdPASS)
    {
        printf("Created task1 successfully\n");
    }
    res = xTaskCreatePinnedToCore(task2,"t2",2048,NULL,6,&task2_handle,taskcore);
    if(res == pdPASS)
    {
        printf("Created task2 successfully\n");
    }
    res = xTaskCreatePinnedToCore(task3,"t3",2048,NULL,7,&task3_handle,taskcore);
    if(res == pdPASS)
    {
        printf("Created task3 successfully\n");
    }
    res = xTaskCreatePinnedToCore(task4,"t4",2048,NULL,8,&task4_handle,taskcore);
    if(res == pdPASS)
    {
        printf("Created task4 successfully\n");
    }
    res = xTaskCreatePinnedToCore(task5,"t5",2048,NULL,9,&task5_handle,taskcore);
    if(res == pdPASS)
    {
        printf("Created task5 successfully\n");
    }

    // Creating message queue
    Queuehandle = xQueueCreate( MSG_QUEUELENGTH, MSG_SIZE );
    if(Queuehandle != NULL)
    {
        printf("Queue created successfully\n");
    }
}


