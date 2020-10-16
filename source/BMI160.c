/*
 * BMI160.c
 *
 *  Created on: Oct 15, 2020
 *      Author: eduar
 */
#include "BMI160.h"

freertos_i2c_flag_t  BMI160_init(void)
{
	freertos_i2c_config_t bmi160_config;
	freertos_i2c_flag_t status = freertos_i2c_fail;
	bmi160_config.baudrate = BAUDRATE;
	bmi160_config.i2c_number = freertos_i2c_0;
}
bmi160_raw_data_t get_accelerometer(void)
{
}

bmi160_raw_data_t get_giroscope(void)
{
}


