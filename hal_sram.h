/*
 * hal_sram.h
 *
 *  Created on: Nov 13, 2019
 *      Author: caijie
 */

#ifndef HWDEF_HAL_SRAM_H_
#define HWDEF_HAL_SRAM_H_
#include "hwdef.h"

#ifdef HAL_SRAM

#define STM32_SRAM_BASE     SRAM_BASE
#ifndef BOARD_SRAM_SIZE
#define BOARD_SRAM_SIZE     (256 * 1024)
#endif
#ifndef SRAM_STORAGE_SIZE
#define SRAM_STORAGE_SIZE   (8 * 1024)
#endif

#pragma pack(1)

/**
 * 保存到sram的头部格式
 */
struct storage_head_struct{
    uint32_t headr; /*!< 缓存的头部  */
    uint16_t crc;   /*!< 数据的校验  */
    uint16_t len;   /*!< 数据的长度  */
};
#pragma pack()

/**
 * sram 的偏移值 在0到SRAM_STORAGE_SIZE之间
 */
extern uint32_t sram_ofs;

/**
 * 获取备份的数据
 */
void get_bkp_sram(uint8_t *buffer, uint32_t length);
/**
 * 设置备份的数据
 */
uint32_t set_bkp_sram(uint8_t *buffer, uint32_t length);
/**
 * 清除备份数据为0xff
 */
void bkp_sram_erase(void);
/**
 * 组包
 */
uint32_t storage_group_package(uint8_t *buf, uint8_t *data, uint32_t len);
/**
 * 解包
 */
int storage_unpacking(void (*read)(uint8_t *buf, uint32_t len), uint8_t *data, uint32_t len);
/**
 * 按格式写入备份数据
 */
int backup_data_write(uint8_t *data, uint32_t len);
/**
 * 按格式读取备份数据
 */
int backup_data_read(uint8_t *data, uint32_t len);
#endif
#endif /* HWDEF_HAL_SRAM_H_ */
