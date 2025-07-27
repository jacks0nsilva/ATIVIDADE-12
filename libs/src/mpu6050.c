#include "mpu6050.h"
#include "config.h"
#include "hardware/i2c.h" 
#include "FreeRTOS.h"
#include "task.h"


void mpu6050_reset() {
    // Dois bytes para reset: primeiro o registrador, segundo o dado
    // Existem muitas outras opções de configuração do dispositivo, se necessário
    uint8_t buf[] = {0x6B, 0x80};
    i2c_write_blocking(I2C_PORT_MPU6050, I2C_ADDR_MPU6050, buf, 2, false);
    vTaskDelay(pdMS_TO_TICKS(100)); // Aguarda o reset e estabilização do dispositivo

    // Sai do modo sleep (registrador 0x6B, valor 0x00)
    buf[1] = 0x00; // Sai do sleep escrevendo 0x00 no registrador 0x6B
    i2c_write_blocking(I2C_PORT_MPU6050, I2C_ADDR_MPU6050, buf, 2, false);
    vTaskDelay(pdMS_TO_TICKS(10)); // Aguarda a estabilização
}

// Função para ler dados crus (raw) do MPU6050: aceleração, giroscópio e temperatura
void mpu6050_read_raw(int16_t accel[3], int16_t gyro[3], int16_t *temp) {
    // Para este dispositivo, enviamos o endereço do registrador a ser lido
    // e depois lemos os dados. O registrador auto-incrementa, então basta enviar o inicial.

    uint8_t buffer[6];

    // Lê os dados de aceleração a partir do registrador 0x3B (6 bytes)
    uint8_t val = 0x3B;
    i2c_write_blocking(I2C_PORT_MPU6050, I2C_ADDR_MPU6050, &val, 1, true); // true mantém o controle do barramento
    i2c_read_blocking(I2C_PORT_MPU6050, I2C_ADDR_MPU6050, buffer, 6, false);

    for (int i = 0; i < 3; i++)
    {
        accel[i] = (buffer[i * 2] << 8 | buffer[(i * 2) + 1]);
    }

    // Lê dados do giroscópio a partir do registrador 0x43 (6 bytes)
    // O registrador auto-incrementa a cada leitura
    val = 0x43;
    i2c_write_blocking(I2C_PORT_MPU6050, I2C_ADDR_MPU6050, &val, 1, true);
    i2c_read_blocking(I2C_PORT_MPU6050, I2C_ADDR_MPU6050, buffer, 6, false);

    for (int i = 0; i < 3; i++)
    {
        gyro[i] = (buffer[i * 2] << 8 | buffer[(i * 2) + 1]);
    }

    // Lê temperatura a partir do registrador 0x41 (2 bytes)
    val = 0x41;
    i2c_write_blocking(I2C_PORT_MPU6050, I2C_ADDR_MPU6050, &val, 1, true);
    i2c_read_blocking(I2C_PORT_MPU6050, I2C_ADDR_MPU6050, buffer, 2, false);

    *temp = buffer[0] << 8 | buffer[1];
}
