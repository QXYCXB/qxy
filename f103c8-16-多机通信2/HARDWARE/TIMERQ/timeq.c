#include "timeq.h"
#include "usart.h"	  


//////////////////////////////////////////////////////////////////////////////////
//函数名称：TIM1_IRQ_Init(u16 arr, u16 psc);
//函数作用：定时器中断  
//入口参数：
//返 回 值：
//说    明：
//时    间:	  
//////////////////////////////////////////////////////////////////////////////////
void TIM1_IRQ_Init(u16 arr, u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;//
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;//计数模式（向上计数）
	TIM_TimeBaseInitStruct.TIM_Period=arr-1;//自动装载值
	TIM_TimeBaseInitStruct.TIM_Prescaler=psc-1;//预分频系数
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStruct);
	

	
	TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);//使能定时器的更新中断 //第二个参数：中断类型（更新中断）
	
	
	NVIC_InitStruct.NVIC_IRQChannel=TIM1_UP_IRQn;//中断通道（定时器3）
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;//IRQ通道被使能
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;//抢占优先级（0级）
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=3;//子优先级（3级）
	NVIC_Init(&NVIC_InitStruct);
	
	TIM_Cmd(TIM1,ENABLE);//使能定时器
	
	
}

void TIM1_UP_IRQHandler(void)
{
	
	if(TIM_GetITStatus(TIM1,TIM_IT_Update)!=RESET)
	{
		TIM_ClearITPendingBit(TIM1,TIM_IT_Update);//清除定时器3的更新中断标志

		

		
		
		
		


	
		
	}


}
