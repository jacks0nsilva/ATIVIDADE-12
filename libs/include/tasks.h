#ifndef TASKS_H
#define TASKS_H

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

// Definições e declarações relacionadas às tarefas do FreeRTOS
void vTaskCapturarDados(void *params); // Declaração da tarefa para capturar dados do MPU6050
void vTaskGravarDados(void *params); // Declaração da tarefa para gravar dados no cartão SD
void vTaskMontarDesmontarSD(void *params); // Declaração da tarefa para montar/desmontar o cartão SD
void vTaskLeds(void *params); // Declaração da tarefa para controlar os LEDs

extern SemaphoreHandle_t xMutexCartaoSD; // Semáforo para acesso ao cartão SD
extern TaskHandle_t xHandleGravar; // Handle para a tarefa de gravar dados no cartão SD
#endif // TASKS_H