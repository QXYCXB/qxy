#include "timeq.h"
#include "usart.h"	  


//////////////////////////////////////////////////////////////////////////////////
//�������ƣ�TIM1_IRQ_Init(u16 arr, u16 psc);
//�������ã���ʱ���ж�  
//��ڲ�����
//�� �� ֵ��
//˵    ����
//ʱ    ��:	  
//////////////////////////////////////////////////////////////////////////////////
void TIM1_IRQ_Init(u16 arr, u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;//
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;//����ģʽ�����ϼ�����
	TIM_TimeBaseInitStruct.TIM_Period=arr-1;//�Զ�װ��ֵ
	TIM_TimeBaseInitStruct.TIM_Prescaler=psc-1;//Ԥ��Ƶϵ��
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStruct);
	

	
	TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);//ʹ�ܶ�ʱ���ĸ����ж� //�ڶ����������ж����ͣ������жϣ�
	
	
	NVIC_InitStruct.NVIC_IRQChannel=TIM1_UP_IRQn;//�ж�ͨ������ʱ��3��
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;//IRQͨ����ʹ��
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;//��ռ���ȼ���0����
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=3;//�����ȼ���3����
	NVIC_Init(&NVIC_InitStruct);
	
	TIM_Cmd(TIM1,ENABLE);//ʹ�ܶ�ʱ��
	
	
}

void TIM1_UP_IRQHandler(void)
{
	
	if(TIM_GetITStatus(TIM1,TIM_IT_Update)!=RESET)
	{
		TIM_ClearITPendingBit(TIM1,TIM_IT_Update);//�����ʱ��3�ĸ����жϱ�־

		

		
		
		
		


	
		
	}


}
