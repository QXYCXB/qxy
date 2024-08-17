#ifndef __BLUE_H__
#define __BLUE_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

void Get_Blue_inf(UART_HandleTypeDef *huart,u8* uart_rxbuff);
void Blue_USART3_Init(void);

#ifdef __cplusplus
}
#endif

#endif


