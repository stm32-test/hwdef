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
 * ���浽sram��ͷ����ʽ
 */
struct storage_head_struct{
    uint32_t headr; /*!< �����ͷ��  */
    uint16_t crc;   /*!< ���ݵ�У��  */
    uint16_t len;   /*!< ���ݵĳ���  */
};
#pragma pack()

/**
 * sram ��ƫ��ֵ ��0��SRAM_STORAGE_SIZE֮��
 */
extern uint32_t sram_ofs;

/**
 * ��ȡ���ݵ�����
 */
void get_bkp_sram(uint8_t *buffer, uint32_t length);
/**
 * ���ñ��ݵ�����
 */
uint32_t set_bkp_sram(uint8_t *buffer, uint32_t length);
/**
 * �����������Ϊ0xff
 */
void bkp_sram_erase(void);
/**
 * ���
 */
uint32_t storage_group_package(uint8_t *buf, uint8_t *data, uint32_t len);
/**
 * ���
 */
int storage_unpacking(void (*read)(uint8_t *buf, uint32_t len), uint8_t *data, uint32_t len);
/**
 * ����ʽд�뱸������
 */
int backup_data_write(uint8_t *data, uint32_t len);
/**
 * ����ʽ��ȡ��������
 */
int backup_data_read(uint8_t *data, uint32_t len);
#endif
#endif /* HWDEF_HAL_SRAM_H_ */
