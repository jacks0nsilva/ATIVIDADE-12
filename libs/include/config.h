#ifndef CONFIG_H
#define CONFIG_H

#include <stdbool.h>

// Configurações do MPU6050
#define I2C_ADDR_MPU6050 0x68 // Endereço I2C do MPU6050
#define I2C_PORT_MPU6050 i2c0 // Identificador da porta I2C usada para o MPU6050
#define SDA_PIN_MPU6050 0 // Pino SDA do MPU6050
#define SCL_PIN_MPU6050 1 // Pino SCL do MPU6050

#define QUANTIDADE_AMOSTRAS 20 // Quantidade de amostras a serem capturadas
#define INTERVALO_AMOSTRAGEM_MS 500 // Intervalo de captura de dados em milissegundos


// Configurações do Display SSD1306
#define I2C_PORT_DISPLAY i2c1 // Identificador da porta I2C usada para o display
#define I2C_SDA_DISPLAY 14
#define I2C_SCL_DISPLAY 15
#define ADDRESS_DISPLAY 0x3C // Endereço I2C do display SSD1306

// Definicão dos periféricos
#define BOTAO_A 5
#define BOTAO_B 6
#define LED_VERDE 11
#define LED_AZUL 12
#define LED_VERMELHO 13
#define BUZZER_B 10

typedef struct
{
    int16_t numero_amostra;
    int16_t aceleracao[3];
    int16_t gyro[3];
    int16_t temp;
} imu_data_t;


typedef enum 
{
    PRONTO, // Sistema pronto para capturar dados
    CAPTURANDO, // Sistema capturando dados
    ERRO,       // Sistema em estado de erro
    MONTANDO_SD, // Sistema montando o cartão SD
    DESMONTANDO_SD, // Sistema desmontando o cartão SD
    GRAVANDO_SD, // Sistema gravando dados no cartão SD
    FEEDBACK // Feedback após gravação
} ESTADO_SISTEMA;

extern imu_data_t data_buffer[QUANTIDADE_AMOSTRAS]; // Buffer para armazenar os dados capturados
extern ESTADO_SISTEMA estado_sistema; // Variável global para armazenar o estado do sistema
extern volatile bool parar_captura; // Variável global para controlar a captura de dados
extern int quantidade_coletada; // Variável global para controlar a quantidade de dados coletados
extern volatile bool cartao_montado; // Variável global para controlar o estado do cartão SD
#endif // CONFIG_H