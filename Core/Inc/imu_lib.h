#ifndef IMU_LIB_H_
#define IMU_LIB_H_
#include "stm32f7xx_hal.h"
#include <stdint.h>

void hello_imu(void);
void setup_function_imu(void);
int16_t get_data_accel_axis(uint8_t upper_register_accel_axis);
int16_t get_data_gyro_axis(uint8_t upper_register_gyro_axis);
void setup_function_imu(void);



#endif
