#include "main.h"
#include <stdint.h>

#ifndef IMU_LIB_H_
#define IMU_LIB_H_

extern SPI_HandleTypeDef hspi1;
extern UART_HandleTypeDef huart3;

#define READ_BIT_IMU  	      0x80; // 0x80 - маска с приёмом данных читать даташит !!!!!
//Упорядочить как в datasheet

//DEVICE_CONFIG
#define DEVICE_CONFIG_REG     0x11
#define DEVICE_CONFIG_DATA    0x00
//INTF_CONFIG0
#define INTF_CONFIG0_REG      0x4C
#define INTF_CONFIG0_DATA     0xF3
//INTF_CONFIG1
#define INTF_CONFIG1_REG      0x4D
#define INTF_CONFIG1_DATA     0x99
//PWR_MGMT0
#define PWR_MGMT0_REG         0x4E
#define PWR_MGMT0_DATA        0xF
//ACCEL_CONFIG0
#define ACCEL_CONFIG0_REG     0x50
#define ACCEL_CONFIG0_DATA    0x02 // +-q16g и 16kHz
//GYRO_CONFIG0
#define GYRO_CONFIG0_REG      0x4F
#define GYRO_CONFIG0_DATA     0x02 // +-2000dps и 16kHz

//axis accel
#define AXIS_ACCEL_X          0x1F //axis x
#define AXIS_ACCEL_Y          0x21 //axis y
#define AXIS_ACCEL_Z          0x23 //axis z

//axis accel
#define AXIS_GYRO_X           0x25 //axis x
#define AXIS_GYRO_Y           0x27 //axis y
#define AXIS_GYRO_Z           0x29 //axis z


//3.2 ACCELEROMETER SPECIFICATIONS/Sensitivity Scale Factor
#define ACCEL_SENS_SCALE      2048.0f
#define G                     9.80665f

//3.1 GYROSCOPE SPECIFICATIONS
#define GYRO_SENS_SCALE       16.4f
#define PI                    3.14159265358979323846f

typedef struct {
	int16_t ax, ay, az;
	int16_t gx, gy, gz;
} IMU_Data;

extern IMU_Data imu;

//uint8_t reg_axis_AccelGyro[5] = {AXIS_ACCEL_X, AXIS_ACCEL_Y, AXIS_ACCEL_Z, AXIS_GYRO_X, AXIS_GYRO_Y, AXIS_GYRO_Z}; //регистры для получения данных определённых осей
//uint8_t data_accel_buff[5]; //буфер для записи полученных данных акселерометра
//uint8_t data_gyro_buff[5]; // буфер для записи полученных данных гироскоп

HAL_StatusTypeDef IMU_data_update(void);//Функция получения сырых данных и их преобразование
void setup_function_imu(void); //фунция конфигурации





#endif
