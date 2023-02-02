/************************************************************
Author: Katuri Keerthana
PG- DESD
Roll No : 220950330005
Question2
*************************************************************/

//Headers
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"

//Global variable declarations i.e., handles
TaskHandle_t task1_handle;
TaskHandle_t task2_handle;
TaskHandle_t task3_handle;
TimerHandle_t timerhandle;

static int taskcore =1;

//Task definitions
void callbackfunction()
{
    printf("One shot Timer fired from Task3\n");
}

void task1(void *data)
{
    printf("In task1\n");
    vTaskDelay(pdMS_TO_TICKS(1000));
    // To check the periodicity of task1
    for(int i=1;i<10;i++)
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
    for(int i=1;i<5;i++)
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
    printf("task3 again\n");
    timerhandle = xTimerCreate("10sec_oneshottimer",10000/portTICK_PERIOD_MS,pdFALSE,NULL,callbackfunction);
    if(xTimerStart(timerhandle,0) == pdPASS)
    {
        printf("Timer activated successfully\n");
    }
    // To check the periodicity of task3
    for(int i=1;i<2;i++)
    {
        vTaskDelay(pdMS_TO_TICKS(5000));
        printf("task3 again\n");
    }
    vTaskDelete(task3_handle);
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
}
