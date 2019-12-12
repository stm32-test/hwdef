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
#define BOARD_FLASH_SIZE 512            /*!< FLASH��С */
#endif
#define STM32_FLASH_BASE    0x08000000  /*!< FLASH����ַ */
#define FLASH_WAITE_TIME   50000        /*!< дFLASH��ʱʱ�� */
#define KB(x)   ((x*1024))

#if defined(USE_UBOOT) || defined(USE_USER_PARAMS)
#ifdef USE_UBOOT
    #include "uboot_parameter.h"
#endif
#ifdef USE_USER_PARAMS
    #include "user_parameter.h"
#endif
/**
 * ������
 */
#define     ADDR_UBOOT_APP          STM32_FLASH_BASE                 /*!< uboot�����ַ,���ÿռ�64K */
#define     ADDR_FLASH_PARAM        flash_func_sector_address(4)     /*!< uboot�������û�������ַ,���ÿռ�64K */
#define     ADDR_USER_APP           flash_func_sector_address(5)     /*!< �û������ַ,���ÿռ�896K */

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
 * ��FLASH��������
 */
void flash_read_param(struct flash_param *param);
/**
 * д�������FLASH
 */
int flash_write_param(struct flash_param *param);
/**
 * FLASH����
 */
extern struct flash_param flash_params;
#endif
/**
 * ��ȡһ��8λ������
 */
uint8_t flash_read_byte(uint32_t address);
/**
 * ��ȡһ��32λ������
 */
uint32_t flash_read_word(uint32_t address);
/**
 * ��ȡ���8λ������
 */
void flash_read_array_byte(uint32_t address, uint8_t *buffer, uint32_t length);
/**
 * ��ȡ���32λ������
 */
void flash_read_array_word(uint32_t address, uint32_t *buffer, uint32_t length);
/**
 * д��8λ����
 * ����ֵ��0ʧ�ܣ�1�ɹ�
 */
int flash_write_array_byte(uint32_t address, uint8_t *buffer, uint32_t length);
/**
 * д��32λ������
 * ����ֵ��0ʧ�ܣ�1�ɹ�
 */
int flash_write_array_word(uint32_t address, uint32_t *buffer, uint32_t length);

/**
 * ��ȡ������С
 */
uint32_t flash_func_sector_size(uint8_t sector);
/**
 * ��ȡ�����ĵ�ַ
 */
uint32_t flash_func_sector_address(uint8_t sector);

/**
 * ������ǰ����
 */
int flash_sector_erase(uint32_t sector, uint32_t num);
#endif
#endif /* HWDEF_HAL_FLASH_H_ */
