#ifndef __JY61_H__
#define __JY61_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"


typedef struct 
{
	float Ax;  //������ٶ�
	float Ay;
	float Az;
	float wx;  //������ٶ�
	float wy;
	float wz;
	float ROLL;  //ŷ����
	float PITCH;
	float YAW;
	float T;  //�¶�
}jy61_inf_str;

extern jy61_inf_str jy61_inf;



void Get_JY61_inf(UART_HandleTypeDef *huart,u8* uart_rxbuff);
void jy61_USART4_Init(void);


#ifdef __cplusplus
}
#endif

#endif


