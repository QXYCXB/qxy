#ifndef __JG_H__
#define __JG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"



void Get_JG_inf(UART_HandleTypeDef *huart,u32* pos,u8* uart_rxbuff);

void JG_Command_SET(UART_HandleTypeDef *huart);
void UART_Send_Data(UART_HandleTypeDef *huart, char* point, u8 Length);



extern char SingleMea[4];
extern char Switch_Off[4];
extern char Cont_Mea[4];
extern char Set_addr[5];
extern char Range[5];
extern char Set_freq[5];
extern char Set_accuracy[5];
extern char Mea_On[5];
extern char Ctrl_On[5];
extern char Ctrl_Off[5];
extern char Cont_Mea_time[5];
extern char Ctrl_Off[5];









#ifdef __cplusplus
}
#endif
#endif
