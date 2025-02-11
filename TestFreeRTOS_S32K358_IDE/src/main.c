/******************************************************************************
 *                                                                            *
 *   FreeRTOS sample application for RTD on S32 platforms                     *
 *                                                                            *
 *   Copyright 2023 NXP                                                       *
 *                                                                            *
 ******************************************************************************/

/* Including necessary configuration files. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "uart.h"

#define main_TASK_PRIORITY                ( tskIDLE_PRIORITY + 2 )

SemaphoreHandle_t sem_handle;

/**
* @brief        SendTask is used to give the semaphore
* @details      SendTask give the semaphore every 1 second
*/
void SendTask( void *pvParameters )
{
    (void)pvParameters;
    BaseType_t operation_status;

    for( ;; )
    {
        operation_status = xSemaphoreGive(sem_handle);
        configASSERT(operation_status == pdPASS);
        UART_printf("Hello from sendTask\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

/**
* @brief        ReceiveTask get the semaphore
* @details      ReceiveTask try to get the semaphore with portMAX_DELAY timeout,
*               After receiving the semaphore successfully, prints
*/
void ReceiveTask( void *pvParameters )
{
    (void)pvParameters;
    BaseType_t operation_status;

    for( ;; )
    {
        operation_status = xSemaphoreTake(sem_handle, portMAX_DELAY);
        configASSERT(operation_status == pdPASS);
        UART_printf("Hello from recTask\n");
    }
}

/**
* @brief        Main function of the example
* @details      Initializes the used drivers and uses 1 binary Semaphore and 2 tasks
*/
int main(void)
{
	UART_init();

    UART_printf("Hello from main\n");

    vSemaphoreCreateBinary(sem_handle);
    xTaskCreate( SendTask   , ( const char * const ) "SendTask", configMINIMAL_STACK_SIZE, (void*)0, main_TASK_PRIORITY, NULL );
    xTaskCreate( ReceiveTask, ( const char * const ) "RecTask" , configMINIMAL_STACK_SIZE, (void*)0, main_TASK_PRIORITY + 1, NULL );
    vTaskStartScheduler();

    for( ;; );

    return 0;
}

