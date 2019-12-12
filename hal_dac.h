#ifndef __HAL_DAC_H_
#define __HAL_DAC_H_
#include "hwdef.h"

#ifdef HAL_DAC
/**
 * …Ë÷√µÁ—π÷µ
 */
void set_voltage(DAC_HandleTypeDef* hdac, uint8_t channel, uint32_t base_vol, uint32_t vol);
#endif

#endif
