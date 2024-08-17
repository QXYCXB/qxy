#include "blue.h"

#include "usart.h"
#include "all.h"
//uint8_t blue_flag=0;
typedef union{
	int data;
	uint8_t array[4];
}INT_M;
void Get_Blue_inf(UART_HandleTypeDef *huart,u8* uart_rxbuff)
{
	static u8 rxbuff[Blue_data_length];
	static u8 sum;
	static FloatTypedef KP,KI,KD;
	static INT_M SPEED;
	if(RESET!=__HAL_UART_GET_FLAG(huart,UART_FLAG_IDLE))
	{
		__HAL_UART_CLEAR_IDLEFLAG(huart);

		memcpy(rxbuff,uart_rxbuff,Blue_data_length);
		memset(uart_rxbuff,0,Blue_data_length);
	
////		HAL_UART_Transmit(&huart1, rxbuff, 21, 0xffff);
////		A5 01 9A 99 99 3F CD CC 8C 3F CD CC 8C 3F D4 5A 
		sum = rxbuff[1]+rxbuff[2]+rxbuff[3]+rxbuff[4]+rxbuff[5]+rxbuff[6]+rxbuff[7]+rxbuff[8]+rxbuff[9]+rxbuff[10]+rxbuff[11]+rxbuff[12]+rxbuff[13]+rxbuff[14]+rxbuff[15]+rxbuff[16]+rxbuff[17]+rxbuff[18];
		sum = sum +0;
		if((rxbuff[1]== 0x01)&&(rxbuff[0]== 0xA5)&&(rxbuff[20]== 0x5A)&&(rxbuff[19]==sum))
		{
			sum=0;
			
			SPEED.array[0]=rxbuff[3];
			SPEED.array[1]=rxbuff[4];
			SPEED.array[2]=rxbuff[5];
			SPEED.array[3]=rxbuff[6];
			
			KP.array[0]=rxbuff[7];
			KP.array[1]=rxbuff[8];
			KP.array[2]=rxbuff[9];
			KP.array[3]=rxbuff[10];
			
			KI.array[0]=rxbuff[11];
			KI.array[1]=rxbuff[12];
			KI.array[2]=rxbuff[13];
			KI.array[3]=rxbuff[14];
			
			KD.array[0]=rxbuff[15];
			KD.array[1]=rxbuff[16];
			KD.array[2]=rxbuff[17];
			KD.array[3]=rxbuff[18];
			
			k210.Kp=KP.data;
			k210.Ki=KI.data;
			k210.Kd=KD.data;
			speedExp=SPEED.data;
			HAL_UART_Transmit_DMA(huart,rxbuff,Blue_data_length);
			HAL_UART_Transmit_DMA(huart,rxbuff,Blue_data_length);
			HAL_UART_Transmit_DMA(huart,rxbuff,Blue_data_length);
			if(rxbuff[2]==1)speedExp=0;
//			printf("%.2f %.2f %.2f\r\n",KP.data,KI.data,KD.data);
		}
		else{}

			
			HAL_UART_Receive_DMA(huart,uart_rxbuff,Blue_data_length);//Blue_data_length
		}
}



void Blue_USART3_Init(void)
{
	__HAL_UART_ENABLE_IT(&huart3,UART_IT_IDLE);
	HAL_UART_Receive_DMA(&huart3,Blue_rxbuff,Blue_data_length);
}







