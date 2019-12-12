#include "hal_usb.h"

#ifdef HAL_USB
void usb_printf(char* fmt,...)
{
    uint16_t len = 0;
    uint8_t buf[250] = {0};
    va_list ap;

    va_start(ap, fmt);
    len = vsprintf((char*)buf, fmt, ap);
    va_end(ap);
    
    if(len > 0)
        usb_transmit(buf, len);
}
#endif
