#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 
typedef struct{
	u8 my_id;
	u8 to_id;
	u8 RX_data[20];
	u8 TX_data[20];
}UART_Str;
extern UART_Str Str1;
void uart_init(u32 bound);
void MY_Send_Data(USART_TypeDef* USARTx, char* point, u8 Length);
#endif


