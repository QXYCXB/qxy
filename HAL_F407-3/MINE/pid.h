#ifndef _PID_H_
#define _PID_H_

#define max(x,y) (x>y?x:y)
#define min(x,y) (x<y?x:y)
#define limit(x,y,z) ((min(x,y))>z?(min(x,y)):(min(max(x,y),z)))   //限幅
#define limitt(x,a,b) (min(max(x,a),b))        //限幅  要求a<b
#define ABS(x) ((x) > 0 ? (x) : -(x))
#include "main.h"
typedef struct{
	float Kp;    //pid参数
	float Ki;
	float Kd;
	
	float Err;   //误差
	float Err1;
	float Err2; 
	
	float Isum;  //积分
	
	float Exp;   //期望值  测量值  输出值
	float Mea;
	float Out;
	
	float Imax;  //积分限幅
	
	float Omin;  //输出限幅
	float Omax;
}PID_Str;

void PID_Init(float Kp,float Ki,float Kd,float Imax,float Omin,float Omax,PID_Str *PID);
void PID_Reset(PID_Str *PID);
void PID_Update_Pos(PID_Str *PID,float limit);
void PID_Update_Inc(PID_Str *PID);
void PID_Update_Pos_angle(PID_Str *PID);
void PID_Update_Inc_Angle(PID_Str *PID);


#endif
