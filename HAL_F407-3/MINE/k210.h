#ifndef __K210_H__
#define __K210_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

void Get_k210_inf(UART_HandleTypeDef *huart,u8* uart_rxbuff);
void K210_USART6_Init(void);
extern uint8_t blue_flag;

#ifdef __cplusplus
}
#endif

#endif


