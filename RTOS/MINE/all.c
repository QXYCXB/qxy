#include "all.h"

extern int ABS_angle;
extern float VgX,VgY;////VX,VY :世界坐标系下的分速度
extern float w;//自身坐标系下角速度
 bool MODE;
float Goal_pos_X,Goal_pos_Y,Goal_Angel;
int Goal_JZ;
int launch_Exp1,launch_Exp2;

float action_init=0;

PID_Str Motor[3];//底盘
PID_Str Shoot[8];//发射
PID_Str Angel;
PID_Str Pos_X;//位置
PID_Str Pos_Y;
PID_Str JG_X;
PID_Str JG_Y;//////
PID_Str JZ_RealAngle;

int initial_angle;

//9.0f,0.75f,1.0f,100.0f,-16000,16000
void ALL_PID_Init(void)
{
	PID_Init(9.0f,0.75f,1.0f,100.0f,-16000,16000,&Shoot[0]);
	PID_Init(9.0f,0.75f,1.0f,100.0f,-16000,16000,&Shoot[1]);
	PID_Init(9.0f,0.75f,1.0f,100.0f,-16000,16000,&Shoot[2]);
	PID_Init(9.0f,0.75f,1.0f,100.0f,-16000,16000,&Shoot[3]);
	PID_Init(9.0f,0.75f,1.0f,100.0f,-16000,16000,&Shoot[4]);
	PID_Init(9.0f,0.75f,1.0f,100.0f,-16000,16000,&Shoot[5]);
	PID_Init(9.0f,0.75f,1.0f,100.0f,-16000,16000,&Shoot[6]);
	PID_Init(9.0f,0.75f,1.0f,100.0f,-16000,16000,&Shoot[7]);
	
	PID_Init(6.0f,0.8f,1.0f,100.0f,-16000,16000,&Motor[0]);
	PID_Init(6.0f,0.8f,1.0f,100.0f,-16000,16000,&Motor[1]);
	PID_Init(6.0f,0.8f,1.0f,100.0f,-16000,16000,&Motor[2]);

	PID_Init(80.0f,0,0,0,-3000,3000,&Angel);//37
	PID_Init(3.5f,0,0,0,-4000,4000,&Pos_X);
	PID_Init(2.0f,0,0,0,-4000,4000,&Pos_Y);
	PID_Init(0.035,0,1.2,0,-9000,9000,&JZ_RealAngle);	
	FaShe = 0;
	LED1=1;
	Goal_pos_Y=0;
	Goal_pos_X=0;
	Goal_Angel=0;
	
	
	
	HAL_Delay(100);
	Goal_JZ = JZ_RealAngle.Mea-(100000-8191*2);
	initial_angle=Goal_JZ;

	while(motor_inf[0].angle==0)printf("motor1 connection failure\r\n");
	while(motor_inf[1].angle==0)printf("motor2 connection failure\r\n");
	while(motor_inf[2].angle==0)printf("motor3 connection failure\r\n");
	while(motor_inf[3].angle==0)printf("motor4 connection failure\r\n");
	
	while(launch_inf[0].angle==0)printf("launch1 connection failure\r\n");
	while(launch_inf[1].angle==0)printf("launch2 connection failure\r\n");
	while(launch_inf[2].angle==0)printf("launch3 connection failure\r\n");
	while(launch_inf[3].angle==0)printf("launch4 connection failure\r\n");
	while(launch_inf[4].angle==0)printf("launch5 connection failure\r\n");
	while(launch_inf[5].angle==0)printf("launch6 connection failure\r\n");
	while(launch_inf[6].angle==0)printf("launch7 connection failure\r\n");
	while(launch_inf[7].angle==0)printf("launch8 connection failure\r\n");

	while(SBusRemote.Channel[1]==0)printf("Sbus connection failure\r\n");
	printf("Sbus connection successeded\r\n");
//	
//	while(JG_pos_x==0||JG_pos_y==0)printf("JG connection failure\r\n");
//	printf("JG connection successeded");
//	
	while(action_inf.pos_x==0)printf("action connection failure\r\n");
	printf("action connection successeded");
//	launch_Exp1=8000;
//	launch_Exp2=8000;////////////////////////////////////////////6度
	
	
	send_ACT0();
	HAL_Delay(500);
	
	while(action_inf.pos_x==0)printf("action connection failure\r\n");
	printf("action connection successeded");

}


