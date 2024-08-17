
#ifndef __motor_H__
#define __motor_H__

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
}motor_inf_Str;

typedef struct{
	int16_t cur;
}motor_cur_Str;
	

extern motor_inf_Str motor_inf[4];
extern motor_cur_Str motor_cur[4];






void Get_motor_inf(CAN_RxHeaderTypeDef* RxMessage,u8* data);
void Get_ABS_angle(void);

void Send_cur(void);




#ifdef __cplusplus
}
#endif
#endif
