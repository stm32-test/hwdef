/*
 * hal_adc.c
 *
 *  Created on: Nov 12, 2019
 *      Author: caijie
 */
#include "hal_adc.h"

#ifdef HAL_ADC_DMA
struct adc_dma_type adc_dma = {NULL};

void start_adc_dma_transfer(struct adc_type *list, uint32_t* data, uint32_t length)
{
    uint8_t i = 0, j = 0;
    ADC_HandleTypeDef* hadc_last = NULL;

    adc_dma.cache = data;
    adc_dma.length = length;
    adc_dma.adc = list;

    for(; i < 255; i++){
        if(list[i].hadc == NULL)
            break;
        if(hadc_last != list[i].hadc){
            hadc_last = list[i].hadc;
            for(j = 0; j < 255; j++)
                if(hadc_last != list[i + j].hadc)
                    break;

            HAL_ADC_Start_DMA(list[i].hadc, &data[i * length], j * length);
            i += j - 1;
        }
    }
}

/** 获取排列的位置排序
 *  ofs 这组ADC排列在第几组里
 *  group 这组ADC一共使用了几个通道
 *  seq 这个通道在这组ADC的第几个
 */
void get_adc_dma_coordinate(ADC_HandleTypeDef* adc, uint32_t chan, uint8_t *ofs, uint8_t *group, uint8_t *seq)
{
    uint8_t ofs_flag = 0, seq_flag = 0;
    uint8_t ofs_temp = *ofs, group_temp = *group, seq_temp = *seq;

    for(uint8_t i = 0; i < 255; i++) {
        if((adc_dma.adc[i].hadc == NULL)) {
            break;
        }

        if(adc_dma.adc[i].hadc == adc) {
            if((ofs_flag == 0) && (ofs_flag == 0)) {
                ofs_temp = i;
                ofs_flag = 1;
            }
            group_temp = group_temp + 1;

            if((adc_dma.adc[i].channel != chan) && (seq_flag == 0)) {
                seq_temp = seq_temp + 1;
            }
            else {
                seq_flag = 1;
            }
        }

    }

    *ofs = ofs_temp;
    *group = group_temp;
    *seq = seq_temp;
}
#endif

#ifdef HAL_ADC

#ifdef STM32F1
ADC_ChannelConfTypeDef adc_config = {
        .Rank = 1,
        .SamplingTime = ADC_SAMPLETIME_239CYCLES_5
};
#else
ADC_ChannelConfTypeDef adc_config = {
        .Rank = 1,
        .SamplingTime = ADC_SAMPLETIME_480CYCLES};
#endif




uint32_t read_adc(ADC_HandleTypeDef* hadc, uint32_t channel)
{
    uint32_t adc_val = 0;
#ifdef HAL_ADC_DMA
    uint8_t group = 0, ofs = 0, seq = 0;

    get_adc_dma_coordinate(hadc, channel, &ofs, &group, &seq);
    //转换成二维数组,和当前组ADC数量一样
    uint32_t (*t)[group] = (uint32_t (*)[group])&adc_dma.cache[ofs * adc_dma.length];

    uint64_t temp = 0;
    for(uint16_t i = 0; i < adc_dma.length; i++) {
        temp += *(*(t+i)+seq);
    }
    adc_val = temp / adc_dma.length;
#else
    adc_config.Channel = channel;
    HAL_ADC_ConfigChannel(hadc, &adc_config);
    HAL_ADC_Start(hadc);
    HAL_ADC_PollForConversion(hadc, 10);
    adc_val = HAL_ADC_GetValue(hadc);
#endif
    return adc_val;
}

void read_adc_list(struct adc_type *list)
{
    uint8_t i = 0;
    for(; i < 255; i++){
        if(list[i].hadc == NULL)
            break;
        list[i].value = read_adc(list[i].hadc, list[i].channel);
    }
}

uint32_t get_adc_average(ADC_HandleTypeDef* hadc, uint32_t channel, uint8_t num)
{
    uint8_t i = 0;
    uint32_t temp_val = 0;
    for(; i < num; i++)
        temp_val += read_adc(hadc, channel);
    return (temp_val / num);
}

void get_adc_average_list(struct adc_type *list, uint8_t num)
{
    uint8_t i = 0;
    for(; i < 255; i++){
        if(list[i].hadc == NULL)
            break;
        list[i].value = get_adc_average(list[i].hadc, list[i].channel, num);
    }
}

uint32_t get_voltage(ADC_HandleTypeDef* hadc, uint32_t channel, uint32_t base_vol)
{
    uint8_t bits = 0;
    double resolution = 0.0;
    uint32_t adc_val = get_adc_average(hadc, channel, 10);
#ifdef STM32F1
    bits = 12;
    resolution = 1.0 / 4095;
#else
    switch(hadc->Init.Resolution){
        case ADC_RESOLUTION_12B:
                                bits = 12;
                                resolution = 1.0 / 4095;
                                break;
        case ADC_RESOLUTION_10B:
                                bits = 10;
                                resolution = 1.0 / 1023;
                                break;
        case ADC_RESOLUTION_8B:
                                bits = 8;
                                resolution = 1.0 / 255;
                                break;
        case ADC_RESOLUTION_6B:
                                bits = 6;
                                resolution = 1.0 / 63;
                                break;
    }
#endif
    if(hadc->Init.DataAlign == ADC_DATAALIGN_LEFT)
        adc_val >>= (16 - bits);
    return (adc_val * resolution * base_vol);
}

void get_voltage_list(struct adc_type *list, uint32_t base_vol)
{
    uint8_t i = 0;
    for(; i < 255; i++){
        if(list[i].hadc == NULL)
            break;
        list[i].value = get_voltage(list[i].hadc, list[i].channel, base_vol);
    }
}
#endif
