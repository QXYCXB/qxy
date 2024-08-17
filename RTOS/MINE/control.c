#include "control.h"



#define L 1//中心到轮子的距离


float Va,Vb,Vc;//各个轮子的速度
float Vx,Vy;//自身坐标系下的分速度
float w;//自身坐标系下角速度
float Agle;//坐标系之间的夹角
float VgX,VgY;////VX,VY :世界坐标系下的分速度



//三轮运动学解析
void Move_Analys(float* M1,float* M2,float* M3,float Agle)
{

	//获取坐标系之间的夹角
	Agle = PI*Agle/180;
	Vx=arm_cos_f32(Agle)*VgX + arm_sin_f32(Agle)*VgY;
	Vy= -arm_sin_f32(Agle)*VgX + arm_cos_f32(Agle)*VgY;
	
	
	Va = Vx + w*L;
	Vb = -Vx*0.5f - Vy*0.866025f + w*L;
	Vc = -Vx*0.5f + Vy*0.866025f + w*L;
	
	*M3=Va;
	*M1=Vb;
	*M2=Vc;

}




int channel_1,channel_2,channel_3,channel_4;
int SpeedExp;
int Xdata,Ydata;
float beat;
void Move_Car(void)
{
	channel_1=SBusRemote.Channel[0]-1023;
	channel_2=SBusRemote.Channel[1]-1023;
	channel_3=SBusRemote.Channel[2]-307;
	channel_4=SBusRemote.Channel[3]-1023;
	SpeedExp = channel_3*4;
	if(SpeedExp<0)SpeedExp=0;
	if((ABS(channel_1)<200)&&(ABS(channel_2)<200)){VgY=0;VgX=0;}
	else 
	{
		Xdata=channel_1;
		Ydata=channel_2;
		beat=atan2f(Xdata*1.0f,Ydata*1.0f);
		if(beat<0)beat+=2*PI;

		VgY=SpeedExp*arm_cos_f32(beat);
		VgX=SpeedExp*arm_sin_f32(beat);
	}
		if((ABS(channel_4)>100))
		{
			w=(channel_4-100)*3;
		}
		else w=0;
//		printf("%.2f\r\t%.2f\r\t%d\r\n",VgX,VgY,SpeedExp);
//		printf("%.2f\r\t%.2f\r\t%.2f\r\n",beat,beat,beat);
}




float X_Value,Y_Value;
void New_Move_car(void)
{
	channel_1=SBusRemote.Channel[0]-1023;
	channel_2=SBusRemote.Channel[1]-1023;
	channel_3=SBusRemote.Channel[2]-307;
	channel_4=SBusRemote.Channel[3]-1023;
	SpeedExp = channel_3*4;
	if(SpeedExp<0)SpeedExp=0;
	X_Value=channel_1/784.0f;
	Y_Value=channel_2/784.0f;
	
	VgX = X_Value*SpeedExp;
	VgY = Y_Value*SpeedExp;
	
	if((ABS(channel_1)<200)&&(ABS(channel_2)<200)){VgY=0;VgX=0;}
	
	if((ABS(channel_4)>100))
		{
			w=SpeedExp*((channel_4-100)/(784.0f-100.0f));
		}
		else w=0; 
}




