#ifndef CONFIG_H
#define CONFIG_H

// Configurações do MPU6050
#define I2C_ADDR_MPU6050 0x68 // Endereço I2C do MPU6050
#define I2C_PORT_MPU6050 i2c0 // Identificador da porta I2C usada para o MPU6050
#define SDA_PIN_MPU6050 0 // Pino SDA do MPU6050
#define SCL_PIN_MPU6050 1 // Pino SCL do MPU6050

#define QUANTIDADE_AMOSTRAS 20 // Quantidade de amostras a serem capturadas
#define INTERVALO_AMOSTRAGEM_MS 500 // Intervalo de captura de dados em milissegundos


typedef struct
{
    int16_t numero_amostra;
    int16_t aceleracao[3];
    int16_t gyro[3];
    int16_t temp;
} imu_data_t;


#endif // CONFIG_H