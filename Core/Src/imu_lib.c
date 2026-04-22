#include "imu_lib.h"

IMU_Data imu;

//функция для упрощённой отправки конфигурации
void set_function_in(uint8_t write_register, uint8_t data_setting){ //страница 52 в datasheet: сначала адрес потом данные
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0);
	HAL_SPI_Transmit(&hspi1, (uint8_t[]){write_register, data_setting}, 2, 10);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1);

	HAL_Delay(10);
}

//https://byte-tools.com/en/binary/bin-to-hex/
uint16_t hello_imu(void){ //подумаь над функцией
	  uint8_t data_rx;
	  uint8_t who_am_i = 0x75 | READ_BIT_IMU;
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0); //cs low
	  HAL_SPI_Transmit(&hspi1, &who_am_i, 1, 10); //просим данные в регистр who_am_i он его не видит
	  HAL_SPI_Receive(&hspi1, &data_rx, 1, 10);
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1); // cs hight
	  return data_rx;
}
uint8_t rx_buff[12] = {0};
int16_t raw_data[6] = {0};
HAL_StatusTypeDef IMU_data_update(void){

		uint8_t reg = AXIS_ACCEL_X  | READ_BIT_IMU;
		HAL_StatusTypeDef state = HAL_OK;
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0);
		state |= HAL_SPI_Transmit(&hspi1, &reg, 1, 10);
		state |= HAL_SPI_Receive(&hspi1, rx_buff, 12, 100);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1);
	    for (int i = 0; i < 6; i++) {
	        raw_data[i] = (int16_t)((rx_buff[i * 2] << 8) | rx_buff[i * 2 + 1]);
	    }
		imu.ax = ((int16_t)(raw_data[0]))*G/ACCEL_SENS_SCALE;//m/s^2
		imu.ay = ((int16_t)(raw_data[1]))*G/ACCEL_SENS_SCALE;//m/s^2
		imu.az = ((int16_t)(raw_data[2]))*G/ACCEL_SENS_SCALE;//m/s^2

		imu.gx = ((int16_t)(raw_data[3]))*(PI/180.0F)/GYRO_SENS_SCALE;//radian
		imu.gy = ((int16_t)(raw_data[4]))*(PI/180.0F)/GYRO_SENS_SCALE;//radian
		imu.gz = ((int16_t)(raw_data[5]))*(PI/180.0F)/GYRO_SENS_SCALE;//radian

		return state;

}


void setup_function_imu(void){
	//if (hello_imu()==0x47){
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
	//}
	//else{
	//	return;
	//}
}

