#ifndef __ALL_H
#define __ALL_H

#ifdef __cplusplus
extern "C" {
#endif


#include "main.h"

#include "pid.h"

void All_Init(void);

void SpeedUpdate(void);
void vofa_send_float(float* data,u8 len);
float First_kalman(float measure,float EST_err,float MEA_err);
void UART_Send_Data(UART_HandleTypeDef *huart, u8* point, u8 Length);
extern int STOP;
extern int speedExp;
extern PID_Str Motor[2], k210;
extern int M1,M2,M3,M4;
#ifdef __cplusplus
}
#endif

#endif 
