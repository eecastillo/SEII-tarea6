/*
 * BMI160.c
 *
 *  Created on: Oct 15, 2020
 *      Author: eduar
 */
#include "BMI160.h"

static freertos_i2c_config_t bmi160_config;

freertos_i2c_flag_t  BMI160_init(void)
{
	freertos_i2c_flag_t status = freertos_i2c_fail;
	bmi160_config.baudrate = BAUDRATE;
	bmi160_config.i2c_number = freertos_i2c_0;
	bmi160_config.pin_mux = kPORT_MuxAlt5;
	bmi160_config.port = freertos_i2c_portE;
	bmi160_config.scl_pin = I2C_SCL_PIN;
	bmi160_config.sda_pin = I2C_SDA_PIN;

	status = freertos_i2c_init(bmi160_config);
	if(freertos_i2c_sucess == status)
	{
		status = freertos_i2c_fail;
		uint8_t acc_normal = ACC_NORMAL_MODE;
		uint8_t gyro_normal = GYR_NORMAL_MODE;
		status = freertos_i2c_send(bmi160_config.i2c_number, &acc_normal , 1, SLAVE_ADRESS, CMD_REGISTER, 1);
		vTaskDelay(pdMS_TO_TICKS(I2C_DELAY));
		if(freertos_i2c_fail != status)
		{
			status = freertos_i2c_send(bmi160_config.i2c_number, &gyro_normal , 1, SLAVE_ADRESS, CMD_REGISTER, 1);
		}
	}
	return status;
}
bmi160_raw_data_t get_accelerometer(void)
{

	bmi160_raw_data_t acc_data;
	uint8_t lsb = 0;
	uint8_t msb = 0;

	//Get X_ACC data
	freertos_i2c_receive(bmi160_config.i2c_number, &lsb, 1, SLAVE_ADRESS, ACC_X_L, 1);
	freertos_i2c_receive(bmi160_config.i2c_number, &msb, 1, SLAVE_ADRESS, ACC_X_H, 1);
	acc_data.x = (msb << 8) + lsb;

	//Get Y_ACC data
	freertos_i2c_receive(bmi160_config.i2c_number, &lsb, 1, SLAVE_ADRESS, ACC_Y_L, 1);
	freertos_i2c_receive(bmi160_config.i2c_number, &msb, 1, SLAVE_ADRESS, ACC_Y_H, 1);
	acc_data.y = (msb << 8) + lsb;

	//Get Z_ACC data
	freertos_i2c_receive(bmi160_config.i2c_number, &lsb, 1, SLAVE_ADRESS, ACC_Z_L, 1);
	freertos_i2c_receive(bmi160_config.i2c_number, &msb, 1, SLAVE_ADRESS, ACC_Z_H, 1);
	acc_data.z = (msb << 8) + lsb;

	return acc_data;

}

bmi160_raw_data_t get_giroscope(void)
{
	bmi160_raw_data_t gyr_data;
	uint8_t lsb = 0;
	uint8_t msb = 0;

	//Get X_GYR data
	freertos_i2c_receive(bmi160_config.i2c_number, &lsb, 1, SLAVE_ADRESS, GYR_X_L, 1);
	freertos_i2c_receive(bmi160_config.i2c_number, &msb, 1, SLAVE_ADRESS, GYR_X_H, 1);
	gyr_data.x = (msb << 8) + lsb;

	//Get Y_GYR data
	freertos_i2c_receive(bmi160_config.i2c_number, &lsb, 1, SLAVE_ADRESS, GYR_Y_L, 1);
	freertos_i2c_receive(bmi160_config.i2c_number, &msb, 1, SLAVE_ADRESS, GYR_Y_H, 1);
	gyr_data.y = (msb << 8) + lsb;

	//Get Z_GYR data
	freertos_i2c_receive(bmi160_config.i2c_number, &lsb, 1, SLAVE_ADRESS, GYR_Z_L, 1);
	freertos_i2c_receive(bmi160_config.i2c_number, &msb, 1, SLAVE_ADRESS, GYR_Z_H, 1);
	gyr_data.z = (msb << 8) + lsb;

	return gyr_data;	
}


