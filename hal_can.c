/*
 * hal_can.c
 *
 *  Created on: 2019年11月15日
 *      Author: caijie
 */
#include "hal_can.h"
#ifdef HAL_CAN
/**
 * CAN 的过滤配置
 */
int can_filter_config(CAN_HandleTypeDef *can, uint32_t filter_bank)
{
    CAN_FilterTypeDef  sFilterConfig = {0};

    sFilterConfig.FilterBank = filter_bank;
    sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
    sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
    sFilterConfig.FilterIdHigh = 0x0000;
    sFilterConfig.FilterIdLow = 0x0000;
    sFilterConfig.FilterMaskIdHigh = 0x0000;
    sFilterConfig.FilterMaskIdLow = 0x0000;
    sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
    sFilterConfig.FilterActivation = ENABLE;
    sFilterConfig.SlaveStartFilterBank = 14;

    if(HAL_CAN_ConfigFilter(can, &sFilterConfig) != HAL_OK)
    {
      /* Filter configuration Error */
      return 0;
    }

    /*##-3- Start the CAN peripheral ###########################################*/
    if (HAL_CAN_Start(can) != HAL_OK)
    {
      /* Start Error */
      return 0;
    }

    /*打开中断时需*/
    if(HAL_CAN_ActivateNotification(can, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
    {
        return 0;
    }
    return 1;
}
#endif
