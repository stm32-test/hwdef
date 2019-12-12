/*
 * hal_flash.c
 *
 *  Created on: Nov 8, 2019
 *      Author: caijie
 */

#include "hal_flash.h"

#ifdef HAL_FLASH

#ifdef STM32F4
#if (BOARD_FLASH_SIZE == 512)
#define STM32_FLASH_NPAGES  8
static const uint32_t flash_memmap[STM32_FLASH_NPAGES] = {
                            KB(16), KB(16), KB(16), KB(16), KB(64),
                            KB(128), KB(128), KB(128)
};
#elif (BOARD_FLASH_SIZE == 1024)
#define STM32_FLASH_NPAGES  12
static const uint32_t flash_memmap[STM32_FLASH_NPAGES] = {
                            KB(16), KB(16), KB(16), KB(16), KB(64),
                            KB(128), KB(128), KB(128), KB(128), KB(128), KB(128), KB(128)
};
#elif (BOARD_FLASH_SIZE == 2048)
#define STM32_FLASH_NPAGES  24
static const uint32_t flash_memmap[STM32_FLASH_NPAGES] = {
                            KB(16), KB(16), KB(16), KB(16), KB(64),
                            KB(128), KB(128), KB(128), KB(128), KB(128), KB(128), KB(128),
                            KB(16), KB(16), KB(16), KB(16), KB(64),
                            KB(128), KB(128), KB(128), KB(128), KB(128), KB(128), KB(128)};
#endif
#endif

#ifdef STM32F7
#if (BOARD_FLASH_SIZE == 1024)
#define STM32_FLASH_NPAGES  8
static const uint32_t flash_memmap[STM32_FLASH_NPAGES] = {
                            KB(32), KB(32), KB(32), KB(32), KB(128), KB(256), KB(256), KB(256)
};

#elif (BOARD_FLASH_SIZE == 2048)
#define STM32_FLASH_NPAGES  12
static const uint32_t flash_memmap[STM32_FLASH_NPAGES] = {
                            KB(32), KB(32), KB(32), KB(32), KB(128), KB(256), KB(256), KB(256),
                            KB(256), KB(256), KB(256), KB(256) };
#endif
#endif


uint8_t flash_get_sector(uint32_t address)
{
#ifdef STM32F1
    return ((address - STM32_FLASH_BASE) / 1024);
#else
    uint32_t memmap = STM32_FLASH_BASE;
    for(uint8_t sector = 0; sector < STM32_FLASH_NPAGES; sector++) {
        memmap = flash_memmap[sector] + memmap;
       if(address < memmap) {
           return sector;
       }
    }
    return STM32_FLASH_NPAGES - 1;
#endif
}

uint32_t flash_func_sector_size(uint8_t sector)
{
#ifdef STM32F1
    return 1024U;
#else
    return flash_memmap[sector];
#endif
}

uint32_t flash_func_sector_address(uint8_t sector)
{
#ifdef STM32F1
    return (STM32_FLASH_BASE + sector * 1024);
#else
    uint32_t adder = 0;
    for(uint8_t i = 0; i < sector; i++) {
        adder += flash_memmap[i];
    }
    return adder + STM32_FLASH_BASE;
#endif
}

int flash_sector_erase(uint32_t sector, uint32_t num)
{
    FLASH_EraseInitTypeDef flash_erase = {0};
    uint32_t error = 0;
#ifdef STM32F1
    flash_erase.TypeErase = FLASH_TYPEERASE_PAGES;
    flash_erase.NbPages = num;
    flash_erase.PageAddress = flash_func_sector_address(sector);
#else
    flash_erase.TypeErase = FLASH_TYPEERASE_SECTORS;
    flash_erase.Sector = sector;
    flash_erase.NbSectors = num;
    flash_erase.VoltageRange = FLASH_VOLTAGE_RANGE_3;
#endif
    flash_erase.Banks = (num == 1)?(0):(FLASH_BANK_1);

    if((HAL_FLASHEx_Erase(&flash_erase, &error) != HAL_OK) && (error != 0xFFFFFFFFU)) {
        printf("HAL_FLASHEx_Erase err \r\n");
        return 0;
    }

    if(FLASH_WaitForLastOperation(FLASH_WAITE_TIME) != HAL_OK) {//等待上次操作完成
        printf("FLASH_WaitForLastOperation time out \r\n");
        return 0;
    }
    return 1;
}

uint8_t flash_read_byte(uint32_t address)
{
    return *(volatile uint8_t *)address;
}

uint32_t flash_read_word(uint32_t address)
{
    return *(volatile uint32_t *)address;
}

void flash_read_array_byte(uint32_t address, uint8_t *buffer, uint32_t length)
{
    for(uint32_t i = 0; i < length; i++) {
        buffer[i] = flash_read_byte(address);
        address++;
    }
}

void flash_read_array_word(uint32_t address, uint32_t *buffer, uint32_t length)
{
    for(uint32_t i = 0; i < length; i++) {
        buffer[i] = flash_read_word(address);
        address += 4;
    }
}

int flash_write_array_byte(uint32_t address, uint8_t *buffer, uint32_t length)
{
    uint32_t addrx = address;
    uint32_t endaddr = address + length;
#ifdef STM32F1
    uint16_t temp = 0;
    uint32_t type_program = FLASH_TYPEPROGRAM_HALFWORD;
#else
    uint32_t type_program = FLASH_TYPEPROGRAM_BYTE;
#endif

    if((address < STM32_FLASH_BASE) || (address % 4) || (endaddr >= 0x1FFF0000)) {
        return -1;
    }

    HAL_FLASH_Unlock();

    while(addrx < endaddr) {
        if(flash_read_word(addrx) != 0xFFFFFFFF) {
            if(!flash_sector_erase(flash_get_sector(addrx), 1)) {
                HAL_FLASH_Lock();
                return 0;
            }
        }
        else {
            addrx += 4;
        }
    }

    addrx = address;

    while(addrx < endaddr) {
#ifdef STM32F1
        if((length % 2 == 1) && (addrx == endaddr -1)){
            temp = 0xFF << 8  | (*buffer);
        }
        else{
            temp = *(uint16_t*)buffer;
        }

        if(HAL_FLASH_Program(type_program, addrx, temp) != HAL_OK) {
            HAL_FLASH_Lock();
            return 0;
        }

#else
        if(HAL_FLASH_Program(type_program, addrx, *buffer) != HAL_OK) {
            HAL_FLASH_Lock();
            return 0;
        }
#endif
#ifdef STM32F1
        addrx += 2;
        buffer += 2;
#else
        addrx++;
        buffer++;
#endif
    }

    /* Locks the FLASH control register access */
    HAL_FLASH_Lock();
    return 1;
}

int flash_write_array_word(uint32_t address, uint32_t *buffer, uint32_t length)
{
#ifdef STM32F1
    return flash_write_array_byte(address, (uint8_t*)buffer, length * 2);
#else
    return flash_write_array_byte(address, (uint8_t*)buffer, length * 4);
#endif
}

#if defined(USE_UBOOT) || defined(USE_USER_PARAMS)
struct flash_param flash_params = {0};

void flash_read_param(struct flash_param *param)
{
    if(param == NULL)
        param = &flash_params;
    flash_read_array(ADDR_FLASH_PARAM, (uint8_t *)param, sizeof(struct flash_param));
}

int flash_write_param(struct flash_param *param)
{
    if(param == NULL)
        param = &flash_params;
    return flash_write_array(ADDR_FLASH_PARAM, (uint8_t *)param, sizeof(struct flash_param));
}
#endif

#endif
