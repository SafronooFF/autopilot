#include "imu_lib.h"
#include "main.h"

extern SPI_HandleTypeDef hspi1;

//https://byte-tools.com/en/binary/bin-to-hex/
void hello_imu(void){
	  uint8_t data_rx[8];
	  uint8_t who_am_i = 0x75 | 0x80; // 0x80 - маска с приёмом данных читать даташит !!!!!
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0); //cs low
	  HAL_SPI_Transmit(&hspi1, &who_am_i, 1, 10); //просим данные в регистр who_am_i он его не видит
	  HAL_SPI_Receive(&hspi1, &data_rx, 8, 10);
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1); // cs hight
}

int16_t get_data_accel_axis(uint8_t upper_register_accel_axis){
	uint8_t data_accel = upper_register_accel_axis | 0x80;
	uint8_t data_accel_buff[2];
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0);
	HAL_SPI_Transmit(&hspi1, &data_accel, 1, 10);
	HAL_SPI_Receive(&hspi1, data_accel_buff, 2, 10);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1);

	return (int16_t)((data_accel_buff[0] << 8) | data_accel_buff[1]);
}

int16_t get_data_gyro_axis(uint8_t upper_register_gyro_axis){
	uint8_t data_gyro = upper_register_gyro_axis | 0x80;
	uint8_t data_gyro_buff[2];
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0);
	HAL_SPI_Transmit(&hspi1, &data_gyro, 1, 10);
	HAL_SPI_Receive(&hspi1, data_gyro_buff, 2, 10);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1);

	return (int16_t)((data_gyro_buff[0] << 8) | data_gyro_buff[1]);
}

void setup_function_imu(void){
	uint8_t tx_buf[2] = {0}; //страница 52 в datasheet: сначала адрес потом данные

	//DEVICE_CONFIG
	tx_buf[0] = 0x11;
	tx_buf[1] = 0x00;

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0);
	HAL_SPI_Transmit(&hspi1, &tx_buf, 2, 10);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1);

	HAL_Delay(10);

	//INTF_CONFIG0
	tx_buf[0] = 0x4C;
	tx_buf[1] = 0xF3;

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0);
	HAL_SPI_Transmit(&hspi1, &tx_buf, 2, 10);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1);

	HAL_Delay(10);

	//INTF_CONFIG1
	tx_buf[0] = 0x4D;
	tx_buf[1] = 0x99;

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0);
	HAL_SPI_Transmit(&hspi1, &tx_buf, 2, 10);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1);

	HAL_Delay(10);

	//PWR_MGMT0

	tx_buf[0] = 0x4E;
	tx_buf[1] = 0xF;

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0);
	HAL_SPI_Transmit(&hspi1, &tx_buf, 2, 10);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1);

	HAL_Delay(10);

	// ACCEL_CONFIG0
	//uint8_t accel_config0 = 0x02; // +-q16g и 16kHz
	//uint8_t reg_data_accel = 0x50;
	tx_buf[0] = 0x50; //регистр записи
	tx_buf[1] = 0x02; //выставленные данные

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0);
	HAL_SPI_Transmit(&hspi1, &tx_buf, 2, 10);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1);

	HAL_Delay(10);

	// GYRO_CONFIG0
	//uint8_t gyro_config0 = 0x02; // +-2000dps и 16kHz
	//uint8_t reg_data_gyro = 0x4F;
	tx_buf[0] = 0x4F;
	tx_buf[1] = 0x02;

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0);
	HAL_SPI_Transmit(&hspi1, &tx_buf, 2, 10);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1);

	HAL_Delay(10);

}
