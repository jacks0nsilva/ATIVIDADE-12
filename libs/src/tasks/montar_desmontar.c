#include "tasks.h"
#include "config.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

void vTaskMontarDesmontarSD(void *params) {
    while (true) {
        // Espera até que a tarefa de captura de dados tenha coletado dados
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        // Aqui você pode adicionar o código para montar/desmontar o cartão SD
        if(xSemaphoreTake(xMutexCartaoSD, pdTRUE) == pdTRUE){
            if(!cartao_montado) {
                estado_sistema = MONTANDO_SD; // Atualiza o estado do sistema para montando
                printf("Montando o cartão SD...\n");
                cartao_montado = true; // Atualiza o estado do cartão SD para montado
                // chamaa a função de montagem do cartão SD
            } else {
                estado_sistema = DESMONTANDO_SD; // Atualiza o estado do sistema para desmontando
                printf("Desmontando o cartão SD...\n");
                cartao_montado = false; // Atualiza o estado do cartão SD para desmontado
                // chama a função de desmontagem do cartão SD
            }
            estado_sistema = PRONTO; // Atualiza o estado do sistema para pronto após montar/desmontar
            xSemaphoreGive(xMutexCartaoSD); // Libera o semáforo após montar
        } else {
            printf("Erro ao obter o semáforo para acesso ao cartão SD.\n");
        }


    }
}
