/*
 * hal_gpio.c
 *
 *  Created on: Nov 6, 2019
 *      Author: caijie
 */
#include "hal_gpio.h"

#ifdef HAL_GPIO
void gpio_rcc_config(GPIO_TypeDef *gpiox)
{
    if(gpiox == GPIOA){
        __HAL_RCC_GPIOA_CLK_ENABLE();
    }
    else if(gpiox == GPIOB){
        __HAL_RCC_GPIOB_CLK_ENABLE();
    }
    else if(gpiox == GPIOC){
        __HAL_RCC_GPIOC_CLK_ENABLE();
    }

#ifdef GPIOD
     else if(gpiox == GPIOD){
         __HAL_RCC_GPIOD_CLK_ENABLE();
     }
#endif
#ifdef GPIOE
     else if(gpiox == GPIOE){
         __HAL_RCC_GPIOE_CLK_ENABLE();
     }
#endif
#ifdef GPIOF
     else if(gpiox == GPIOF){
         __HAL_RCC_GPIOF_CLK_ENABLE();
     }
#endif
#ifdef GPIOG
     else if(gpiox == GPIOG){
         __HAL_RCC_GPIOG_CLK_ENABLE();
     }
#endif
#ifdef GPIOH
     else if(gpiox == GPIOH){
         __HAL_RCC_GPIOH_CLK_ENABLE();
     }
#endif
}

/*  配置GPIO输入模式还是输出模式
 *  port:对应的GPIO端口
 */
void gpio_config_structure(struct gpio_port *port, uint32_t mode, uint32_t pull)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    gpio_rcc_config(port->group);

    GPIO_InitStruct.Pin = port->pin;
    GPIO_InitStruct.Mode = mode;
    GPIO_InitStruct.Pull = pull;
#ifdef STM32F1
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
#else
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
#endif
    HAL_GPIO_Init(port->group, &GPIO_InitStruct);
}
void gpio_config(GPIO_TypeDef *group, uint16_t pin, uint32_t mode, uint32_t pull)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    gpio_rcc_config(group);

    GPIO_InitStruct.Pin = pin;
    GPIO_InitStruct.Mode = mode;
    GPIO_InitStruct.Pull = pull;
#ifdef STM32F1
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
#else
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
#endif
    HAL_GPIO_Init(group, &GPIO_InitStruct);
}
#endif
