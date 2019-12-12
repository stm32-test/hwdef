#include "hal_input_capture.h"

#ifdef HAL_INPUT_CAPTURE
struct input_capture input_capture[14 * 4] = {0};

void extract_input_capture(struct input_capture *capture, TIM_HandleTypeDef *htim, uint32_t channel)
{
    if(capture->channel_edge == 0){
        capture->rising_time = HAL_TIM_ReadCapturedValue(htim, channel);//获取上升沿时间点
        __HAL_TIM_SET_CAPTUREPOLARITY(htim, channel, TIM_INPUTCHANNELPOLARITY_FALLING);//切换捕获
        if(capture->rising_time_last == 0){
            capture->cycle = 0;
        }
        else{
            if(capture->rising_time > capture->rising_time_last){
                capture->cycle = capture->rising_time - capture->rising_time_last;
            }
            else{
                capture->cycle = capture->rising_time + 0xffff - capture->rising_time_last + 1;
            }
        }
        capture->rising_time_last = capture->rising_time;
        capture->channel_edge = 1;
    }
    else{
        capture->falling_time = HAL_TIM_ReadCapturedValue(htim, channel);
        __HAL_TIM_SET_CAPTUREPOLARITY(htim, channel, TIM_INPUTCHANNELPOLARITY_RISING);//切换捕获

        if(capture->falling_time < capture->rising_time){
            capture->high_time = capture->falling_time + 0xffff - capture->rising_time + 1;
        }
        else{
            capture->high_time = capture->falling_time - capture->rising_time;
        }
        capture->channel_edge = 0;
        capture->flag = 1;
    }
}
#endif
