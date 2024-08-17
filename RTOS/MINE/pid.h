#ifndef _PID_H_
#define _PID_H_

#define max(x,y) (x>y?x:y)
#define min(x,y) (x<y?x:y)
#define limit(x,y,z) ((min(x,y))>z?(min(x,y)):(min(max(x,y),z)))   //�޷�
#define limitt(x,a,b) (min(max(x,a),b))        //�޷�  Ҫ��a<b
#define ABS(x) ((x) > 0 ? (x) : -(x))
#include "main.h"
typedef struct{
	float Kp;    //pid����
	float Ki;
	float Kd;
	
	float Err;   //���
	float Err1;
	float Err2; 
	
	float Isum;  //����
	
	float Exp;   //����ֵ  ����ֵ  ���ֵ
	float Mea;
	float Out;
	
	float Imax;  //�����޷�
	
	float Omin;  //����޷�
	float Omax;
}PID_Str;

void PID_Init(float Kp,float Ki,float Kd,float Imax,float Omin,float Omax,PID_Str *PID);
void PID_Reset(PID_Str *PID);
void PID_Update_Pos(PID_Str *PID,float limit);
void PID_Update_Inc(PID_Str *PID);
void PID_Update_Pos_angle(PID_Str *PID);
void PID_Update_Inc_Angle(PID_Str *PID);


#endif
