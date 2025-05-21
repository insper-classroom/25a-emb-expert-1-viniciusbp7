#include "mpu6050.h"

void mpu6050_set_config(imu_c *config, i2c_inst_t *i2c, int pin_sda, int pin_scl, int acc_scale) {
    config->i2c = i2c;
    config->pin_sda = pin_sda;
    config->pin_scl = pin_scl;
    config->acc_scale = acc_scale;
}

int mpu6050_init(imu_c config) {
    i2c_init(config.i2c, 400 * 1000);
    gpio_set_function(config.pin_sda, GPIO_FUNC_I2C);
    gpio_set_function(config.pin_scl, GPIO_FUNC_I2C);
    gpio_pull_up(config.pin_sda);
    gpio_pull_up(config.pin_scl);
    sleep_ms(100);

    uint8_t buf[] = {0x6B, 0x00}; 
    return i2c_write_blocking(config.i2c, MPU6050_ADDR, buf, 2, false) == 2 ? 1 : 0;
}

int mpu6050_reset(imu_c config) {
    uint8_t buf[] = {0x6B, 0x80}; 
    return i2c_write_blocking(config.i2c, MPU6050_ADDR, buf, 2, false) == 2 ? 1 : 0;
}

int mpu6050_read_acc(imu_c config, int16_t accel[3]) {
    uint8_t reg = 0x3B;
    uint8_t data[6];
    if (i2c_write_blocking(config.i2c, MPU6050_ADDR, &reg, 1, true) != 1) return 0;
    if (i2c_read_blocking(config.i2c, MPU6050_ADDR, data, 6, false) != 6) return 0;

    for (int i = 0; i < 3; i++) {
        accel[i] = (data[2 * i] << 8) | data[2 * i + 1];
    }
    return 1;
}

int mpu6050_read_gyro(imu_c config, int16_t gyro[3]) {
    uint8_t reg = 0x43;
    uint8_t data[6];
    if (i2c_write_blocking(config.i2c, MPU6050_ADDR, &reg, 1, true) != 1) return 0;
    if (i2c_read_blocking(config.i2c, MPU6050_ADDR, data, 6, false) != 6) return 0;

    for (int i = 0; i < 3; i++) {
        gyro[i] = (data[2 * i] << 8) | data[2 * i + 1];
    }
    return 1;
}

int mpu6050_read_temp(imu_c config, int16_t *temp) {
    uint8_t reg = 0x41;
    uint8_t data[2];
    if (i2c_write_blocking(config.i2c, MPU6050_ADDR, &reg, 1, true) != 1) return 0;
    if (i2c_read_blocking(config.i2c, MPU6050_ADDR, data, 2, false) != 2) return 0;

    *temp = (data[0] << 8) | data[1];
    return 1;
}
