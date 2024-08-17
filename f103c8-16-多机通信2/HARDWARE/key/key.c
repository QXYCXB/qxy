#include "key.h"
void KEY_Init(void)//������ʼ��
{
	
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB| RCC_APB2Periph_AFIO, ENABLE);	 //ʹ��A�˿�ʱ��
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;	 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�50MHz
 	GPIO_Init(GPIOB, &GPIO_InitStructure);	  //��ʼ��GPIOA8-11	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��B�˿�ʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		 //��������/����ɨ��
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�50MHz
 	GPIO_Init(GPIOA, &GPIO_InitStructure);	  //��ʼ��GPIOB12-15

}

/*********************************************************************
*����˵���� ����ɨ��
*����ֵ  :  ����ֵ
*����    ��  void
**********************************************************************/
char Key_Scan(void)
{
	char valu=0;
	GPIO_Write(GPIOB,((GPIOB->ODR & 0xff87 )| 0x0078));//��PA8-11����ߵ�ƽ0000 0000 0111 1000
    
	if((GPIOA->IDR & 0x000f)==0x0000)//��PB12-PB15ȫΪ0����û�а�������
	valu= 'e';
	else
	{
		delay_ms(5);//��ʱ����
		
		if((GPIOA->IDR & 0x000f)==0x0000)//��PB12-PB15ȫΪ0����ո��Ƕ�������
		valu= 'e';
	
	}
	GPIO_Write(GPIOB,(GPIOB->ODR & 0xff87 )| 0x0008);//��PA8-11���0001����������
	switch(GPIOA->IDR & 0x000f)
	{
		case 0x0001 : valu= 'A';break;//
		case 0x0002 : valu= '3';break;//
		case 0x0004 : valu= '2';break;//
		case 0x0008 : valu= '1';break;//
	}
	
	GPIO_Write(GPIOB,(GPIOB->ODR & 0xff87 )| 0x0010);//��PA8-11���0010����������
	switch(GPIOA->IDR & 0x000f)
	{
		case 0x0001 : valu= 'B';break;//
		case 0x0002 : valu= '6';break;//
		case 0x0004 : valu= '5';break;//
		case 0x0008 : valu= '4';break;//
	}
	
	GPIO_Write(GPIOB,(GPIOB->ODR & 0xff87 )| 0x0020);//��PA8-11���0100�����ڶ���
	switch(GPIOA->IDR & 0x000f)
	{
		case 0x0001 : valu= 'C';break;//
		case 0x0002 : valu= '9';break;//
		case 0x0004 : valu= '8';break;//
		case 0x0008 : valu= '7';break;//
	}
	GPIO_Write(GPIOB,(GPIOB->ODR & 0xff87 )| 0x0040);//��PA8-11���1000������һ��
	switch(GPIOA->IDR & 0x000f)
	{
		case 0x0001 : valu= 'D';break;//
		case 0x0002 : valu= '#';break;//
		case 0x0004 : valu= '0';break;//
		case 0x0008 : valu= '*';break;//
	}
	

	return valu;
}



	
	
	
	
	
	
