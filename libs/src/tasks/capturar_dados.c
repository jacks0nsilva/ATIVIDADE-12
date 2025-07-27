#include <stdio.h>
#include <pico/stdlib.h>
#include "FreeRTOS.h"
#include "task.h"
#include "tasks.h"
#include "hardware/i2c.h"
#include "config.h"
#include "mpu6050.h"
#include "pico/binary_info.h"


void vTaskCapturarDados(void *params){

     
    

    i2c_init(I2C_PORT_MPU6050, 400 * 1000); // Inicializa o I2C a 400kHz
    gpio_set_function(SDA_PIN_MPU6050, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN_MPU6050, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN_MPU6050);
    gpio_pull_up(SCL_PIN_MPU6050);

    // Declara os pinos como I2C na Binary Info para depuração
    bi_decl(bi_2pins_with_func(SDA_PIN_MPU6050, SCL_PIN_MPU6050, GPIO_FUNC_I2C));
    mpu6050_reset();

    int16_t aceleracao[3], gyro[3], temp;  // Variáveis para armazenar os dados lidos do MPU6050

    while (true) {
        
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY); // Espera por notificação para iniciar a captura
        quantidade_coletada = 0; // Variável para controlar a quantidade de dados coletados caso a captura seja interrompida
        estado_sistema = CAPTURANDO; // Atualiza o estado do sistema para capturando
        for (int i = 0; i < QUANTIDADE_AMOSTRAS; i++)
        {
                mpu6050_read_raw(aceleracao, gyro, &temp);
                data_buffer[i].numero_amostra = i+1;
                data_buffer[i].aceleracao[0] = aceleracao[0];
                data_buffer[i].aceleracao[1] = aceleracao[1];
                data_buffer[i].aceleracao[2] = aceleracao[2];
                data_buffer[i].gyro[0] = gyro[0];
                data_buffer[i].gyro[1] = gyro[1];
                data_buffer[i].gyro[2] = gyro[2];
                data_buffer[i].temp = temp;
                vTaskDelay(pdMS_TO_TICKS(INTERVALO_AMOSTRAGEM_MS)); // Delay for INTERVALO_AMOSTRAGEM_MS milliseconds
                quantidade_coletada++; // Incrementa a quantidade de amostras coletadas
                if(parar_captura) break; // Verifica se a captura deve ser interrompida
        }
        if(cartao_montado){
            xTaskNotifyGive(xHandleGravar);
        } else {
            printf("Cartão SD não montado. Não é possível gravar dados.\n");
        }

        /*
        printf("Amostras capturadas:\n");
        for (int i = 0; i < quantidade_coletada; i++)
        {
            printf("Amostra %d: Aceleracao: X=%d, Y=%d, Z=%d | Giroscopio: X=%d, Y=%d, Z=%d | Temperatura: %d\n",
                   data_buffer[i].numero_amostra,
                   data_buffer[i].aceleracao[0], data_buffer[i].aceleracao[1], data_buffer[i].aceleracao[2],
                   data_buffer[i].gyro[0], data_buffer[i].gyro[1], data_buffer[i].gyro[2],
                   data_buffer[i].temp);
        }*/
         // Notifica a tarefa de gravação de dados
        parar_captura = false; // Reseta a variável de controle de captura
        vTaskDelay(pdMS_TO_TICKS(2000)); // Delay for 2000 ms before the next capture
    }
}