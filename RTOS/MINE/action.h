#ifndef __ACTION_H__
#define __ACTION_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

typedef struct{
	float pos_x;       //x����
	float pos_y;       //y����
	float angle_x;     //������
	float angle_y;     //�����
	float angle_z;     //�����
	float w;           //������ٶ�
}ACT_inf_Str;


void  Get_action_inf(UART_HandleTypeDef *huart,u8* uart_rxbuff);
void send_ACT0(void);
extern ACT_inf_Str action_inf;



#ifdef __cplusplus
}
#endif
#endif
