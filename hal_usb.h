#ifndef __HAL_USB_H_
#define __HAL_USB_H_
#include "hwdef.h"

#ifdef HAL_USB
#include "string.h"
#include "stdarg.h"
#include "stdio.h"



#ifndef USB_TRANSMIT
#ifdef USB_OTG_FS
#include "usbd_cdc_if.h"
#define usb_transmit CDC_Transmit_FS
#else
#error "USB_OTG_FS not define!"
#endif
#endif


/**
 * USBÐéÄâ´®¿Ú´òÓ¡º¯Êý
 */
void usb_printf(char* fmt,...);

#endif

#endif /* EX_USB_EX_H_ */
