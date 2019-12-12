#ifndef __HAL_INPUT_CAPTURE_H_
#define __HAL_INPUT_CAPTURE_H_
#include "hwdef.h"

#ifdef HAL_INPUT_CAPTURE
/**
 * ���벶��ṹ
 */
struct input_capture
{
    uint16_t rising_time;           /*!< ������ʱ��� */
    uint16_t falling_time;          /*!< �½���ʱ��� */
    uint16_t rising_time_last;      /*!< �ߵ�ƽ��ʱ��ĳ���ʱ�� */
    uint16_t cycle;                 /*!< ����ʱ�� */
    uint16_t high_time;             /*!< �ߵ�ƽʱ�� */
    uint16_t prescaler;             /*!< ���� */
    uint8_t channel_edge;           /*!< ��ת��־ */
    uint8_t flag;                   /*!< ��ɹ��ı�־ */
};
/**
 * ��ȡ���벶����Ϣ
 */
void extract_input_capture(struct input_capture *capture, TIM_HandleTypeDef *htim, uint32_t channel);
/**
 * �������ṹ������
 */
extern struct input_capture input_capture[14 * 4];
#endif
#endif
