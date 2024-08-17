#include "jy61.h"
#include "all.h"
#include "usart.h"
jy61_inf_str jy61_inf;
void Get_JY61_inf(UART_HandleTypeDef *huart,u8* uart_rxbuff)
{
	static u8 Rx_buf[33];
	static u8 sum1,sum2,sum3;
	if(RESET!=__HAL_UART_GET_FLAG(huart,UART_FLAG_IDLE))
{
		__HAL_UART_CLEAR_IDLEFLAG(huart);
		
	
		memcpy(Rx_buf,uart_rxbuff,33);
		
		memset(uart_rxbuff,0,jy61_data_length);
//		HAL_UART_Transmit(&huart1, Rx_buf, 33, 0xffff);

		if( Rx_buf[0] != 0x55) return;  //≈–∂œ÷°Õ∑
		if( Rx_buf[11] != 0x55) return;  //≈–∂œ÷°Õ∑
		if( Rx_buf[22] != 0x55) return;  //≈–∂œ÷°Õ∑
	
		if( Rx_buf[1] != 0x51) return; 
		if( Rx_buf[12] != 0x52) return;
		if( Rx_buf[23] != 0x53) return;
	
		sum1 = Rx_buf[0] + Rx_buf[1] + Rx_buf[2] + Rx_buf[3] + Rx_buf[4] + Rx_buf[5] + Rx_buf[6] + Rx_buf[7] + Rx_buf[8] + Rx_buf[9]; //Rx_buf[10]
		sum2 = Rx_buf[11]+ Rx_buf[12]+ Rx_buf[13]+ Rx_buf[14]+ Rx_buf[15]+ Rx_buf[16]+ Rx_buf[17]+ Rx_buf[18]+ Rx_buf[19]+ Rx_buf[20];//Rx_buf[21]
		sum3 = Rx_buf[22]+ Rx_buf[23]+ Rx_buf[24]+ Rx_buf[25]+ Rx_buf[26]+ Rx_buf[27]+ Rx_buf[28]+ Rx_buf[29]+ Rx_buf[30]+ Rx_buf[31];//Rx_buf[32]
		if( Rx_buf[10] != sum1) return;
		if( Rx_buf[21] != sum2) return;
		if( Rx_buf[32] != sum3) return;
		
		sum1=0;sum2=0;sum3=0;
		
		jy61_inf.Ax = (((short)Rx_buf[3]<<8)|Rx_buf[2])/32768.0f*16*9.8f;
		jy61_inf.Ay = (((short)Rx_buf[5]<<8)|Rx_buf[4])/32768.0f*16*9.8f;
		jy61_inf.Az = (((short)Rx_buf[7]<<8)|Rx_buf[6])/32768.0f*16*9.8f;
		jy61_inf.T = (((short)Rx_buf[9]<<8)|Rx_buf[8])/340.0f+36.53f;

		jy61_inf.wx = (((short)Rx_buf[14]<<8)|Rx_buf[13])/32768.0f*2000;
		jy61_inf.wy = (((short)Rx_buf[16]<<8)|Rx_buf[15])/32768.0f*2000;
		jy61_inf.wz = (((short)Rx_buf[20]<<8)|Rx_buf[19])/32768.0f*2000;
		jy61_inf.T = (((short)Rx_buf[9]<<8)|Rx_buf[8])/340.0f+36.53f;
		if(jy61_inf.wx>2000)jy61_inf.wx-=4000;
		if(jy61_inf.wy>2000)jy61_inf.wy-=4000;
		if(jy61_inf.wz>2000)jy61_inf.wz-=4000;

		jy61_inf.ROLL = (((short)Rx_buf[25]<<8)|Rx_buf[24])/32768.0f*180;
		jy61_inf.PITCH = (((short)Rx_buf[27]<<8)|Rx_buf[26])/32768.0f*180;
		jy61_inf.YAW = (((short)Rx_buf[29]<<8)|Rx_buf[28])/32768.0f*180;
		jy61_inf.T = (((short)Rx_buf[31]<<8)|Rx_buf[30])/340.0f+36.53f;
	
//		if(jy61_inf.ROLL>180)jy61_inf.ROLL -= 360;
//		if(jy61_inf.PITCH>180)jy61_inf.PITCH -= 360;
//		if(jy61_inf.YAW>180)jy61_inf.YAW -= 360;


			HAL_UART_Receive_DMA(huart,uart_rxbuff,jy61_data_length);
		}
}









void jy61_USART4_Init(void)
{
	__HAL_UART_ENABLE_IT(&huart4,UART_IT_IDLE);
	HAL_UART_Receive_DMA(&huart4,jy61_rxbuff,jy61_data_length);
	while(jy61_inf.T==0)printf("jy61 failed\n");
}








