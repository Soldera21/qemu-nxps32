/******************************************************************************
 *                                                                            *
 *   FreeRTOS sample application for RTD on S32 platforms                     *
 *                                                                            *
 *   Copyright 2023 NXP                                                       *
 *                                                                            *
 ******************************************************************************/

/* Including necessary configuration files. */
//#include "Clock_Ip.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "uart.h"

#define main_TASK_PRIORITY                ( tskIDLE_PRIORITY + 2 )

SemaphoreHandle_t sem_handle;
volatile BaseType_t testResult = 0x33U;

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
        /* Not very exciting - just delay... */
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

/**
* @brief        ReceiveTask get the semaphore and toggle pins
* @details      ReceiveTask try to get the semaphore with portMAX_DELAY timeout,
*               After receiving the semaphore successfully, the led will be toggle
*               LED_PIN <-> PTA1
*/
void ReceiveTask( void *pvParameters )
{
    (void)pvParameters;
    BaseType_t operation_status;
    BaseType_t count = 0;

    for( ;; )
    {
        operation_status = xSemaphoreTake(sem_handle, portMAX_DELAY);
        configASSERT(operation_status == pdPASS);
        if(count++ > 10)
        {
            testResult = 0x5AU;
        }
        UART_printf("Hello, World! from task\n");
    }
}

/**
* @brief        Main function of the example
* @details      Initializes the used drivers and uses 1 binary Semaphore and
*               2 tasks to toggle a LED.
*/
int main(void)
{
	UART_init();

    /* Initialize Clock */
    /*Clock_Ip_StatusType Status_Init_Clock = CLOCK_IP_ERROR;
    Status_Init_Clock = Clock_Ip_Init(Clock_Ip_aClockConfig);

    if (Status_Init_Clock != CLOCK_IP_SUCCESS)
    {
        while(1);
    }*/

    UART_printf("Hello, World! from main\n");

    vSemaphoreCreateBinary(sem_handle);
    xTaskCreate( SendTask   , ( const char * const ) "SendTask", configMINIMAL_STACK_SIZE, (void*)0, main_TASK_PRIORITY, NULL );
    xTaskCreate( ReceiveTask, ( const char * const ) "RecTask" , configMINIMAL_STACK_SIZE, (void*)0, main_TASK_PRIORITY + 1, NULL );
    vTaskStartScheduler();

    for( ;; );

    return 0;
}

/** @} */
