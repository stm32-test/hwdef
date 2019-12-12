/*
 * hal_i2c.c
 *
 *  Created on: Nov 15, 2019
 *      Author: caijie
 */
#include "hal_i2c.h"
#include <string.h>

#ifdef HAL_I2C

I2C_HandleTypeDef *hi2c_list[HAL_I2C_DEVICE_NUMBER] = HAL_I2C_DEVICE_LIST;


int i2c_write_register(uint8_t chan, uint16_t  DevAddress, uint8_t *recv, uint16_t recv_len)
{
    if( HAL_I2C_Master_Transmit(hi2c_list[chan], DevAddress, recv, recv_len, 100) != HAL_OK){
        return 0;
    }
    return 1;
}

int i2c_read_registers(uint8_t chan, uint16_t  DevAddress, uint8_t reg, uint8_t *recv, uint16_t recv_len)
{
    uint8_t buf[recv_len * 2];

    buf[0] = reg;
    for(uint16_t i = 0; i < recv_len; i++)
    {
        buf[i * 2] = buf[0] + i;
    }

    if( HAL_I2C_Master_Receive(hi2c_list[chan], DevAddress, buf, recv_len, 100) != HAL_OK){

        return 0;
    }
    memcpy(recv, buf, recv_len);
    return 1;
}


#endif
