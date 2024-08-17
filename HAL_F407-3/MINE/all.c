#include "all.h"

#include "motor.h"
#include "jy61.h"
#include "blue.h"
#include "usart.h"
#include "key.h"
int M1,M2,M3,M4;
PID_Str Motor[2];
PID_Str k210;
float kp,ki,kd;
int speedd;
int speedExp;
int STOP=1,s=0;
uint8_t times=0;
void All_Init(void)
{
	PID_Init(60,0.002,0,20,-5000,5000,&Motor[0]);
	PID_Init(60,0.002,0,20,-5000,5000,&Motor[1]);
	PID_Init(5,0,0,10,-5000,5000,&k210);
	
	
	 
	
	///////1100-------5
	///////
}



void SpeedUpdate(void)
{
	
	k210.Exp=120;
	
	if(MODE==0)k210.Mea=Outside;
	else k210.Mea=Inside;
	
	if(stop_flag==1)
	{
		times++;
		stop_flag=0;
		if(MODE==0&&circle==1)
		{
			if(times==2)
			{
				speedExp=950;
				k210.Kp=3;
				k210.Ki=0;
				k210.Kd=8;
				circle=0;
				MODE=1;
			}
		else{}
			goto JM1;
		}
		else
		{
			
		}
		speedExp=0;
			JM1:;
	}

	PID_Update_Pos(&k210,0);
	
	Motor[0].Exp=speedExp+k210.Out;
	Motor[1].Exp=speedExp-k210.Out;
	Get_Encoder_Data(&M1,&M2,&M3,&M4);
	Motor[0].Mea=M3;
	Motor[1].Mea=M4;
	PID_Update_Pos(&Motor[0],2);
	PID_Update_Pos(&Motor[1],2);
	send_speed_date(3,(int)Motor[0].Out);
	send_speed_date(4,(int)Motor[1].Out);
}



//EST_err:estimate error
//MEA_err:measure error
float First_kalman(float measure,float EST_err,float MEA_err)
{
	float Kk,Zk;
	static float Xk=0;//initial estimate 
	//Xk :estimate
	//Zk:Kalman Gain
	Zk=measure;
	Kk = EST_err/(EST_err+MEA_err);
	Xk = Xk+Kk*(Zk-Xk);
	EST_err = (1-Kk)*EST_err;
	return Xk;
}




void vofa_send_float(float* data,u8 len)
{
	static char tail[4] = {0x00, 0x00, 0x80, 0x7f};
	HAL_UART_Transmit(&huart1, (u8 *)data, sizeof(float) * len,100);
  HAL_UART_Transmit(&huart1, (u8 *)tail, 4, 100);
}



void UART_Send_Data(UART_HandleTypeDef *huart, u8* point, u8 Length)
{
	__HAL_UART_GET_FLAG(huart,UART_FLAG_TC);
	
	while(Length--)
	{
		huart->Instance->DR = (*point++ & (uint16_t)0x01FF);
		while(__HAL_UART_GET_FLAG(huart,UART_FLAG_TC)!=SET);
	}
}


