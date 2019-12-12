#include "hal_uart.h"
#include <stdarg.h>
#include <stdio.h>

#ifdef HAL_UART
UART_HandleTypeDef *printf_port = NULL;
DMA_HandleTypeDef *printf_dma = NULL;

#ifdef __GNUC__
	#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
	#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif
PUTCHAR_PROTOTYPE
{
    HAL_UART_Transmit(printf_port, (uint8_t *)&ch, 1, 10);
    return ch;
}

void uprintf_init(UART_HandleTypeDef *port, DMA_HandleTypeDef *dma)
{
    printf_port = port;
    printf_dma = dma;
}

void uprintf(char * fmt, ...)
{
    uint8_t buf[256] = {0};
    uint8_t len = 0;

    va_list args;
    va_start(args, fmt);
    len = vsprintf((char *)buf, fmt, args);
    va_end(args);

    if(printf_dma != NULL){
        while(printf_dma->State != 1);
        HAL_UART_Transmit_DMA(printf_port, buf, len);
        while(printf_dma->State != 1);
    }
    else{
        HAL_UART_Transmit(printf_port , buf, len, 100);
    }
}
#endif
