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
 * adc���Ͷ���
 */
struct adc_type
{
    ADC_HandleTypeDef* hadc;    /*!< adc��� */
    uint32_t channel;           /*!< adcͨ�� */
    uint32_t value;             /*!< adc��ֵ���ѹֵ */
};
/**
 * ��ȡADC��ֵ
 */
uint32_t read_adc(ADC_HandleTypeDef* hadc, uint32_t channel);
/**
 * ���б����ʽ��ȡADC��ֵ
 */
void read_adc_list(struct adc_type *list);
/**
 * ��ȡADC��ƽ��ֵ
 */
uint32_t get_adc_average(ADC_HandleTypeDef* hadc, uint32_t channel, uint8_t num);
/**
 * ���б����ʽ��ȡADC��ƽ��ֵ
 */
void get_adc_average_list(struct adc_type *list, uint8_t num);
/**
 * ��ȡADC�ĵ�ѹֵ
 */
uint32_t get_voltage(ADC_HandleTypeDef* hadc, uint32_t channel, uint32_t base_vol);
/**
 * ���б����ʽ��ȡADC�ĵ�ѹֵ
 */
void get_voltage_list(struct adc_type *list, uint32_t base_vol);

#ifdef HAL_ADC_DMA
/**
 * adc_dma���Ͷ���
 */
struct adc_dma_type
{
    uint32_t *cache;        /*!< DMA�����ַ */
    uint32_t length;        /*!< DMA�����С */
    struct adc_type *adc;   /*!< adc���� */
};
/**
 * ��ʼADC��DMA����
 */
void start_adc_dma_transfer(struct adc_type *list, uint32_t* data, uint32_t length);

#endif
#endif
#endif /* HWDEF_HAL_ADC_H_ */