void Speed_Update(void)
{
	JZ_RealAngle.Exp=Goal_JZ;//夹球装置绝对角度期望值
	Angel.Exp=Goal_Angel;//角度期望值
	Pos_X.Exp=Goal_pos_X; //X横坐标期望值
	Pos_Y.Exp=Goal_pos_Y; //Y纵坐标期望值
	
	Shoot[0].Exp = launch_Exp1;
	Shoot[1].Exp = launch_Exp1;
	Shoot[2].Exp = launch_Exp1;
	Shoot[3].Exp = launch_Exp1;
	
	Shoot[4].Exp = launch_Exp2;
	Shoot[5].Exp = launch_Exp2;
	Shoot[6].Exp = launch_Exp2;
	Shoot[7].Exp = launch_Exp2;
	
	Angel.Mea=action_inf.angle_z;//获取实时角度 //航向角
	
	if(SBusRemote.Channel[4]<500)//自动
	{
		MODE=0;
		Pos_X.Mea=action_inf.pos_x;//获取实时横坐标
		Pos_Y.Mea=action_inf.pos_y;//获取实时纵坐标

		PID_Update_Pos_angle(&Angel);//角度PID计算
		PID_Update_Pos(&Pos_X,0);//横坐标 PID计算
		PID_Update_Pos(&Pos_Y,0);//纵坐标 PID计算
		
		w=Angel.Out;
		VgX=-Pos_X.Out;
		VgY=-Pos_Y.Out;
	}
	
	else//手动
	{
		MODE=1;
//		Angel.Mea = 0;
		New_Move_car();
		if(SBusRemote.Channel[5]<500)Goal_JZ = initial_angle; 
		else Goal_JZ = initial_angle - 500000; 
		
		if(SBusRemote.Channel[9]<500)JZ = 0; 
		else JZ = 1;

		if(SBusRemote.Channel[8]<500)Turning = 0; 
		else Turning = 1;
		
		if(SBusRemote.Channel[6]<500)
		{
			launch_Exp1 = 0;
			launch_Exp2 = 0;
			FaShe =0;
			
			
		}
		else if(SBusRemote.Channel[6]>1400)
		{
			FaShe =1;
		}
		
		
		else 
		{
			launch_Exp1 = 5000; 
			launch_Exp2 = 8000;
		}
		
		
	}
		
	Move_Analys(&Motor[0].Exp,&Motor[1].Exp,&Motor[2].Exp,Angel.Mea);//运动学解析
	
//////////////////////////////////////
//	Shoot[0].Exp = 5000;
///////////////////////////////////////////
	
	
	
	if(SBusRemote.Channel[7]<500)
	{
		send_ACT0();
		Motor[0].Exp=0;Motor[1].Exp=0;Motor[2].Exp=0;
		Shoot[0].Exp=0;Shoot[1].Exp=0;Shoot[2].Exp=0;Shoot[3].Exp=0;
		Shoot[4].Exp=0;Shoot[5].Exp=0;Shoot[6].Exp=0;Shoot[7].Exp=0;
	}//急停
	
	
	
	Motor[0].Mea = motor_inf[0].speed; 	                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
	Motor[1].Mea = motor_inf[1].speed;
	Motor[2].Mea = motor_inf[2].speed;
	JZ_RealAngle.Mea=ABS_angle;
	
	Shoot[0].Mea = launch_inf[0].speed;
	Shoot[1].Mea = launch_inf[1].speed;
	Shoot[2].Mea = launch_inf[2].speed;
	Shoot[3].Mea = launch_inf[3].speed;
	Shoot[4].Mea = launch_inf[4].speed;
	Shoot[5].Mea = launch_inf[5].speed;
	Shoot[6].Mea = launch_inf[6].speed;
	Shoot[7].Mea = launch_inf[7].speed;
	
	
	
	PID_Update_Pos(&JZ_RealAngle,100);
	PID_Update_Inc(&Motor[0]);
	PID_Update_Inc(&Motor[1]);
	PID_Update_Inc(&Motor[2]);
	PID_Update_Inc(&Shoot[0]);
	PID_Update_Inc(&Shoot[1]);
	PID_Update_Inc(&Shoot[2]);
	PID_Update_Inc(&Shoot[3]);
	PID_Update_Inc(&Shoot[4]);
	PID_Update_Inc(&Shoot[5]);
	PID_Update_Inc(&Shoot[6]);
	PID_Update_Inc(&Shoot[7]);
	
	motor_cur[0].cur += (int)(Motor[0].Out+0.5f);
	motor_cur[1].cur += (int)(Motor[1].Out+0.5f);
	motor_cur[2].cur += (int)(Motor[2].Out+0.5f);
	motor_cur[3].cur  = (int)(JZ_RealAngle.Out);
	
	launch_cur[0].cur += (int)(Shoot[0].Out+0.5f);
	launch_cur[1].cur += (int)(Shoot[1].Out+0.5f);
	launch_cur[2].cur += (int)(Shoot[2].Out+0.5f);
	launch_cur[3].cur += (int)(Shoot[3].Out+0.5f);
	launch_cur[4].cur += (int)(Shoot[4].Out+0.5f);
	launch_cur[5].cur += (int)(Shoot[5].Out+0.5f);
	launch_cur[6].cur += (int)(Shoot[6].Out+0.5f);
	launch_cur[7].cur += (int)(Shoot[7].Out+0.5f);

	Send_cur();
	Send_cur_launch();
}
	







