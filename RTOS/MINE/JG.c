#include "JG.h"



////////////////////////////激光测距发送指令(部分)//////////////
////////////////////////////////////////////////////////////////
//单次测量
	char SingleMea[4]={0x80,0x06,0x02,0x78};
	
//关机
	char Switch_Off[4]={0x80,0x04,0x02,0x7A};
	
	
//连续测量
	char Cont_Mea[4]={0x80,0x06,0x03,0x77};//80 06 03 77
	
//连续测量间隔时间
	char Cont_Mea_time[5]={0xFA,0x04,0x05,0x00,0xFD};
	
//设置地址(01)
	char Set_addr[5]={0xFA,0x04,0x01,0x80,0x81};
	
//设置量程(10m)
	char Range[5]= {0xFA,0x04,0x09,0x0A,0xEF};
	
//设置频率(10Hz)
	char Set_freq[5]={0xFA,0x04,0x0A,0x0A,0xEE};
	
//设置分辨率(1mm)
	char Set_accuracy[5]={0xFA,0x04,0x0C,0x01,0xF5};
	
//上电就测(开启)
	char Mea_On[5]={0xFA,0x04,0x0D,0x01,0xF4};
	
//控制激光开启
	char Ctrl_On[5]={0x80,0x06,0x05,0x01,0x74};
		
//控制激光关闭
	char Ctrl_Off[5]={0x80,0x06,0x05,0x00,0x75};
////////////////////////////////////////////////////////////////////////////////
	

void JG_Command_SET(UART_HandleTypeDef *huart)
{

	UART_Send_Data(huart, Set_addr, 5);//地址设置为   FA 04 01 80 81
	HAL_Delay(100);
	UART_Send_Data(huart, Range, 5);//设置量程(10m)  FA 04 09 0A EF
	HAL_Delay(100);
	UART_Send_Data(huart, Set_accuracy, 5);//设置分辨率(1mm)  FA 04 0C 01 F5
	HAL_Delay(100);
	UART_Send_Data(huart, Cont_Mea_time, 5);//连续测量间隔时间  FA 04 05 00 FD
	HAL_Delay(100);
	UART_Send_Data(huart, Set_freq, 5);//设置频率(10Hz)  FA 04 0A 0A EE
	HAL_Delay(100);
	UART_Send_Data(huart, Mea_On, 5);//上电就测(开启)  FA 04 0D 01 F4
	HAL_Delay(100);
	UART_Send_Data(huart, Cont_Mea, 4);//连续测量  80 06 03 77
	HAL_Delay(100);
}

void UART_Send_Data(UART_HandleTypeDef *huart, char* point, u8 Length)
{
	__HAL_UART_GET_FLAG(huart,UART_FLAG_TC);
	
	while(Length--)
	{
		huart->Instance->DR = (*point++ & (uint16_t)0x01FF);
		while(__HAL_UART_GET_FLAG(huart,UART_FLAG_TC)!=SET);
	}
}

void USART_SendData(UART_HandleTypeDef *huart, u8 data)
{
	huart->Instance->DR = (data & (uint16_t)0x01FF);
	while(__HAL_UART_GET_FLAG(huart,UART_FLAG_TC)!=SET);
}






void Get_JG_inf(UART_HandleTypeDef *huart,u32* pos,u8* uart_rxbuff)
{
	static u8 rxbuff[11];
	static u8 sum;
	if(RESET!=__HAL_UART_GET_FLAG(huart,UART_FLAG_IDLE))
{
		__HAL_UART_CLEAR_IDLEFLAG(huart);

		memcpy(rxbuff,uart_rxbuff,11);
		memset(uart_rxbuff,0,JG_data_length);
		sum = rxbuff[0]+rxbuff[1]+rxbuff[2]+rxbuff[3]+rxbuff[4]+rxbuff[5]+rxbuff[6]+rxbuff[7]+rxbuff[8]+rxbuff[9];
		sum = ~sum +1; 
		if((rxbuff[0]== 0x80)&&(rxbuff[1]== 0x06)&&(rxbuff[2]== 0x83)&&(sum == rxbuff[10])) 
		{
			sum=0;
			if((rxbuff[3]=='E') && (rxbuff[4]=='R') && (rxbuff[5]=='R'))
			{
				if((rxbuff[8]==0x31) && (rxbuff[9]==0x30))printf("Low Battery\r\n");//电量低
				if((rxbuff[8]==0x31) && (rxbuff[9]==0x34))printf("caculation is wrong\r\n");//计算错误
				if((rxbuff[8]==0x31) && (rxbuff[9]==0x35))printf("out of range\r\n");//超出量程
				if((rxbuff[8]==0x31) && (rxbuff[9]==0x36))printf("weak signal or too long measurement\r\n");//信号弱或者测量时间过长
				if((rxbuff[8]==0x31) && (rxbuff[9]==0x38))printf("Light is too strong\r\n");//环境光太强
				if((rxbuff[8]==0x32) && (rxbuff[9]==0x36))printf("out of display\r\n");//超出显示范围
			}
			else *pos = (rxbuff[3]-'0')*100000 + (rxbuff[4]-'0')*10000 + (rxbuff[5]-'0')*1000 + (rxbuff[7]-'0')*100 + (rxbuff[8]-'0')*10;
			
			
		}
			HAL_UART_Receive_DMA(huart,uart_rxbuff,JG_data_length);
		}
}











