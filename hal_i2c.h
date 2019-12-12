/*
 * hal_i2c.h
 *
 *  Created on: Nov 15, 2019
 *      Author: caijie
 */

#ifndef HWDEF_HAL_I2C_H_
#define HWDEF_HAL_I2C_H_
#include "hwdef.h"

#ifdef HAL_I2C

int i2c_write_register(uint8_t chan, uint16_t  DevAddress, uint8_t *recv, uint16_t recv_len);
int i2c_read_registers(uint8_t chan, uint16_t  DevAddress, uint8_t reg, uint8_t *recv, uint16_t recv_len);
#endif
#endif /* HWDEF_HAL_I2C_H_ */
