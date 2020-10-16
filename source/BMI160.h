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

typedef struct
{
	int16_t x;
	int16_t y;
	int16_t z;
} bmi160_raw_data_t;

void BMI160_init(void *pvParameters);
void BMI_160_read(void *pvParameters);
bmi160_raw_data_t get_accelerometer();
bmi160_raw_data_t get_giroscope();

#endif /* BMI160_H_ */
