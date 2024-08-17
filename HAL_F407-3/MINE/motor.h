#ifndef __Motor_H
#define __Motor_H

#ifdef __cplusplus
extern "C" {
#endif


#include "main.h"




void Get_Encoder_Data(int* M1,int* M2,int* M3,int* M4);
void send_speed_date(u8 id,int speed);

void Motor_Init(void);


#ifdef __cplusplus
}
#endif

#endif 
