#ifndef __HAL_UART_H_
#define __HAL_UART_H_
#include "hwdef.h"

#ifdef HAL_UART
/**
 * 串口打印函数初始化
 */
void uprintf_init(UART_HandleTypeDef *port, DMA_HandleTypeDef *dma);
/**
 * 串口发送函数
 */
void uprintf(char * fmt, ...);
#endif

#endif /* EX_UART_EX_H_ */
