#include "tasks.h"
#include "config.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

void vTaskGravarDados(void *params) {
    while (true) {
        // Espera até que a tarefa de captura de dados tenha coletado dados
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        if(xSemaphoreTake(xMutexCartaoSD, portMAX_DELAY) == pdTRUE) {
            printf("Gravando dados no cartão SD...\n");
            estado_sistema = GRAVANDO_SD; // Atualiza o estado do sistema para gravando
            // Simula a gravação de dados
            vTaskDelay(pdMS_TO_TICKS(5000)); // Simula um delay de 5 segundos para a gravação
            estado_sistema = PRONTO; // Atualiza o estado do sistema para pronto após gravar
            xSemaphoreGive(xMutexCartaoSD); // Libera o semáforo após gravar os dados
        } else {
            printf("Erro ao obter o semáforo para acesso ao cartão SD.\n");
        }

        // Exemplo de uso da variável "quantidade_coletada"
        printf("Gravando %d amostras no cartão SD...\n", quantidade_coletada);
    }
}