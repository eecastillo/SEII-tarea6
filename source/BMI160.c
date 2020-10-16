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
	acc_data.x = (msb << 8) + lsb;

	//Get Y_GYR data
	freertos_i2c_receive(bmi160_config.i2c_number, &lsb, 1, SLAVE_ADRESS, GYR_Y_L, 1);
	freertos_i2c_receive(bmi160_config.i2c_number, &msb, 1, SLAVE_ADRESS, GYR_Y_H, 1);
	acc_data.y = (msb << 8) + lsb;

	//Get Z_GYR data
	freertos_i2c_receive(bmi160_config.i2c_number, &lsb, 1, SLAVE_ADRESS, GYR_Z_L, 1);
	freertos_i2c_receive(bmi160_config.i2c_number, &msb, 1, SLAVE_ADRESS, GYR_Z_H, 1);
	acc_data.z = (msb << 8) + lsb;

	return gyr_data;	
}


