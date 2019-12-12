/*
 * hal_sram.c
 *
 *  Created on: Nov 13, 2019
 *      Author: caijie
 */
#include "hal_sram.h"
#include <string.h>

#ifdef HAL_SRAM
#include "crc16.h"
uint32_t sram_ofs = 0;
#define BACKUP_HEADR 0x123456
#define BACKUP_STOP  0x654321

void get_bkp_sram(uint8_t *buffer, uint32_t length)
{
    uint32_t address = STM32_SRAM_BASE + BOARD_SRAM_SIZE - SRAM_STORAGE_SIZE + sram_ofs;

    for(uint32_t i = 0; i < length; i++) {
        buffer[i] = *(__IO uint8_t *)address;
        address++;
    }
}

uint32_t set_bkp_sram(uint8_t *buffer, uint32_t length)
{
    uint32_t address = STM32_SRAM_BASE + BOARD_SRAM_SIZE - SRAM_STORAGE_SIZE + sram_ofs;

    for(uint32_t i = 0; i < length; i++) {
        *(__IO uint8_t*)address = buffer[i];
        address++;
    }
    return length;
}

void bkp_sram_erase(void)
{
    uint32_t address = STM32_SRAM_BASE + BOARD_SRAM_SIZE - SRAM_STORAGE_SIZE + sram_ofs;

    for(uint32_t i = 0; i < SRAM_STORAGE_SIZE; i++) {
        *(__IO uint8_t*)address = 0xff;
        address++;
    }
}
uint32_t storage_group_package(uint8_t *buf, uint8_t *data, uint32_t len)
{
    struct storage_head_struct storage = {0};
    uint32_t stop = BACKUP_STOP;
    uint32_t index = 0;

    storage.headr = BACKUP_HEADR;
    storage.crc = crc16((const uint8_t *)data, len);
    storage.len = len;

    memcpy(buf + index, &storage, sizeof(struct storage_head_struct));
    index += sizeof(struct storage_head_struct);
    memcpy(buf + index, data, len);
    index += len;
    memcpy(buf + index, &stop, 4);
    index += 4;

    return index;
}
int storage_unpacking(void (*read)(uint8_t *buf, uint32_t len), uint8_t *data, uint32_t len)
{

    struct storage_head_struct storage = {0};
    uint8_t buf[sizeof(struct storage_head_struct) + len + 4];
    uint32_t stop = BACKUP_STOP;
    uint32_t index = 0;
    uint16_t crc = 0;

    memset(buf, 0, sizeof(sizeof(struct storage_head_struct) + len + 4));
    read(buf, sizeof(struct storage_head_struct));
    memcpy(&storage, buf + index, sizeof(struct storage_head_struct));
    index +=sizeof(struct storage_head_struct);

    if(storage.headr != BACKUP_HEADR) {
        return 0;
    }
    if(storage.len > len) {
        return 0;
    }

    read(buf, sizeof(struct storage_head_struct) + storage.len + 4);
    memcpy(data, buf + index, storage.len);
    index += storage.len;

    crc = crc16((const uint8_t *)data, storage.len);
    if(storage.crc != crc) {
        return 0;
    }

    memcpy(&stop, buf + index, 4);
    if(stop != BACKUP_STOP) {
        return 0;
    }
    return 1;
}
int backup_data_write(uint8_t *data, uint32_t len)
{
    uint32_t index = 0;
    uint8_t buf[sizeof(struct storage_head_struct) + len + 4];
    memset(buf, 0, sizeof(struct storage_head_struct) + len + 4);

    index = storage_group_package(buf, data, len);
    return set_bkp_sram(buf, index);
}
int backup_data_read(uint8_t *data, uint32_t len)
{
    return storage_unpacking(get_bkp_sram, data, len);
}
#endif
