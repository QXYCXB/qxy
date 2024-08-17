#include "SBUS.h"
#include "JG.h"
#include "usart.h"
u8 SBusData[25];
SBusRemote_t SBusRemote; 
void Get_SBUS_inf(UART_HandleTypeDef *huart,u8* uart_rxbuff)
{
	
	if(RESET!=__HAL_UART_GET_FLAG(huart,UART_FLAG_IDLE))
	{
		__HAL_UART_CLEAR_IDLEFLAG(huart);
//		UART_Send_Data(&huart1,(char*)uart_rxbuff, 25);
		memcpy(SBusData,uart_rxbuff,25);
		memset(uart_rxbuff,0,sbus_data_length);
		if(SBusData[0] == 0x0F)
		{
			SBusRemote.Channel[0]  = ((SBusData[1]    |SBusData[2]<<8)                  & 0x07FF);
			SBusRemote.Channel[1]  = ((SBusData[2]>>3 |SBusData[3]<<5)                  & 0x07FF);
			SBusRemote.Channel[2]  = ((SBusData[3]>>6 |SBusData[4]<<2 |SBusData[5]<<10) & 0x07FF);
			SBusRemote.Channel[3]  = ((SBusData[5]>>1 |SBusData[6]<<7)                  & 0x07FF);
			SBusRemote.Channel[4]  = ((SBusData[6]>>4 |SBusData[7]<<4)                  & 0x07FF);
			SBusRemote.Channel[5]  = ((SBusData[7]>>7 |SBusData[8]<<1 |SBusData[9]<<9)  & 0x07FF);
			SBusRemote.Channel[6]  = ((SBusData[9]>>2 |SBusData[10]<<6)                 & 0x07FF);
			SBusRemote.Channel[7]  = ((SBusData[10]>>5|SBusData[11]<<3)                 & 0x07FF);
			SBusRemote.Channel[8]  = ((SBusData[12]   |SBusData[13]<<8)                 & 0x07FF);
			SBusRemote.Channel[9]  = ((SBusData[13]>>3|SBusData[14]<<5)                 & 0x07FF);
			SBusRemote.Channel[10] = ((SBusData[14]>>6|SBusData[15]<<2|SBusData[16]<<10)& 0x07FF);
			SBusRemote.Channel[11] = ((SBusData[16]>>1|SBusData[17]<<7)                 & 0x07FF);
			SBusRemote.Channel[12] = ((SBusData[17]>>4|SBusData[18]<<4)                 & 0x07FF);
			SBusRemote.Channel[13] = ((SBusData[18]>>7|SBusData[19]<<1|SBusData[20]<<9) & 0x07FF);
			SBusRemote.Channel[14] = ((SBusData[20]>>2|SBusData[21]<<6)                 & 0x07FF);
			SBusRemote.Channel[15] = ((SBusData[21]>>5|SBusData[22]<<3)                 & 0x07FF);
		}
		HAL_UART_Receive_DMA(huart,uart_rxbuff,sbus_data_length);	

	}
}



u8 Sbus_key(u8 mode)
{
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按	
	if(key_up&&(SBUS_KEY0==0||SBUS_KEY1==0))
	{
		HAL_Delay(10);//去抖动 
		key_up=0;
		if(SBUS_KEY0==0)return 1;
		else if(SBUS_KEY1==0)return 2;
		
	}else if(SBUS_KEY0==1&&SBUS_KEY1==1)key_up=1; 	    
 	return 0;// 无按键按下
}






