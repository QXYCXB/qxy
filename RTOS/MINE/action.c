
#include "action.h"
#include "usart.h"

uint8_t actionData[28];
ACT_inf_Str action_inf;

void  Get_action_inf(UART_HandleTypeDef *huart,u8* uart_rxbuff)
{
	if(RESET!=__HAL_UART_GET_FLAG(huart,UART_FLAG_IDLE))
	{
		__HAL_UART_CLEAR_IDLEFLAG(huart);
		memcpy(actionData,uart_rxbuff,28);
		memset(uart_rxbuff,0,action_data_length);
		static union
	{
		uint8_t data[24];
		float ActVal[6];
	}posture;
	
	if(actionData[0] == 0x0d&&actionData[1] == 0x0a&&actionData[26] == 0x0a&&actionData[27] == 0x0d)
	{
		memcpy(posture.data,&actionData[2],24);
		action_inf.angle_z = posture.ActVal[0]<0 ? (360+posture.ActVal[0]) : posture.ActVal[0];   //0-360
		action_inf.angle_x = posture.ActVal[1];
		action_inf.angle_y = posture.ActVal[2];
		action_inf.pos_x = posture.ActVal[3];
		action_inf.pos_y = posture.ActVal[4];
		action_inf.w = posture.ActVal[5];
	}
		
		HAL_UART_Receive_DMA(huart,uart_rxbuff,action_data_length);
	}
	
}



void send_ACT0(void)
{
	u8 buf[] = {'A','C','T','0'};
	u8 i;
	for(i=0;i<4;i++)
	{
		while((USART3->SR&0X40)==0);  //等待上一次发送完毕
    USART3->DR=buf[i];
	}
}
 


