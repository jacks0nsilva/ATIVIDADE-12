#include <stdio.h>
#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "tasks.h"
#include "config.h"

volatile uint32_t last_time = 0; // Variável global para armazenar o último tempo
volatile bool parar_captura = false; // Variável global para controlar a captura de dados
void gpio_irq_handler(uint gpio, uint32_t events); // Declaração da função de interrupção
ESTADO_SISTEMA estado_sistema = PRONTO; // Inicializa o estado do sistema
int quantidade_coletada = 0; // Variável global para controlar a quantidade de dados coletados

TaskHandle_t xHandleCaptura = NULL; // Handle para a tarefa de captura de dados 

int main()
{
    stdio_init_all();

    gpio_init(BOTAO_A);
    gpio_set_dir(BOTAO_A, GPIO_IN);
    gpio_pull_up(BOTAO_A); // Configura o pino do botão A com pull-up

    gpio_set_irq_enabled_with_callback(BOTAO_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler); // Configura a interrupção para o botão A

    // Criação das tarefas 
    xTaskCreate(vTaskCapturarDados, "Capturar Dados", configMINIMAL_STACK_SIZE, NULL, 1, &xHandleCaptura);
    // Início do scheduler
    vTaskStartScheduler();
    panic_unsupported(); 
}

void gpio_irq_handler(uint gpio, uint32_t events) {
    uint32_t current_time = to_us_since_boot(get_absolute_time());

    if(current_time - last_time > 200000) { 
        last_time = current_time; // Atualiza o último tempo registrado
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;

        if(gpio == BOTAO_A) {
            if (estado_sistema == PRONTO) {
                vTaskNotifyGiveFromISR(xHandleCaptura, &xHigherPriorityTaskWoken);
            } else if(estado_sistema == CAPTURANDO) {
                parar_captura = true;
            }
            
        } else if(gpio == BOTAO_B) {

        }
    }
}