#include "motor.h"
#include "tim.h"

void Get_Encoder_Data(int* Motor1,int* Motor2,int* Motor3,int* Motor4)
{
	
	*Motor1=TIM4->CNT - 0x7fff;
	TIM4->CNT = 0x7fff;
	
	*Motor2=TIM3->CNT - 0x7fff;
	*Motor2=-*Motor2;
	TIM3->CNT = 0x7fff;
	
	*Motor3=TIM2->CNT - 0x7fff;
	*Motor3=-*Motor3;
	TIM2->CNT = 0x7fff;
	
	*Motor4=TIM5->CNT - 0x7fff;
	*Motor4=-*Motor4;
	TIM5->CNT = 0x7fff;
}





void send_speed_date(u8 id,int speed)
{
	
	if(speed>0)
	{
		switch(id)
		{
			case 3:
				GPIOG->BSRR = GPIO_PIN_0;
				GPIOG->BSRR = (uint32_t)GPIO_PIN_1 << 16U;
			break;
			
			case 4:
				GPIOG->BSRR = GPIO_PIN_3;
				GPIOG->BSRR = (uint32_t)GPIO_PIN_2 << 16U;
			break;
			
			case 1:
				GPIOG->BSRR = GPIO_PIN_4;
				GPIOG->BSRR = (uint32_t)GPIO_PIN_5 << 16U;
			break;
			
			case 2:
				GPIOG->BSRR = GPIO_PIN_7;
				GPIOG->BSRR = (uint32_t)GPIO_PIN_6 << 16U;
			break;
		}	
	}
	else if(speed<0)
	{
		switch(id)
		{
			case 3:
				GPIOG->BSRR = GPIO_PIN_1;
				GPIOG->BSRR = (uint32_t)GPIO_PIN_0 << 16U;
			break;
			
			case 4:
				GPIOG->BSRR = GPIO_PIN_2;
				GPIOG->BSRR = (uint32_t)GPIO_PIN_3 << 16U;
			break;
			
			case 1:
				GPIOG->BSRR = GPIO_PIN_5;
				GPIOG->BSRR = (uint32_t)GPIO_PIN_4 << 16U;
			break;
			
			case 2:
				GPIOG->BSRR = GPIO_PIN_6;
				GPIOG->BSRR = (uint32_t)GPIO_PIN_7 << 16U;
			break;
		}	
		speed=-speed;
	}
	else if(speed==0)
	{
		switch(id)
		{
			case 3:
				GPIOG->BSRR = (uint32_t)GPIO_PIN_0 << 16U;
				GPIOG->BSRR = (uint32_t)GPIO_PIN_1 << 16U;
			break;
			
			case 4:
				GPIOG->BSRR = (uint32_t)GPIO_PIN_2 << 16U;
				GPIOG->BSRR = (uint32_t)GPIO_PIN_3 << 16U;
			break;
			
			case 1:
				GPIOG->BSRR = (uint32_t)GPIO_PIN_4 << 16U;
				GPIOG->BSRR = (uint32_t)GPIO_PIN_5 << 16U;
			break;
			
			case 2:
				GPIOG->BSRR = (uint32_t)GPIO_PIN_6 << 16U;
				GPIOG->BSRR = (uint32_t)GPIO_PIN_7 << 16U;
			break;
		}
	}
	switch(id)
		{
			case 1:
			TIM1->CCR1 = speed;
			break;
			
			case 2:
			TIM1->CCR2 = speed;
			break;
			
			case 3:
			TIM1->CCR3 = speed;
			break;
			
			case 4:
			TIM1->CCR4 = speed;
			break;
		}
}




void Motor_Init(void)
{
	
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);/* 定时器通道1输出PWM */
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);/* 定时器通道2输出PWM */
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);/* 定时器通道3输出PWM */
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);/* 定时器通道3输出PWM */
	
	HAL_TIM_Encoder_Start(&htim2,TIM_CHANNEL_ALL);//开启编码器模式
	HAL_TIM_Encoder_Start(&htim3,TIM_CHANNEL_ALL);//开启编码器模式
	HAL_TIM_Encoder_Start(&htim4,TIM_CHANNEL_ALL);//开启编码器模式
	HAL_TIM_Encoder_Start(&htim5,TIM_CHANNEL_ALL);//开启编码器模式
	__HAL_TIM_SetCounter(&htim2,0x7fff);
	__HAL_TIM_SetCounter(&htim3,0x7fff);
	__HAL_TIM_SetCounter(&htim4,0x7fff);
	__HAL_TIM_SetCounter(&htim5,0x7fff);
}



