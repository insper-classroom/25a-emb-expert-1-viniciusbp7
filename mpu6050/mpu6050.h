#ifndef MPU6050_H
#define MPU6050_H

#include "hardware/i2c.h"
#include "pico/stdlib.h"

#define MPU6050_ADDR 0x68

typedef struct imu6050 {
    i2c_inst_t *i2c;
    int pin_sda;
    int pin_scl;
    int acc_scale;
} imu_c;

void mpu6050_set_config(imu_c *config, i2c_inst_t *i2c, int pin_sda, int pin_scl, int acc_scale);
int mpu6050_init(imu_c config);
int mpu6050_reset(imu_c config);
int mpu6050_read_acc(imu_c config, int16_t accel[3]);
int mpu6050_read_gyro(imu_c config, int16_t gyro[3]);
int mpu6050_read_temp(imu_c config, int16_t *temp);

#endif
