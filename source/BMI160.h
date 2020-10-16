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

// Accelerometer Registers
#define ACC_Z_H 0x17
#define ACC_Z_L 0x16
#define ACC_Y_H 0x15
#define ACC_Y_L 0x14
#define ACC_X_H 0x13
#define ACC_X_L 0x12
// Gyroscope Registers
#define GYR_Z_H 0x11
#define GTR_Z_L 0x10
#define GYR_Y_H 0x0F
#define GYR_Y_L 0x0E
#define GYR_X_H 0x0D
#define GYR_X_L 0x0C
#define STATUS_REG 0x1B //bit 7 data ready accelerometer, bit 6 drdy gyroscope
#define GYR_CONF_REG 0x42
#define ACC_CONG_REG 0x40
#define SLAVE_ADRESS 0x68
//Bit 5 y 4 estado de accm bit 3 y 2 estado de Gyro. Ambos normal es 01
#define	PMU_STATUS 0x03
#define CMD_REGISTER 0x7E //
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
