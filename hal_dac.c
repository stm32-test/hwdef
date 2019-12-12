#include "hal_dac.h"

#ifdef HAL_DAC
void set_voltage(DAC_HandleTypeDef* hdac, uint8_t channel, uint32_t base_vol, uint32_t vol)
{
    HAL_DAC_SetValue(hdac, channel, DAC_ALIGN_12B_R, (double)vol / base_vol * 4095);
}
#endif
