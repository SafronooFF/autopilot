#include "imu_lib.h"
#include "main.h"





//функция для упрощённой отправки конфигурации
void set_function_in(uint8_t write_register, uint8_t data_setting){ //страница 52 в datasheet: сначала адрес потом данные
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0);
	HAL_SPI_Transmit(&hspi1, (uint8_t[]){write_register, data_setting}, 2, 10);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1);

	HAL_Delay(10);
}

//https://byte-tools.com/en/binary/bin-to-hex/
void hello_imu(void){ //подумаь над функцией
	  uint8_t data_rx[8];
	  uint8_t who_am_i = 0x75 | READ_BIT_IMU;
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0); //cs low
	  HAL_SPI_Transmit(&hspi1, &who_am_i, 1, 10); //просим данные в регистр who_am_i он его не видит
	  HAL_SPI_Receive(&hspi1, &data_rx, 8, 10);
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1); // cs hight
}

int16_t get_data_accel_axis(uint8_t upper_register_accel_axis){
	uint8_t data_accel = upper_register_accel_axis | READ_BIT_IMU;
	uint8_t data_accel_buff[2];
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0);
	HAL_SPI_Transmit(&hspi1, &data_accel, 1, 10);
	HAL_SPI_Receive(&hspi1, data_accel_buff, 2, 10);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1);

	return (int16_t)((data_accel_buff[0] << 8) | data_accel_buff[1]);
}

int16_t get_data_gyro_axis(uint8_t upper_register_gyro_axis){
	uint8_t data_gyro = upper_register_gyro_axis | READ_BIT_IMU;
	uint8_t data_gyro_buff[2];
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0);
	HAL_SPI_Transmit(&hspi1, &data_gyro, 1, 10);
	HAL_SPI_Receive(&hspi1, data_gyro_buff, 2, 10);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1);

	return (int16_t)((data_gyro_buff[0] << 8) | data_gyro_buff[1]);
}

void setup_function_imu(void){
	//DEVICE_CONFIG
	set_function_in(DEVICE_CONFIG_REG, DEVICE_CONFIG_DATA);
	//INTF_CONFIG0
	set_function_in(INTF_CONFIG0_REG, INTF_CONFIG0_DATA);
	//INTF_CONFIG1
	set_function_in(INTF_CONFIG1_REG, INTF_CONFIG1_DATA);
	//PWR_MGMT0
	set_function_in(PWR_MGMT0_REG, PWR_MGMT0_DATA);
	//ACCEL_CONFIG0
	set_function_in(ACCEL_CONFIG0_REG, ACCEL_CONFIG0_DATA);
	//GYRO_CONFIG0
	set_function_in(GYRO_CONFIG0_REG, GYRO_CONFIG0_DATA);
}

void update_accel_data(AccelData *data){
	data -> x = ((float)(get_data_accel_axis(AXIS_ACCEL_X)/ACCEL_SENS_SCALE))*G;
	data -> y = ((float)(get_data_accel_axis(AXIS_ACCEL_Y)/ACCEL_SENS_SCALE))*G;
	data -> z = ((float)(get_data_accel_axis(AXIS_ACCEL_Z)/ACCEL_SENS_SCALE))*G;
}

void update_gyro_data(GyroData *data){
	data -> x = ((float)(get_data_accel_axis(AXIS_ACCEL_X)/GYRO_SENS_SCALE));
	data -> y = ((float)(get_data_accel_axis(AXIS_ACCEL_Y)/GYRO_SENS_SCALE));
	data -> z = ((float)(get_data_accel_axis(AXIS_ACCEL_Z)/GYRO_SENS_SCALE));
}
/*
void update_accel_data(GyroData *data){
	data -> x = get_data_gyro_axis(AXIS_GYRO_X);
	data -> y = get_data_gyro_axis(AXIS_GYRO_Y);
	data -> z = get_data_gyro_axis(AXIS_GYRO_Z);
}*/
