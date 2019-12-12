/*
 * hal_flash.h
 *
 *  Created on: Nov 8, 2019
 *      Author: caijie
 */

#ifndef HWDEF_HAL_FLASH_H_
#define HWDEF_HAL_FLASH_H_
#include "hwdef.h"

#ifdef HAL_FLASH
#include <stdio.h>

#ifndef BOARD_FLASH_SIZE
#define BOARD_FLASH_SIZE 512            /*!< FLASH大小 */
#endif
#define STM32_FLASH_BASE    0x08000000  /*!< FLASH基地址 */
#define FLASH_WAITE_TIME   50000        /*!< 写FLASH超时时间 */
#define KB(x)   ((x*1024))

#if defined(USE_UBOOT) || defined(USE_USER_PARAMS)
#ifdef USE_UBOOT
    #include "uboot_parameter.h"
#endif
#ifdef USE_USER_PARAMS
    #include "user_parameter.h"
#endif
/**
 * 分区表
 */
#define     ADDR_UBOOT_APP          STM32_FLASH_BASE                 /*!< uboot程序地址,可用空间64K */
#define     ADDR_FLASH_PARAM        flash_func_sector_address(4)     /*!< uboot参数和用户参数地址,可用空间64K */
#define     ADDR_USER_APP           flash_func_sector_address(5)     /*!< 用户程序地址,可用空间896K */

struct flash_param
{
#ifdef USE_UBOOT
    struct uboot_param uboot;
#endif
#ifdef USE_USER_PARAMS
    struct user_param user;
#endif
};

/**
 * 从FLASH读出参数
 */
void flash_read_param(struct flash_param *param);
/**
 * 写入参数到FLASH
 */
int flash_write_param(struct flash_param *param);
/**
 * FLASH参数
 */
extern struct flash_param flash_params;
#endif
/**
 * 读取一个8位的数据
 */
uint8_t flash_read_byte(uint32_t address);
/**
 * 读取一个32位的数据
 */
uint32_t flash_read_word(uint32_t address);
/**
 * 读取多个8位的数据
 */
void flash_read_array_byte(uint32_t address, uint8_t *buffer, uint32_t length);
/**
 * 读取多个32位的数据
 */
void flash_read_array_word(uint32_t address, uint32_t *buffer, uint32_t length);
/**
 * 写入8位数据
 * 返回值：0失败，1成功
 */
int flash_write_array_byte(uint32_t address, uint8_t *buffer, uint32_t length);
/**
 * 写入32位的数据
 * 返回值：0失败，1成功
 */
int flash_write_array_word(uint32_t address, uint32_t *buffer, uint32_t length);

/**
 * 获取扇区大小
 */
uint32_t flash_func_sector_size(uint8_t sector);
/**
 * 获取扇区的地址
 */
uint32_t flash_func_sector_address(uint8_t sector);

/**
 * 擦除当前扇区
 */
int flash_sector_erase(uint32_t sector, uint32_t num);
#endif
#endif /* HWDEF_HAL_FLASH_H_ */
