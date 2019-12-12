#ifndef __HAL_INPUT_CAPTURE_H_
#define __HAL_INPUT_CAPTURE_H_
#include "hwdef.h"

#ifdef HAL_INPUT_CAPTURE
/**
 * 输入捕获结构
 */
struct input_capture
{
    uint16_t rising_time;           /*!< 上升的时间点 */
    uint16_t falling_time;          /*!< 下降的时间点 */
    uint16_t rising_time_last;      /*!< 高电平的时间的持续时间 */
    uint16_t cycle;                 /*!< 周期时间 */
    uint16_t high_time;             /*!< 高电平时间 */
    uint16_t prescaler;             /*!< 周期 */
    uint8_t channel_edge;           /*!< 翻转标志 */
    uint8_t flag;                   /*!< 测成功的标志 */
};
/**
 * 提取输入捕获信息
 */
void extract_input_capture(struct input_capture *capture, TIM_HandleTypeDef *htim, uint32_t channel);
/**
 * 输出捕获结构体数组
 */
extern struct input_capture input_capture[14 * 4];
#endif
#endif
