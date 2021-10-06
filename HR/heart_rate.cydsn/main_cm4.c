#include "project.h"
#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include <limits.h>
#include "BLE_Task.h"

int main(void)
{
    __enable_irq(); /* Enable global interrupts. */

    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    printf("System Started!! \r\n");
    xTaskCreate(bleTask, "BLE Task", 8*1024, 0, 2, 0);
    vTaskStartScheduler();
    for(;;)
    {

    }
}

/* [] END OF FILE */
