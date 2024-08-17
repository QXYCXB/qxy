#include "k210.h"
#include "usart.h"
#include "all.h"
u8 usart6_byte,usart5_byte;
int Inside,Outside;
bool stop_flag=0;
uint8_t blue_flag=0;


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	static u8 usart6_rxbuff[10] = {0x00};  //帧数据缓存
	static u8 count = 0;  //计数标志  校验和
	if(huart->Instance==USART6)
	{
		if((count==0) && (usart6_byte!='A'))goto JM;;
		if((count==8) && (usart6_byte!='\r'))goto JM;
		if((count==9) && (usart6_byte!='\n'))goto JM;
		usart6_rxbuff[count++] = usart6_byte;
		if(count == 10)
		{
			count = 0;
			Inside = (usart6_rxbuff[1]-'0')*100+(usart6_rxbuff[2]-'0')*10+usart6_rxbuff[3]-'0';
			Outside = (usart6_rxbuff[4]-'0')*100+(usart6_rxbuff[5]-'0')*10+usart6_rxbuff[6]-'0';
			stop_flag = usart6_rxbuff[7]-'0';
		}
		JM:;
		HAL_UART_Receive_IT(&huart6, &usart6_byte, 1);
	}
	else if(huart->Instance==UART5)
	{
		blue_flag=usart5_byte;
		HAL_UART_Receive_IT(&huart5, &usart5_byte, 1);
		
	}
	else{}
}


void K210_USART6_Init(void)
{
	HAL_UART_Receive_IT(&huart5, &usart5_byte, 1);
	HAL_UART_Receive_IT(&huart6, &usart6_byte, 1);
	while(Inside==0)printf("k210 connection failure\r\n");
}





