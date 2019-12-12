/*
 * hal_gpio.h
 *
 *  Created on: Nov 6, 2019
 *      Author: caijie
 */

#ifndef HWDEF_HAL_GPIO_H_
#define HWDEF_HAL_GPIO_H_

#include "hwdef.h"

#ifdef HAL_GPIO
/**
 * GPIO的数据
 */
struct gpio_port{
    GPIO_TypeDef *group; /*!< GPIO的类型  */
    uint16_t pin;        /*!< 第几个GPIO  */
};

#define SET_GPIO_STATUS(group, pin, status) HAL_GPIO_WritePin(group, pin, status)
#define GET_GPIO_STATUS(group, pin)         HAL_GPIO_ReadPin(group, pin)
#define GPIO_TOGGLE(group, pin)             HAL_GPIO_TogglePin(group, pin)

/**
 * GPIO的配置
 */
void gpio_config(GPIO_TypeDef *group, uint16_t pin, uint32_t mode, uint32_t pull);
/**
 * GPIO的配置结构体形式
 */
void gpio_config_structure(struct gpio_port *port, uint32_t mode, uint32_t pull);
#endif
#endif /* HWDEF_HAL_GPIO_H_ */
