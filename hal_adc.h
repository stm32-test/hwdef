/*
 * hal_adc.h
 *
 *  Created on: Nov 12, 2019
 *      Author: caijie
 */

#ifndef HWDEF_HAL_ADC_H_
#define HWDEF_HAL_ADC_H_
#include "hwdef.h"

#ifdef HAL_ADC
/**
 * adc类型定义
 */
struct adc_type
{
    ADC_HandleTypeDef* hadc;    /*!< adc句柄 */
    uint32_t channel;           /*!< adc通道 */
    uint32_t value;             /*!< adc的值或电压值 */
};
/**
 * 读取ADC的值
 */
uint32_t read_adc(ADC_HandleTypeDef* hadc, uint32_t channel);
/**
 * 以列表的形式读取ADC的值
 */
void read_adc_list(struct adc_type *list);
/**
 * 读取ADC的平均值
 */
uint32_t get_adc_average(ADC_HandleTypeDef* hadc, uint32_t channel, uint8_t num);
/**
 * 以列表的形式读取ADC的平均值
 */
void get_adc_average_list(struct adc_type *list, uint8_t num);
/**
 * 读取ADC的电压值
 */
uint32_t get_voltage(ADC_HandleTypeDef* hadc, uint32_t channel, uint32_t base_vol);
/**
 * 以列表的形式读取ADC的电压值
 */
void get_voltage_list(struct adc_type *list, uint32_t base_vol);

#ifdef HAL_ADC_DMA
/**
 * adc_dma类型定义
 */
struct adc_dma_type
{
    uint32_t *cache;        /*!< DMA缓存地址 */
    uint32_t length;        /*!< DMA缓存大小 */
    struct adc_type *adc;   /*!< adc类型 */
};
/**
 * 开始ADC的DMA传输
 */
void start_adc_dma_transfer(struct adc_type *list, uint32_t* data, uint32_t length);

#endif
#endif
#endif /* HWDEF_HAL_ADC_H_ */

