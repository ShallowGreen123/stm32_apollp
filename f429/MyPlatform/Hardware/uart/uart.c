
#include "uart.h"
#include <stdio.h>

uint8_t recv_data;
uint8_t recv_buff[100];
uint8_t recv_one_frame = 0;
uint16_t recv_len = 0;

//#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)	
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{ 	
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
	USART1->DR = (uint8_t) ch;      
	return ch;
}
#endif 
//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart == &huart1) {
        recv_buff[recv_len++] = recv_data;
        HAL_UART_Receive_IT(huart,&recv_data, 1);
        if(recv_len > 2){
            if(recv_buff[recv_len - 2] == '\r' && recv_buff[recv_len - 1] == '\n'){
                recv_one_frame = 1;
            }
        }
    }
}
