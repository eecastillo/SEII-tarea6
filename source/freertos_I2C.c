/*
 * freertos_I2C.c
 *
 *  Created on: Oct 15, 2020
 *      Author: eduar
 */

#include "freertos_I2C.h"
#include "fsl_i2c.h"
#include "fsl_clock.h"
#include "fsl_port.h"
#include "FreeRTOS.h"
#include "semphr.h"

#define NUMBER_OF_SERIAL_PORTS (4)

typedef struct
{
  uint8_t is_init;
  i2c_master_handle_t fsl_i2c_master_handle;
  SemaphoreHandle_t mutex_sda;
  SemaphoreHandle_t sda_sem;
} freertos_i2c_hanlde_t;

static freertos_i2c_hanlde_t freertos_i2c_handles[NUMBER_OF_SERIAL_PORTS] = {0};

static inline void freertos_i2c_enable_port_clock(freertos_i2c_port_t port);

static inline void freertos_i2c_enable_clock(freertos_i2c_number_t i2c_number);

static inline PORT_Type * freertos_i2c_get_port_base(freertos_i2c_port_t port);

static inline I2C_Type * freertos_i2c_get_i2c_base(freertos_i2c_number_t i2c_number);

static void fsl_i2c_callback(I2C_Type *base, uart_handle_t *handle, status_t status, void *userData);

freertos_i2c_flag_t freertos_i2c_init(freertos_i2c_config_t config)
{
	freertos_i2c_flag_t retval = freertos_i2c_fail;
	i2c_master_config_t fsl_i2c_config;

	if(config.i2c_number < NUMBER_OF_SERIAL_PORTS)
	{
		if(!freertos_i2c_handles[config.i2c_number].is_init)
		{
			freertos_i2c_handles[config.i2c_number].mutex_sda = xSemaphoreCreateMutex();

			freertos_i2c_handles[config.i2c_number].sda_sem = xSemaphoreCreateBinary();

		  /* Clock Enable */
			freertos_i2c_enable_port_clock(config.port);
			freertos_i2c_enable_clock(config.i2c_number);

			/* Port Config */
			PORT_SetPinMux(freertos_i2c_get_port_base(config.port), config.sda_pin, config.pin_mux);
			PORT_SetPinMux(freertos_i2c_get_port_base(config.port), config.scl_pin, config.pin_mux);

			I2C_MasterGetDefaultConfig(&fsl_i2c_config);
			fsl_i2c_config.baudRate_Bps = config.baudrate;

			switch(config.i2c_number)
			{
				case freertos_i2c_0:
					I2C_MasterInit(freertos_i2c_get_i2c_base(freertos_i2c_0),&fsl_i2c_config, CLOCK_GetFreq(I2C0_CLK_SRC));
					NVIC_SetPriority(I2C0_IRQn, 5);
					break;
				case freertos_i2c_1:
					I2C_MasterInit(freertos_i2c_get_i2c_base(freertos_i2c_1),&fsl_i2c_config, CLOCK_GetFreq(I2C1_CLK_SRC));
					NVIC_SetPriority(I2C1_IRQn, 5);
					break;
				case freertos_i2c_2:
					I2C_MasterInit(freertos_i2c_get_i2c_base(freertos_i2c_2),&fsl_i2c_config, CLOCK_GetFreq(I2C2_CLK_SRC));
					NVIC_SetPriority(I2C2_IRQn, 5);
					break;
				case freertos_i2c_3:
					I2C_MasterInit(freertos_i2c_get_i2c_base(freertos_i2c_3),&fsl_i2c_config, CLOCK_GetFreq(I2C3_CLK_SRC));
					NVIC_SetPriority(I2C3_IRQn, 5);
					break;
			}

			I2C_MasterTransferCreateHandle(freertos_i2c_get_i2c_base(config.i2c_number), &freertos_i2c_handles[config.i2c_number].fsl_i2c_master_handle, fsl_i2c_callback, NULL);

			freertos_i2c_handles[config.i2c_number].is_init = 1;

			retval = freertos_i2c_sucess;
		}
	}

	return retval;
}

freertos_i2c_flag_t freertos_i2c_send(freertos_i2c_number_t i2c_number, uint8_t * buffer, uint16_t lenght, uint8_t slave_addres, uint32_t reg_address, uint8_t reg_size)
{
	freertos_i2c_flag_t flag = freertos_i2c_fail;
	i2c_master_transfer_t  master_xfer;

	if(freertos_i2c_handles[i2c_number].is_init)
	{
		master_xfer.flags = kI2C_TransferDefaultFlag;
		master_xfer.slaveAddress = slave_addres;
		master_xfer.direction = kI2C_Write;
		master_xfer.subaddress = reg_address;
		master_xfer.subaddressSize = reg_size;
		master_xfer.data = buffer;
		master_xfer.dataSize = lenght;

		xSemaphoreTake(freertos_i2c_handles[i2c_number].mutex_sda, portMAX_DELAY);

		I2C_MasterTransferNonBlocking(freertos_i2c_get_i2c_base(i2c_number), &freertos_i2c_handles[i2c_number].fsl_i2c_master_handle, &master_xfer);

		xSemaphoreTake(freertos_i2c_handles[i2c_number].sda_sem, portMAX_DELAY);

		xSemaphoreGive(freertos_i2c_handles[i2c_number].mutex_sda);

		flag = freertos_i2c_sucess;
	}

	return flag;
}

freertos_i2c_flag_t freertos_i2c_receive(freertos_i2c_number_t i2c_number, uint8_t * buffer, uint16_t lenght, uint8_t slave_addres, uint32_t reg_address, uint8_t reg_size)
{
  freertos_i2c_flag_t flag = freertos_i2c_fail;
  i2c_master_transfer_t master_xfer;

	if(freertos_i2c_handles[i2c_number].is_init)
	{
		master_xfer.flags = kI2C_TransferDefaultFlag;
		master_xfer.slaveAddress = slave_addres;
		master_xfer.direction = kI2C_Read;
		master_xfer.subaddress = reg_address;
		master_xfer.subaddressSize = reg_size;
		master_xfer.data = buffer;
		master_xfer.dataSize = lenght;

		xSemaphoreTake(freertos_i2c_handles[i2c_number].mutex_rx, portMAX_DELAY);

		I2C_MasterTransferNonBlocking(freertos_uart_get_uart_base(i2c_number), &freertos_i2c_handles[i2c_number].fsl_i2c_master_handle, &master_xfer, NULL);

		xSemaphoreTake(freertos_i2c_handles[i2c_number].sda_sem, portMAX_DELAY);

		xSemaphoreGive(freertos_i2c_handles[i2c_number].mutex_sda);

		flag = freertos_i2c_sucess;
	}

	return flag;
}

static inline void freertos_i2c_enable_clock(freertos_i2c_port_t port)
{
	switch(port)
	{
    case freertos_i2c_portA:
      CLOCK_EnableClock(kCLOCK_PortA);
      break;
    case freertos_i2c_portB:
      CLOCK_EnableClock(kCLOCK_PortB);
      break;
    case freertos_i2c_portC:
      CLOCK_EnableClock(kCLOCK_PortC);
      break;
    case freertos_i2c_portD:
      CLOCK_EnableClock(kCLOCK_PortD);
      break;
    case freertos_i2c_portE:
      CLOCK_EnableClock(kCLOCK_PortE);
      break;
	}
}
