/*
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    Tarea6_i2c.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK66F18.h"
#include "fsl_debug_console.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "BMI160.h"
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */


#define BMI160_init_PRIORITY (configMAX_PRIORITIES - 1)
#define master_task_PRIORITY (configMAX_PRIORITIES - 2)
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
#define GUR_X_L 0x0C
#define STATUS_REG 0x1B //bit 7 data ready accelerometer, bit 6 drdy gyroscope
#define GYR_CONF_REG 0x42
#define SLAVE_ADRESS 0x68
#define CMD_REGISTER 0x7E //
#define	ACC_PMU_NORMAL_MODE



int main(void) {

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();



    PRINTF("Hello World\n");

    if (xTaskCreate(BMI160_init, "BMI160_init", configMINIMAL_STACK_SIZE + 100, NULL, BMI160_init_PRIORITY, NULL) !=
		pdPASS)
	{
		PRINTF("Failed to create task");
		while (1);
	}
    if (xTaskCreate(BMI_160_read, "BMI_160_read", configMINIMAL_STACK_SIZE + 100, NULL, BMI160_init_PRIORITY, NULL) !=
		pdPASS)
	{
		PRINTF("Failed to create task");
		while (1);
	}
	vTaskStartScheduler();
    for(;;){}
    return 0 ;
}



