#ifndef MPU6050_H
#define MPU6050_H

#include <stdint.h>

void mpu6050_reset(); // Função para resetar o MPU6050
void mpu6050_read_raw(int16_t accel[3], int16_t gyro[3], int16_t *temp); // Função para ler os dados brutos do MPU6050

#endif 