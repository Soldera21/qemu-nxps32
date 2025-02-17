#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "uart.h"
#include "can.h"
#include <stdio.h>

#define main_TASK_PRIORITY                ( tskIDLE_PRIORITY + 2 )

SemaphoreHandle_t sem1;
SemaphoreHandle_t sem2;


void Task1( void *pvParameters )
{
    (void)pvParameters;
    BaseType_t operation_status;
    char msg[40];
    frame_t frame;

    for( ;; )
    {
		frame.can_id=1234;
		frame.data[0]=10;
		frame.data[1]=12;
		frame.data[2]=14;
		frame.data[3]=16;
		frame.can_dlc=4;

		UART_printf("Writing tsk1 to CAN...\n");
		CAN_write(&frame);

        operation_status = xSemaphoreGive(sem1);
        configASSERT(operation_status == pdPASS);

        operation_status = xSemaphoreTake(sem2, portMAX_DELAY);
        configASSERT(operation_status == pdPASS);

        CAN_read(&frame);

		snprintf(msg, sizeof(msg), "Received tsk1 ID from CAN: %u\n", frame.can_id);
		UART_printf(msg);
		snprintf(msg, sizeof(msg), "Received tsk1 DLC from CAN: %u\n", frame.can_dlc);
		UART_printf(msg);
		for(int i = 0; i < frame.can_dlc; i++){
			snprintf(msg, sizeof(msg), "Received tsk1 from CAN: %u\n", frame.data[i]);
			UART_printf(msg);
		}

        vTaskDelay(pdMS_TO_TICKS(500));
    }
}


void Task2( void *pvParameters )
{
    (void)pvParameters;
    BaseType_t operation_status;
    char msg[40];
    frame_t frame;

    for( ;; )
    {
        operation_status = xSemaphoreTake(sem1, portMAX_DELAY);
        configASSERT(operation_status == pdPASS);

		CAN_read(&frame);

		snprintf(msg, sizeof(msg), "Received tsk2 ID from CAN: %u\n", frame.can_id);
		UART_printf(msg);
		snprintf(msg, sizeof(msg), "Received tsk2 DLC from CAN: %u\n", frame.can_dlc);
		UART_printf(msg);
		for(int i = 0; i < frame.can_dlc; i++){
			snprintf(msg, sizeof(msg), "Received tsk2 from CAN: %u\n", frame.data[i]);
			UART_printf(msg);
		}

		vTaskDelay(pdMS_TO_TICKS(500));

		frame.can_id=432;
		frame.data[0]=15;
		frame.data[1]=17;
		frame.data[2]=19;
		frame.can_dlc=3;

		UART_printf("Writing tsk2 to CAN...\n");
		CAN_write(&frame);

		operation_status = xSemaphoreGive(sem2);
		configASSERT(operation_status == pdPASS);
    }
}

/**
* @brief        Main function of the example
* @details      Initializes the used drivers and uses 1 binary Semaphore and 2 tasks
*/
int main(void)
{
	UART_init();
	CAN_init();

    UART_printf("Hello from main\n");

    vSemaphoreCreateBinary(sem1);
    vSemaphoreCreateBinary(sem2);

    xSemaphoreTake(sem1, portMAX_DELAY);
    xSemaphoreTake(sem2, portMAX_DELAY);

    xTaskCreate( Task1, ( const char * const ) "Task1", configMINIMAL_STACK_SIZE + 512, (void*)0, main_TASK_PRIORITY, NULL );
    xTaskCreate( Task2, ( const char * const ) "Task2", configMINIMAL_STACK_SIZE + 512, (void*)0, main_TASK_PRIORITY, NULL );
    vTaskStartScheduler();

    for( ;; );

    return 0;
}

