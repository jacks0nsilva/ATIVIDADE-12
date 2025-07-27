#include <stdio.h>
#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "tasks.h"
#include "config.h"

volatile uint32_t last_time = 0; // Variável global para armazenar o último tempo
volatile bool parar_captura = false; // Variável global para controlar a captura de dados
volatile bool cartao_montado = false; // Variável global para controlar o estado do cartão SD
void gpio_irq_handler(uint gpio, uint32_t events); // Declaração da função de interrupção
ESTADO_SISTEMA estado_sistema = PRONTO; // Inicializa o estado do sistema
int quantidade_coletada = 0; // Variável global para controlar a quantidade de dados coletados

TaskHandle_t xHandleCaptura = NULL; // Handle para a tarefa de captura de dados
TaskHandle_t xHandleGravar = NULL; // Handle para a tarefa de gravar dados no cartão SD
TaskHandle_t xHandleMontarDesmontar = NULL; // Handle para a tarefa de montar/desmontar o cartão SD 
SemaphoreHandle_t xMutexCartaoSD; // Semáforo para acesso ao cartão SD

int main()
{
    stdio_init_all();

    gpio_init(BOTAO_A);
    gpio_set_dir(BOTAO_A, GPIO_IN);
    gpio_pull_up(BOTAO_A); // Configura o pino do botão A com pull-up

    gpio_init(BOTAO_B);
    gpio_set_dir(BOTAO_B, GPIO_IN);
    gpio_pull_up(BOTAO_B); // Configura o pino do botão B com pull-up


    gpio_set_irq_enabled_with_callback(BOTAO_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler); // Configura a interrupção para o botão A
    gpio_set_irq_enabled(BOTAO_B, GPIO_IRQ_EDGE_FALL, true); // Configura a interrupção para o botão B

    xMutexCartaoSD = xSemaphoreCreateMutex(); // Criação do semáforo para acesso ao cartão SD

    // Criação das tarefas 
    xTaskCreate(vTaskCapturarDados, "Capturar Dados", configMINIMAL_STACK_SIZE, NULL, 1, &xHandleCaptura);
    xTaskCreate(vTaskMontarDesmontarSD, "Montar/Desmontar SD", configMINIMAL_STACK_SIZE, NULL, 1, &xHandleMontarDesmontar);
    xTaskCreate(vTaskGravarDados, "Gravar Dados", configMINIMAL_STACK_SIZE, NULL, 1, &xHandleGravar);
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
                vTaskNotifyGiveFromISR(xHandleMontarDesmontar, &xHigherPriorityTaskWoken);
        }
    }
}