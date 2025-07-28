#include "tasks.h"
#include "config.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include "fatfslib.h"

void vTaskMontarDesmontarSD(void *params) {
    while (true) {
        // Espera até que a tarefa de captura de dados tenha coletado dados
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        printf("Iniciando montagem/desmontagem do cartão SD...\n");
        if(xSemaphoreTake(xMutexCartaoSD, portMAX_DELAY) == pdTRUE){
            printf("Montando/desmontando o cartão SD...\n");
            if(!cartao_montado) {
                estado_sistema = MONTANDO_SD; // Atualiza o estado do sistema para montando
                printf("Montando o cartão SD...\n");
                run_mount();
                vTaskDelay(pdMS_TO_TICKS(2000)); // Delay para simular o tempo de montagem
            } else {
                printf("Desmontando o cartão SD...\n");
                run_unmount();
                estado_sistema = DESMONTANDO_SD; // Atualiza o estado do sistema para desmontando
                vTaskDelay(pdMS_TO_TICKS(2000)); // Delay para simular o tempo de desmontagem
            }
            estado_sistema = PRONTO; // Atualiza o estado do sistema para pronto após montar/desmontar
            xSemaphoreGive(xMutexCartaoSD); // Libera o semáforo após montar
        } else {
            printf("Erro ao obter o semáforo para acesso ao cartão SD.\n");
        }


    }
}
