
#include "launch.h"
#include "can.h"










launch_inf_Str launch_inf[8];
void Get_launch_inf(CAN_RxHeaderTypeDef* RxMessage,u8* Data)
{
	switch(RxMessage->StdId)
	{
		case 0x201:
			launch_inf[0].angle = ((uint16_t)Data[0]<<8) + (uint16_t)Data[1];
			launch_inf[0].speed = ((int16_t)Data[2]<<8) + (int16_t)Data[3];
			launch_inf[0].current = ((int16_t)Data[4]<<8) + (int16_t)Data[5];
			launch_inf[0].temperature = Data[6];
			break;
		
		case 0x202:
			launch_inf[1].angle = ((uint16_t)Data[0]<<8) + (uint16_t)Data[1];
			launch_inf[1].speed = ((int16_t)Data[2]<<8) + (int16_t)Data[3];
			launch_inf[1].current = ((int16_t)Data[4]<<8) + (int16_t)Data[5];
			launch_inf[1].temperature = Data[6];
			break;
		
		case 0x203:
			launch_inf[2].angle = ((uint16_t)Data[0]<<8) + (uint16_t)Data[1];
			launch_inf[2].speed = ((int16_t)Data[2]<<8) + (int16_t)Data[3];
			launch_inf[2].current = ((int16_t)Data[4]<<8) + (int16_t)Data[5];
			launch_inf[2].temperature = Data[6];
			break;
		
		case 0x204:
			launch_inf[3].angle = ((uint16_t)Data[0]<<8) + (uint16_t)Data[1];
			launch_inf[3].speed = ((int16_t)Data[2]<<8) + (int16_t)Data[3];
			launch_inf[3].current = ((int16_t)Data[4]<<8) + (int16_t)Data[5];
			launch_inf[3].temperature = Data[6];
			break;
		case 0x205:
			launch_inf[4].angle = ((uint16_t)Data[0]<<8) + (uint16_t)Data[1];
			launch_inf[4].speed = ((int16_t)Data[2]<<8) + (int16_t)Data[3];
			launch_inf[4].current = ((int16_t)Data[4]<<8) + (int16_t)Data[5];
			launch_inf[4].temperature = Data[6];
			break;
		
		case 0x206:
			launch_inf[5].angle = ((uint16_t)Data[0]<<8) + (uint16_t)Data[1];
			launch_inf[5].speed = ((int16_t)Data[2]<<8) + (int16_t)Data[3];
			launch_inf[5].current = ((int16_t)Data[4]<<8) + (int16_t)Data[5];
			launch_inf[5].temperature = Data[6];
			break;
		
		case 0x207:
			launch_inf[6].angle = ((uint16_t)Data[0]<<8) + (uint16_t)Data[1];
			launch_inf[6].speed = ((int16_t)Data[2]<<8) + (int16_t)Data[3];
			launch_inf[6].current = ((int16_t)Data[4]<<8) + (int16_t)Data[5];
			launch_inf[6].temperature = Data[6];
			break;
		
		case 0x208:
			launch_inf[7].angle = ((uint16_t)Data[0]<<8) + (uint16_t)Data[1];
			launch_inf[7].speed = ((int16_t)Data[2]<<8) + (int16_t)Data[3];
			launch_inf[7].current = ((int16_t)Data[4]<<8) + (int16_t)Data[5];
			launch_inf[7].temperature = Data[6];
			break;
		
		default:
			break;
	}
}


launch_cur_Str launch_cur[8];
void Send_cur_launch(void)
{
		u8 msg[8],msg2[8];
		msg[0] = BYTE1(launch_cur[0].cur);
		msg[1] = BYTE0(launch_cur[0].cur);
		msg[2] = BYTE1(launch_cur[1].cur);
		msg[3] = BYTE0(launch_cur[1].cur);
		msg[4] = BYTE1(launch_cur[2].cur);
		msg[5] = BYTE0(launch_cur[2].cur);
		msg[6] = BYTE1(launch_cur[3].cur);
		msg[7] = BYTE0(launch_cur[3].cur);

		msg2[0] = BYTE1(launch_cur[4].cur);
		msg2[1] = BYTE0(launch_cur[4].cur);
		msg2[2] = BYTE1(launch_cur[5].cur);
		msg2[3] = BYTE0(launch_cur[5].cur);
		msg2[4] = BYTE1(launch_cur[6].cur);
		msg2[5] = BYTE0(launch_cur[6].cur);
		msg2[6] = BYTE1(launch_cur[7].cur);
		msg2[7] = BYTE0(launch_cur[7].cur);
	

	CAN_Send_Msg(&hcan2,msg,0x200,8);
	CAN_Send_Msg(&hcan2,msg2,0x1FF,8);
		
}





