/*
 * hal_can.h
 *
 *  Created on: 2019年11月15日
 *      Author: caijie
 */

#ifndef HWDEF_HAL_CAN_H_
#define HWDEF_HAL_CAN_H_
#include "hwdef.h"
#ifdef HAL_CAN
/**
 * 配置CAN的筛选器
 */
int can_filter_config(CAN_HandleTypeDef *can, uint32_t filter_bank);
/**
 * CAN发送消息
 */
int can_send_msg(CAN_HandleTypeDef *hcan, CAN_TxHeaderTypeDef *pHeader, uint8_t aData[], uint32_t *pTxMailbox);
#endif
#endif /* HWDEF_HAL_CAN_H_ */
