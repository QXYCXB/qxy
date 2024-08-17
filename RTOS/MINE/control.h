#ifndef __CONTR_H__
#define __CONTR_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

#include "SBUS.h"

void Move_Car(void);
void Move_Analys(float* M1,float* M2,float* M3,float Agle);
void New_Move_car(void);

extern int channel_1,channel_2,channel_3,channel_4;
extern int SpeedExp;
extern int Xdata,Ydata;
extern float beat;


#ifdef __cplusplus
}
#endif
#endif
