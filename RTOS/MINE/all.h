#ifndef __JG_H__
#define __JG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

#define FaShe_time 500
#define launch_Speed1 5000//一级发射
#define launch_Speed2 8000//二级发射
#define ANGEL_30 337
#define ANGEL_90 2.63

		
#include <math.h>
#include "JG.h"
#include "action.h"
#include "motor.h"
#include "launch.h"
#include "oled.h"
#include "SBUS.h"
#include "pid.h"
#include "control.h"
void ALL_PID_Init(void);
void Speed_Update(void);

extern	float Goal_pos_X,Goal_pos_Y,Goal_Angel;
extern	int Goal_JZ;
extern	int launch_Exp1,launch_Exp2;

extern	PID_Str Motor[3];//底盘
extern	PID_Str Shoot[8];//发射
extern	PID_Str Angel;
extern	PID_Str Pos_X;//位置
extern	PID_Str Pos_Y;
extern	PID_Str JG_X;
extern	PID_Str JG_Y;//////
extern	PID_Str JZ_RealAngle;

#ifdef __cplusplus
}
#endif
#endif
