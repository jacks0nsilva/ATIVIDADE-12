#include "tasks.h"
#include "config.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include "fatfslib.h"

void vTaskGravarDados(void *params) {
    while (true) {
        // Espera até que a tarefa de captura de dados tenha coletado dados
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        if(xSemaphoreTake(xMutexCartaoSD, portMAX_DELAY) == pdTRUE) {
            printf("Gravando dados no cartão SD...\n");
            estado_sistema = GRAVANDO_SD; // Atualiza o estado do sistema para gravando
            vTaskDelay(pdMS_TO_TICKS(2000)); // Delay para simular o tempo de gravação
            write_file();
            vTaskDelay(pdMS_TO_TICKS(1500)); // Delay para simular o tempo de feedback
            estado_sistema = PRONTO; // Atualiza o estado do sistema para pronto após gravar
            xSemaphoreGive(xMutexCartaoSD); // Libera o semáforo após gravar os dados
            // Exemplo de uso da variável "quantidade_coletada"
            printf("Gravando %d amostras no cartão SD...\n", quantidade_coletada);
        }
    }
}