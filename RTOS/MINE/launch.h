



#ifndef _LAUNCH_H_
#define _LAUNCH_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

#define BYTE0(data)  (*((char *)(&data) + 0))
#define BYTE1(data)  (*((char *)(&data) + 1))
#define BYTE2(data)  (*((char *)(&data) + 2))
#define BYTE3(data)  (*((char *)(&data) + 3))
	
//电机返回参数结构体
typedef struct{
	uint16_t angle;//转子角度  范围0~8191  对应0~360度
	int16_t speed;//转子速度
	int16_t current;//实际电流
	uint8_t temperature;//电机温度  单位摄氏度
}launch_inf_Str;

//电机发送电流结构体
typedef struct{
	int16_t cur;
}launch_cur_Str;


extern launch_inf_Str launch_inf[8];
extern launch_cur_Str launch_cur[8];
void Get_launch_inf(CAN_RxHeaderTypeDef* RxMessage,u8* data);
void Send_cur_launch(void);

#ifdef __cplusplus
}
#endif
#endif


