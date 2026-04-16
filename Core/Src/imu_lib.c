#include "imu_lib.h"

//функция для упрощённой отправки конфигурации
void set_function_in(uint8_t write_register, uint8_t data_setting){ //страница 52 в datasheet: сначала адрес потом данные
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0);
	HAL_SPI_Transmit(&hspi1, (uint8_t[]){write_register, data_setting}, 2, 10);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1);

	HAL_Delay(10);
}

//https://byte-tools.com/en/binary/bin-to-hex/
void hello_imu(void){ //подумаь над функцией
	  uint8_t data_rx;
	  uint8_t who_am_i = 0x75 | READ_BIT_IMU;
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0); //cs low
	  HAL_SPI_Transmit(&hspi1, &who_am_i, 1, 10); //просим данные в регистр who_am_i он его не видит
	  HAL_SPI_Receive(&hspi1, &data_rx, 1, 10);
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1); // cs hight
}

void IMU_data_update(void){
	if (hello_imu()==)
	for (int i = 0; i!=6; i++){
		reg_axis_AccelGyro[i]  |= READ_BIT_IMU;
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0);
		HAL_SPI_Transmit(&hspi1, &data_accel, 1, 10);
		HAL_SPI_Receive(&hspi1, data_accel_buff, 2, 10);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1);
		switch (i){
		case 0:
			data -> x_acc = ((float)((int16_t)((&data_accel_buff[i] << 8) | &data_accel_buff[i+1])))*G;//m/s^2
			break;
		case 1:
			data -> y_acc = ((float)((int16_t)((&data_accel_buff[i] << 8) | &data_accel_buff[i+1])))*G;//m/s^2
			break;
		case 2:
			data -> z_acc = ((float)((int16_t)((&data_accel_buff[i] << 8) | &data_accel_buff[i+1])))*G;//m/s^2
			break;
		case 3:
			data -> gx= ((float)((int16_t)((&data_gyro_buff[i] << 8) | &data_gyro_buff[i+1])))*G;//radian
			break;
		case 4:
			data -> gy= ((float)((int16_t)((&data_gyro_buff[i] << 8) | &data_gyro_buff[i+1])))*G;//radian
			break;
		case 5:
			data -> gz= ((float)((int16_t)((&data_gyro_buff[i] << 8) | &data_gyro_buff[i+1])))*G;//radian
			break;
		}
	}
}

int16_t get_data_gyro_axis_raw(uint8_t upper_register_gyro_axis){
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

