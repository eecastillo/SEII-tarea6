/*
 * BMI160.c
 *
 *  Created on: Oct 15, 2020
 *      Author: eduar
 */
#include "BMI160.h"

bmi160_raw_data_t get_accelerometer()
{
}

bmi160_raw_data_t get_giroscope()
{
}

void BMI_160_read(void *pvParameters)
{
	TickType_t xLastWakeTime;
	TickType_t xfactor = pdMS_TO_TICKS(1000);
	// Initialise the xLastWakeTime variable with the current time.
	xLastWakeTime = xTaskGetTickCount();
	bmi160_raw_data_t gyr_data;
	bmi160_raw_data_t acc_data;

	for( ;; )
	{
		gyr_data = get_giroscope();
		acc_data = get_accelerometer();
		vTaskDelayUntil( &xLastWakeTime, xfactor );
	}
}
void BMI160_init(void *pvParameters)
{

	vTaskSuspend(NULL);
}

