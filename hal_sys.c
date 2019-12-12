/*
 * hal_sys.c
 *
 *  Created on: Nov 19, 2019
 *      Author: caijie
 */
#include "hal_sys.h"

#ifdef HAL_SYS
int jump_to_app(uint32_t appxaddr)
{
    int i;
     typedef void (*_func)(void);
     if(((*(__IO uint32_t*)(appxaddr + 4))&0xFF000000) != 0x08000000)
     {
         return -1;
     }

      __disable_irq();
#if defined (__MPU_PRESENT) && (__MPU_PRESENT == 1U)
      MPU->CTRL &= ~MPU_CTRL_ENABLE_Msk;
#endif
      for(i = 0; i < 8; i++)
      {
        /* disable interrupts. */
        NVIC->ICER[i] = 0xFFFFFFFF;

        /* clean up interrupts flags. */
        NVIC->ICPR[i] = 0xFFFFFFFF;
      }
      SCB->VTOR = appxaddr;
      __set_BASEPRI(0);
       __set_FAULTMASK(0);

      __set_MSP(*(uint32_t*)appxaddr);
      __set_PSP(*(uint32_t*)appxaddr);
      __set_CONTROL(0);

      __ISB();
      __disable_irq();
      ((_func)(*(uint32_t*)(appxaddr + 4)))();
      return 0;
}

void nvic_system_reset(void)
{
    NVIC_SystemReset();
}

#endif
