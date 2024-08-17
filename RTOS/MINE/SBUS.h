

#ifndef _SBUS_H_
#define _SBUS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

#define SBUS_KEY0	(SBusRemote.Channel[8]<1000 ? 1:0)
#define SBUS_KEY1	(SBusRemote.Channel[9]<1000 ? 1:0)



typedef struct
{
    uint16_t Channel[16];
}SBusRemote_t;


extern SBusRemote_t SBusRemote;




void Get_SBUS_inf(UART_HandleTypeDef *huart,u8* uart_rxbuff);
u8 Sbus_key(u8 mode);

#ifdef __cplusplus
}
#endif
#endif





