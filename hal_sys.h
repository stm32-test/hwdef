/*
 * hal_sys.h
 *
 *  Created on: Nov 19, 2019
 *      Author: caijie
 */

#ifndef HWDEF_HAL_SYS_H_
#define HWDEF_HAL_SYS_H_
#include "hwdef.h"

#ifdef HAL_SYS
/**
 * Ìø×ªAPP
 */
int jump_to_app(uint32_t appxaddr);
/**
 * ÖØÆô
 */
void nvic_system_reset(void);

#endif
#endif /* HWDEF_HAL_SYS_H_ */
