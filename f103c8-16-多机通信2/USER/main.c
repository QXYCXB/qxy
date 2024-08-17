#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "key.h"
#include "oled.h"
#define MY_time 200

UART_Str Str1;
char string[20]={0};
bool to_id_set=0;
bool my_id_set=0;
bool data_in=0;
bool Tx_flag=0;
bool MODE=0;
char key_val,value1=0,value2=0,value3=0,last;
u8 CS=0;
char DATA[20]={0};
char key_val;
u8 m_count=0;
int main()
{		
	delay_init();
	OLED_Init();
	KEY_Init();
	uart_init(9600);
	LED=1;
	OLED_Clear();
	while(1)
	{
		key_val=Key_Scan();
//		while(Key_Scan()!=0);
		while(Key_Scan()!='e');
		switch(key_val)
		{
			case 'A':my_id_set=1;break;
			case 'B':to_id_set=1;break;
			case 'C':data_in=1;break;
			case 'D':Tx_flag=1;break;
			case '*':MODE=!MODE;break;
			default:;
		}
			while(my_id_set)
			{
				OLED_ShowString(0,0, (u8*)"         ",16);
				delay_ms(MY_time);
				sprintf(string,"my_id:%02x",Str1.my_id);
				OLED_ShowString(0,0, (u8*)string,16);
				delay_ms(MY_time);
				key_val=Key_Scan();	
				while(Key_Scan()!='e');
//				while(Key_Scan()!=0);
				if(key_val=='#')my_id_set=0;
				if(key_val!='#' && key_val!='e')Str1.my_id=key_val-'0';
			}
			
			while(to_id_set)
			{
				OLED_ShowString(0,2, (u8*)"         ",16);
				delay_ms(MY_time);
				sprintf(string,"to_id:%02x",Str1.to_id);
				OLED_ShowString(0,2, (u8*)string,16);
				delay_ms(MY_time);
				key_val=Key_Scan();
				while(Key_Scan()!='e');
				if(key_val!=0 && key_val!='#' && key_val!='e')Str1.to_id=key_val-0x30;
				if(key_val=='#')to_id_set=0;
			}
			
			while(data_in)
			{
				OLED_ShowString(0,4, (u8*)"              ",16);
				delay_ms(MY_time);
				OLED_ShowString(0,4, (u8*)"T:",16);
				sprintf(string,"%02x",Str1.TX_data[0]);
				OLED_ShowString(16,4, (u8*)string,16);
				sprintf(string,"%02x",Str1.TX_data[1]);
				OLED_ShowString(34,4, (u8*)string,16);
				sprintf(string,"%02x",Str1.TX_data[2]);
				OLED_ShowString(52,4, (u8*)string,16);
				sprintf(string,"%02x",Str1.TX_data[3]);
				OLED_ShowString(70,4, (u8*)string,16);
				delay_ms(MY_time);
				key_val=Key_Scan();
				while(Key_Scan()!='e');
				if(key_val!=0 && key_val!='#' && key_val!='e')Str1.TX_data[m_count++]=key_val-0x30;
				if(key_val=='#'){data_in=0;m_count=0;}
			}
			
			if(Tx_flag)
			{
				OLED_Clear();
				JMP1:;
				key_val=Key_Scan();
				
				while(Key_Scan()!='e');
				OLED_ShowString(0,4, (u8*)"          ",16);
				delay_ms(MY_time);
				OLED_ShowString(0,4, (u8*)"transmit:",16);
				delay_ms(MY_time);
				if(key_val!='#')goto JMP1;
				USART_SendData(USART1,0xff);//Ö¡Í·
				delay_ms(1);
				USART_SendData(USART1,Str1.my_id);//
				delay_ms(1);
				USART_SendData(USART1,Str1.to_id);//
				delay_ms(1);
				MY_Send_Data(USART1,(char*)Str1.TX_data,4);//Êý¾Ý
				delay_ms(1);
				USART_SendData(USART1,0xEE);//Ö¡wei
				Tx_flag=0;
				OLED_Clear();
			}
				sprintf(string,"my_id:%02x",Str1.my_id);
				OLED_ShowString(0,0, (u8*)string,16);
				sprintf(string,"to_id:%02x",Str1.to_id);
				OLED_ShowString(0,2, (u8*)string,16);
				OLED_ShowString(0,4, (u8*)"T:",16);
				sprintf(string,"%02x",Str1.TX_data[0]);
				OLED_ShowString(16,4, (u8*)string,16);
				sprintf(string,"%02x",Str1.TX_data[1]);
				OLED_ShowString(34,4, (u8*)string,16);
				sprintf(string,"%02x",Str1.TX_data[2]);
				OLED_ShowString(52,4, (u8*)string,16);
				sprintf(string,"%02x",Str1.TX_data[3]);
				OLED_ShowString(70,4, (u8*)string,16);
			
				if(MODE)
				{
					OLED_ShowString(0,6, (u8*)"R:",16);
					sprintf(string,"%02x",Str1.RX_data[4]);
					OLED_ShowString(16,6, (u8*)string,16);
					sprintf(string,"%02x",Str1.RX_data[5]);
					OLED_ShowString(34,6, (u8*)string,16);
					sprintf(string,"%02x",Str1.RX_data[6]);
					OLED_ShowString(52,6, (u8*)string,16);
					sprintf(string,"%02x",Str1.RX_data[7]);
					OLED_ShowString(70,6, (u8*)string,16);
					
				}
				else OLED_ShowString(0,6, (u8*)"              ",16);
			
	}
	
}


