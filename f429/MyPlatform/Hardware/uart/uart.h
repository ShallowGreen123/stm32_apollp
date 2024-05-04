
#ifndef USART_INLCUDE
#define USART_INLCUDE

#include "hardware.h"
// config
#define USART_REC_LEN 200 //定义最大接收字节数 200
#define RXBUFFERSIZE 1    //缓存大小
// define
#define USART_RX_FINISH (USART_RX_STA & 0x8000)
#define USART_GET_RX_LEN (USART_RX_STA & 0x3fff)
#define USART_DISP_RX_DATA(uart, buf, len)                     \
    do                                                          \
    {                                                           \
        HAL_UART_Transmit(&uart, (uint8_t *)buf, len, 1000);    \
        while (__HAL_UART_GET_FLAG(&uart, UART_FLAG_TC) != SET) \
            ;                                                   \
        USART_RX_STA = 0;                                       \
    } while (0);

// extern
extern uint8_t USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符
extern uint16_t USART_RX_STA;               //接收状态标记
extern UART_HandleTypeDef UART1_Handler;    // UART句柄
extern uint8_t aRxBuffer[RXBUFFERSIZE];     // HAL库USART接收Buffer

#endif
