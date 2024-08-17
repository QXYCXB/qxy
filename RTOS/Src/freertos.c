/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "all.h"
#include "usart.h"
extern int ABS_angle;
extern bool MODE;
extern int initial_angle;
float Pos_1[2]={1661.61,1700};//位置一   取红球
float Pos_2[2]={1800.61,1700};//位置二   发射红球
float Pos_3[2]={-1841.61,1621.61};//位置二  取蓝1球


u8 key_val;
int speed;


/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for POS */
osThreadId_t POSHandle;
const osThreadAttr_t POS_attributes = {
  .name = "POS",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for KEY */
osThreadId_t KEYHandle;
const osThreadAttr_t KEY_attributes = {
  .name = "KEY",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for OLED */
osThreadId_t OLEDHandle;
const osThreadAttr_t OLED_attributes = {
  .name = "OLED",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for Clamp */
osThreadId_t ClampHandle;
const osThreadAttr_t Clamp_attributes = {
  .name = "Clamp",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void Pos_move(void *argument);
void KEY_CHeck(void *argument);
void OLED_show(void *argument);
void ClampTheBall(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

	
	
	
	
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of POS */
  POSHandle = osThreadNew(Pos_move, NULL, &POS_attributes);

  /* creation of KEY */
  KEYHandle = osThreadNew(KEY_CHeck, NULL, &KEY_attributes);

  /* creation of OLED */
  OLEDHandle = osThreadNew(OLED_show, NULL, &OLED_attributes);

  /* creation of Clamp */
  ClampHandle = osThreadNew(ClampTheBall, NULL, &Clamp_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
	vTaskSuspend(POSHandle);//挂起该任务
	vTaskSuspend(ClampHandle);//挂起该任务

	
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_Pos_move */
/**
  * @brief  Function implementing the POS thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_Pos_move */
void Pos_move(void *argument)
{
  /* USER CODE BEGIN Pos_move */
  /* Infinite loop */
  for(;;)
  {
		LED1=0;
//		Goal_Angel = ANGEL_30;
//		launch_Exp1 = launch_Speed1;
//		launch_Exp2 = launch_Speed2;
		while(ABS(action_inf.angle_z-ANGEL_30)>1)printf("The angle in progress\r\n");
		while(ABS(launch_inf[0].speed)<launch_Speed1)printf("The launch_Exp1 is accelerating\r\n");
		while(ABS(launch_inf[4].speed)<launch_Speed2)printf("The launch_Exp2 is accelerating\r\n");
		HAL_Delay(500);
		FaShe = 1;
		HAL_Delay(500);HAL_Delay(500);
		launch_Exp1 = 0;
		launch_Exp2 = 0;
		FaShe = 0;
		Goal_Angel = ANGEL_90;
		Goal_pos_X = Pos_1[0];
		Goal_pos_Y = Pos_1[1];
;		while(ABS(action_inf.angle_z-ANGEL_90)>2)printf("The angle in progress. \r\n");
		while(ABS(action_inf.pos_x-Pos_1[0])>50)printf("The pos_x in progress. pos_x=%.2f\r\n",action_inf.pos_x);
		while(ABS(action_inf.pos_y-Pos_1[1])>50)printf("The pos_y in progress. pos_y=%.2f\r\n",action_inf.pos_y);
		JZ = 1;
		Goal_JZ = initial_angle;
		HAL_Delay(500);HAL_Delay(500);
		JZ = 0;
		HAL_Delay(500);HAL_Delay(500);
		Goal_JZ = initial_angle-500000;
		HAL_Delay(500);HAL_Delay(500);
		Turning = 1;
		HAL_Delay(500);HAL_Delay(500);HAL_Delay(500);
		JZ = 1;
		HAL_Delay(500);
		Turning = 0;
		JZ = 0;
		Goal_pos_X = Pos_2[0];
		launch_Exp1 = launch_Speed1;
		launch_Exp2 = launch_Speed2;
		while(ABS(action_inf.pos_x-Pos_2[0])>100)printf("The pos_x in progress. pos_x=%.2f\r\t",action_inf.pos_x);
		while(ABS(launch_inf[0].speed)<launch_Speed1)printf("The launch_Exp1 is accelerating\r\n");
		while(ABS(launch_inf[4].speed)<launch_Speed2)printf("The launch_Exp2 is accelerating\r\n");
		HAL_Delay(500);
		FaShe = 1;
		HAL_Delay(500);HAL_Delay(500);
		
		
		launch_Exp1 = 0;
		launch_Exp2 = 0;
		FaShe = 0;
		
		Goal_pos_Y = -300;
		while(ABS(action_inf.pos_y+300)>500)printf("The pos_y in progress. pos_y=%.2f\r\t",action_inf.pos_y+300);
		
		Goal_pos_X = Pos_3[0];
		while(ABS(action_inf.pos_x-Pos_3[0])>100)printf("The pos_x in progress. pos_x=%.2f\r\t",action_inf.pos_x);
		
		Goal_pos_Y = Pos_3[1];
		while(ABS(action_inf.pos_y-Pos_3[1])>100)printf("The pos_y in progress. pos_y=%.2f\r\t",action_inf.pos_y-Pos_3[1]);
		
		JZ = 1;
		Goal_JZ = initial_angle;
		HAL_Delay(500);HAL_Delay(500);
		JZ = 0;
		HAL_Delay(500);HAL_Delay(500);
		Goal_JZ = initial_angle-500000;
		HAL_Delay(500);HAL_Delay(500);
		Turning = 1;
		HAL_Delay(500);HAL_Delay(500);HAL_Delay(500);
		JZ = 1;
		HAL_Delay(500);
		Turning = 0;
		JZ = 0;
		
		Goal_Angel = 0;
		Goal_pos_X = 0;
		Goal_pos_Y = 0;
		
		
		
		osDelay(1);
		vTaskSuspend(POSHandle);
		
		
//		LED1=!LED1;

		
		
  }
  /* USER CODE END Pos_move */
}

/* USER CODE BEGIN Header_KEY_CHeck */
/**
* @brief Function implementing the KEY thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_KEY_CHeck */
void KEY_CHeck(void *argument)
{
  /* USER CODE BEGIN KEY_CHeck */
  /* Infinite loop */
  for(;;)
  {
		if(MODE==0)
		{
			key_val=Sbus_key(0);
			if(key_val==1)vTaskResume(POSHandle);
			else if(key_val==2)vTaskResume(ClampHandle);
			else{}
//			speed_sen/d_data(0,motor_inf[0].speed,Motor[0].Exp);
		}
    osDelay(1);
  }
  /* USER CODE END KEY_CHeck */
}

/* USER CODE BEGIN Header_OLED_show */
/**
* @brief Function implementing the OLED thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_OLED_show */
void OLED_show(void *argument)
{
  /* USER CODE BEGIN OLED_show */
  /* Infinite loop */
	
  for(;;)
  {
		
		sprintf(str,"JG:%d %d ",JG_pos_x,JG_pos_y);
		OLED_ShowString(0,0, (uint8_t*)str,16);
		sprintf(str,"%.2f %.2f ",action_inf.pos_x,action_inf.pos_y);	
		OLED_ShowString(0,2, (uint8_t*)str,16);
		sprintf(str,"%.2f ",action_inf.angle_z);	
		OLED_ShowString(0,4, (uint8_t*)str,16);
		sprintf(str,"%06d",SpeedExp);	
		OLED_ShowString(0,6, (uint8_t*)str,16);
		
    printf("%.2f\r\t%.2f\r\t%.2f\r\t%d\r\n",action_inf.pos_x,action_inf.pos_y,action_inf.angle_z,SBusRemote.Channel[1]);
//		printf("%d\r\t%d\r\t%d\r\t%d\r\t%d\r\n",SBusRemote.Channel[5],SBusRemote.Channel[0],SBusRemote.Channel[1],SBusRemote.Channel[2],SBusRemote.Channel[3]);
		
//		printf("%d\r\t%d\r\t%d\r\t%d\r\t",launch_inf[0].speed,launch_inf[1].speed,launch_inf[2].speed,launch_inf[3].speed);
//		printf("%d\r\t%d\r\t%d\r\t%d\r\n",launch_inf[4].speed,launch_inf[5].speed,launch_inf[6].speed,launch_inf[7].speed);
		
//		printf("%d\r\t%d\r\t%d\r\t%d\r\n",motor_inf[3].angle,ABS_angle,(int)JZ_RealAngle.Exp,(int)(JZ_RealAngle.Exp-ABS_angle));
//		printf("%d\r\t%d\r\t%d\r\t",(int)Motor[0].Exp,(int)Motor[1].Exp,(int)Motor[2].Exp);
//		printf("%d\r\t%d\r\t%d\r\t",motor_cur[0].cur,motor_cur[1].cur,motor_cur[2].cur);
		
		LED0=!LED0;

		osDelay(50);

  }
  /* USER CODE END OLED_show */
}

/* USER CODE BEGIN Header_ClampTheBall */
/**
* @brief Function implementing the Clamp thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_ClampTheBall */
void ClampTheBall(void *argument)
{
  /* USER CODE BEGIN ClampTheBall */
  /* Infinite loop */
  for(;;)
  { 
		Goal_Angel = ANGEL_30;
		launch_Exp1 = launch_Speed1;
		launch_Exp2 = launch_Speed2;
		while(ABS(action_inf.angle_z-ANGEL_30)>1.0f)printf("The angle in progress. angle=%.2f\r\n",action_inf.angle_z);
		while(ABS(launch_inf[0].speed)<launch_Speed1)printf("The launch_Exp1 is accelerating. \r\n");
		while(ABS(launch_inf[4].speed)<launch_Speed2)printf("The launch_Exp2 is accelerating. \r\n");

		vTaskSuspend(ClampHandle);
  }
  /* USER CODE END ClampTheBall */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

