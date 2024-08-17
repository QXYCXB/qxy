#ifndef __ACTION_H__
#define __ACTION_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

typedef struct{
	float pos_x;       //x×ø±ê
	float pos_y;       //y×ø±ê
	float angle_x;     //¸©Ñö½Ç
	float angle_y;     //ºá¹ö½Ç
	float angle_z;     //º½Ïò½Ç
	float w;           //º½Ïò½ÇËÙ¶È
}ACT_inf_Str;


void  Get_action_inf(UART_HandleTypeDef *huart,u8* uart_rxbuff);
void send_ACT0(void);
extern ACT_inf_Str action_inf;



#ifdef __cplusplus
}
#endif
#endif
