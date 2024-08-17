
#include "motor.h"
#include "can.h"



motor_inf_Str motor_inf[4];
void Get_motor_inf(CAN_RxHeaderTypeDef* RxMessage,u8* data)
{
	
	switch(RxMessage->StdId)
	{
		case 0x201:
			motor_inf[0].angle = ((uint16_t)data[0]<<8) + (uint16_t)data[1];
			motor_inf[0].speed = ((int16_t)data[2]<<8) + (int16_t)data[3];
			motor_inf[0].current = ((int16_t)data[4]<<8) + (int16_t)data[5];
			motor_inf[0].temperature = data[6];
			break;
		case 0x202:
			motor_inf[1].angle = ((uint16_t)data[0]<<8) + (uint16_t)data[1];
			motor_inf[1].speed = ((int16_t)data[2]<<8) + (int16_t)data[3];
			motor_inf[1].current = ((int16_t)data[4]<<8) + (int16_t)data[5];
			motor_inf[1].temperature = data[6];
			break;
		case 0x203:
			motor_inf[2].angle = ((uint16_t)data[0]<<8) + (uint16_t)data[1];
			motor_inf[2].speed = ((int16_t)data[2]<<8) + (int16_t)data[3];
			motor_inf[2].current = ((int16_t)data[4]<<8) + (int16_t)data[5];
			motor_inf[2].temperature = data[6];
			break;
		case 0x204:
			motor_inf[3].angle = ((uint16_t)data[0]<<8) + (uint16_t)data[1];
			motor_inf[3].speed = ((int16_t)data[2]<<8) + (int16_t)data[3];
			motor_inf[3].current = ((int16_t)data[4]<<8) + (int16_t)data[5];
			motor_inf[3].temperature = data[6];

			break;
		default:
			break;
	}
			
}

motor_cur_Str motor_cur[4];
void Send_cur(void)
{
		u8 msg[8];
		msg[0] = BYTE1(motor_cur[0].cur);
		msg[1] = BYTE0(motor_cur[0].cur);
		msg[2] = BYTE1(motor_cur[1].cur);
		msg[3] = BYTE0(motor_cur[1].cur);
		msg[4] = BYTE1(motor_cur[2].cur);
		msg[5] = BYTE0(motor_cur[2].cur);
		msg[6] = BYTE1(motor_cur[3].cur);
		msg[7] = BYTE0(motor_cur[3].cur);

		CAN_Send_Msg(&hcan1,msg,0x200,8);
	
}


int ABS_angle;
void Get_ABS_angle(void)
{
	static int16_t last_angle,Err,Err1,Err2,Err3;
	
	Err1 = motor_inf[3].angle - last_angle;
	Err2 = motor_inf[3].angle - last_angle +8191;
	Err3 = motor_inf[3].angle - last_angle -8191;
	Err  = ((ABS(Err1)<ABS(Err2))?Err1:Err2);
	ABS_angle += ((ABS(Err)<ABS(Err3))?Err:Err3);
	last_angle=motor_inf[3].angle;////////////////////////计算实际角度
//	printf("%d\r\t%d\r\t%d\r\n",motor_inf[3].angle,ABS_angle,last_angle);
}



