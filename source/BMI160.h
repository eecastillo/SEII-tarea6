/*
 * BMI160.h
 *
 *  Created on: Oct 15, 2020
 *      Author: eduar
 */

#ifndef BMI160_H_
#define BMI160_H_

#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

#define BAUDRATE 115200

typedef struct
{
	int16_t x;
	int16_t y;
	int16_t z;
} bmi160_raw_data_t;

freertos_i2c_flag_t  BMI160_init(void);
bmi160_raw_data_t get_accelerometer(void);
bmi160_raw_data_t get_giroscope(void);

#endif /* BMI160_H_ */
