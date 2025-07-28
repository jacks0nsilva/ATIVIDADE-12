#include "tasks.h"
#include "FreeRTOS.h"
#include "task.h"
#include "pico/stdlib.h"
#include "config.h"



void vTaskLeds(void *params) {

    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERDE, GPIO_OUT);
    gpio_init(LED_AZUL);
    gpio_set_dir(LED_AZUL, GPIO_OUT);
    gpio_init(LED_VERMELHO);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    while (true) {
        switch (estado_sistema)
        {
        case PRONTO:
        // VERDE - Sistema pronto
            gpio_put(LED_VERDE, true);
            gpio_put(LED_AZUL, false);
            gpio_put(LED_VERMELHO, false);
            break;
        case CAPTURANDO:
        // VERMELHO - Sistema capturando dados
            gpio_put(LED_VERDE, false);
            gpio_put(LED_VERMELHO, true);
            gpio_put(LED_AZUL, false);
            break;
        case ERRO:
        // ROXO - Sistema em estado de erro
            gpio_put(LED_VERDE, false);
            gpio_put(LED_AZUL, true);
            gpio_put(LED_VERMELHO, true);
            break;
        case MONTANDO_SD:
        case DESMONTANDO_SD:
            // AMARELO - Sistema montando/desmontando o cartão SD
            gpio_put(LED_VERDE, true);
            gpio_put(LED_AZUL, false);
            gpio_put(LED_VERMELHO, true);
            break;
        case GRAVANDO_SD:
            // AZUL - Sistema gravando dados no cartão SD
            gpio_put(LED_VERDE, false);
            gpio_put(LED_AZUL, true);
            gpio_put(LED_VERMELHO, false);
            break;
        case FEEDBACK:
            // BRANCO - Feedback após gravação
            gpio_put(LED_VERDE, true);
            gpio_put(LED_AZUL, true);
            gpio_put(LED_VERMELHO, true);
            break;
        default:
            // Desliga todos os LEDs se o estado não for reconhecido
            gpio_put(LED_VERDE, false);
            gpio_put(LED_AZUL, false);
            gpio_put(LED_VERMELHO, false);
            break;
        }
        vTaskDelay(pdMS_TO_TICKS(50)); // Delay de 50 ms para evitar sobrecarga
    }
}
