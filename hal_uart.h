#ifndef __HAL_UART_H_
#define __HAL_UART_H_
#include "hwdef.h"

#ifdef HAL_UART
/**
 * ���ڴ�ӡ������ʼ��
 */
void uprintf_init(UART_HandleTypeDef *port, DMA_HandleTypeDef *dma);
/**
 * ���ڷ��ͺ���
 */
void uprintf(char * fmt, ...);
#endif

#endif /* EX_UART_EX_H_ */
