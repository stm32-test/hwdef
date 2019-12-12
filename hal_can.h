/*
 * hal_can.h
 *
 *  Created on: 2019��11��15��
 *      Author: caijie
 */

#ifndef HWDEF_HAL_CAN_H_
#define HWDEF_HAL_CAN_H_
#include "hwdef.h"
#ifdef HAL_CAN
/**
 * ����CAN��ɸѡ��
 */
int can_filter_config(CAN_HandleTypeDef *can, uint32_t filter_bank);
/**
 * CAN������Ϣ
 */
int can_send_msg(CAN_HandleTypeDef *hcan, CAN_TxHeaderTypeDef *pHeader, uint8_t aData[], uint32_t *pTxMailbox);
#endif
#endif /* HWDEF_HAL_CAN_H_ */
