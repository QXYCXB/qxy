#ifndef __JY61_H__
#define __JY61_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"


typedef struct 
{
	float Ax;  //三轴加速度
	float Ay;
	float Az;
	float wx;  //三轴角速度
	float wy;
	float wz;
	float ROLL;  //欧拉角
	float PITCH;
	float YAW;
	float T;  //温度
}jy61_inf_str;

extern jy61_inf_str jy61_inf;



void Get_JY61_inf(UART_HandleTypeDef *huart,u8* uart_rxbuff);
void jy61_USART4_Init(void);


#ifdef __cplusplus
}
#endif

#endif


