#include <stdio.h>
#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "tasks.h"



int main()
{
    stdio_init_all();

    // Criação da tarefa
    //xTaskCreate(vTask1, "Task 1", 256, NULL, 1, NULL);
    xTaskCreate(vTaskCapturarDados, "Capturar Dados", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    // Início do scheduler
    vTaskStartScheduler();
    panic_unsupported(); 
}

