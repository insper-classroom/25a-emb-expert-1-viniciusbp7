/*
 * LED blink with FreeRTOS
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "mpu6050.h"

int main() {
    stdio_init_all();
    imu_c imu;

    mpu6050_set_config(&imu, i2c0, 4, 5, 0);
    if (!mpu6050_init(imu)) {
        printf("Falha ao iniciar MPU6050!\n");
        return 1;
    }

    int16_t acc[3], gyro[3], temp;
    while (true) {
        if (mpu6050_read_acc(imu, acc)) {
            printf("Acceleration: X=%d Y=%d Z=%d\n", acc[0], acc[1], acc[2]);
        }
        if (mpu6050_read_gyro(imu, gyro)) {
            printf("Gyro: X=%d Y=%d Z=%d\n", gyro[0], gyro[1], gyro[2]);
        }
        if (mpu6050_read_temp(imu, &temp)) {
            printf("Temp: %d\n", temp);
        }
        sleep_ms(1000);
    }
}
