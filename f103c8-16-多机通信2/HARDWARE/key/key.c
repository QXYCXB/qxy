#include "key.h"
void KEY_Init(void)//按键初始化
{
	
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB| RCC_APB2Periph_AFIO, ENABLE);	 //使能A端口时钟
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;	 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
 	GPIO_Init(GPIOB, &GPIO_InitStructure);	  //初始化GPIOA8-11	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能B端口时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		 //下拉输入/逐行扫描
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
 	GPIO_Init(GPIOA, &GPIO_InitStructure);	  //初始化GPIOB12-15

}

/*********************************************************************
*函数说明： 按键扫描
*返回值  :  按键值
*参数    ：  void
**********************************************************************/
char Key_Scan(void)
{
	char valu=0;
	GPIO_Write(GPIOB,((GPIOB->ODR & 0xff87 )| 0x0078));//让PA8-11输出高电平0000 0000 0111 1000
    
	if((GPIOA->IDR & 0x000f)==0x0000)//若PB12-PB15全为0，则没有按键按下
	valu= 'e';
	else
	{
		delay_ms(5);//延时消抖
		
		if((GPIOA->IDR & 0x000f)==0x0000)//若PB12-PB15全为0，则刚刚是抖动产生
		valu= 'e';
	
	}
	GPIO_Write(GPIOB,(GPIOB->ODR & 0xff87 )| 0x0008);//让PA8-11输出0001，检测第四行
	switch(GPIOA->IDR & 0x000f)
	{
		case 0x0001 : valu= 'A';break;//
		case 0x0002 : valu= '3';break;//
		case 0x0004 : valu= '2';break;//
		case 0x0008 : valu= '1';break;//
	}
	
	GPIO_Write(GPIOB,(GPIOB->ODR & 0xff87 )| 0x0010);//让PA8-11输出0010，检测第三行
	switch(GPIOA->IDR & 0x000f)
	{
		case 0x0001 : valu= 'B';break;//
		case 0x0002 : valu= '6';break;//
		case 0x0004 : valu= '5';break;//
		case 0x0008 : valu= '4';break;//
	}
	
	GPIO_Write(GPIOB,(GPIOB->ODR & 0xff87 )| 0x0020);//让PA8-11输出0100，检测第二行
	switch(GPIOA->IDR & 0x000f)
	{
		case 0x0001 : valu= 'C';break;//
		case 0x0002 : valu= '9';break;//
		case 0x0004 : valu= '8';break;//
		case 0x0008 : valu= '7';break;//
	}
	GPIO_Write(GPIOB,(GPIOB->ODR & 0xff87 )| 0x0040);//让PA8-11输出1000，检测第一行
	switch(GPIOA->IDR & 0x000f)
	{
		case 0x0001 : valu= 'D';break;//
		case 0x0002 : valu= '#';break;//
		case 0x0004 : valu= '0';break;//
		case 0x0008 : valu= '*';break;//
	}
	

	return valu;
}



	
	
	
	
	
	
