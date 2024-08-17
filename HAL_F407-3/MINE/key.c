#include "key.h"
bool start_flag=0;
bool MODE=0;
bool circle=0;
uint8_t KEY_Scan(void)
{
	uint8_t valu=0;
	if(HAL_GPIO_ReadPin(K0_GPIO_Port, K0_Pin)==0)
	{
		HAL_Delay(10);
		if(HAL_GPIO_ReadPin(K0_GPIO_Port, K0_Pin)==0)valu=1;
	}
	
	if(HAL_GPIO_ReadPin(K1_GPIO_Port, K1_Pin)==0)
	{
		HAL_Delay(10);
		if(HAL_GPIO_ReadPin(K1_GPIO_Port, K1_Pin)==0)valu=2;
	}
	
	if(HAL_GPIO_ReadPin(K2_GPIO_Port, K2_Pin)==0)
	{
		HAL_Delay(10);
		if(HAL_GPIO_ReadPin(K2_GPIO_Port, K2_Pin)==0)valu=3;
	}
	
	if(HAL_GPIO_ReadPin(K3_GPIO_Port, K3_Pin)==0)
	{
		HAL_Delay(10);
		if(HAL_GPIO_ReadPin(K3_GPIO_Port, K3_Pin)==0)valu=4;
	}
	
	if(HAL_GPIO_ReadPin(K4_GPIO_Port, K4_Pin)==0)
	{
		HAL_Delay(10);
		if(HAL_GPIO_ReadPin(K4_GPIO_Port, K4_Pin)==0)valu=5;
	}
	return valu;
}

void KEY_Check(KEY_Str* KEY)
{
	static __IO uint32_t utick_point=0;
	KEY->key_val=KEY_Scan();
	
	KEY->key_down= KEY->key_val & (KEY->key_val^KEY->key_old);
	KEY->key_up = ~KEY->key_val & (KEY->key_val^KEY->key_old);
	KEY->key_old=KEY->key_val;
	
	if(KEY->key_down!=0)utick_point=uwTick;
	if(KEY->key_up!=0)KEY->key_time=uwTick-utick_point;
}

KEY_Str KEY;
void KEY4_Proc(void)
{
	KEY_Check(&KEY);
	if(KEY.key_down==K4_press)
	{
		KEY_Check(&KEY);
		while(!KEY.key_up)KEY_Check(&KEY);
		LED1=!LED1;
		MODE=!MODE;
	}
	
	
	else {}
}

void KEY3_Proc(void)
{
	KEY_Check(&KEY);
	if(KEY.key_down==K3_press)
	{
		KEY_Check(&KEY);
		while(!KEY.key_up)KEY_Check(&KEY);
		LED0=1;
		LED2=0;
		HAL_Delay(1000);
		LED2=1;
		start_flag=1;
//		printf("%d\r\n",start_flag);
	}
	else {}
}


void KEY2_Proc(void)
{
	KEY_Check(&KEY);
	if(KEY.key_down==K2_press)
	{
		KEY_Check(&KEY);
		while(!KEY.key_up)KEY_Check(&KEY);
		LED0=!LED0;
		circle=!circle;
//		printf("%d\r\n",start_flag);
	}
	else {}
}

