



#ifndef _LAUNCH_H_
#define _LAUNCH_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

#define BYTE0(data)  (*((char *)(&data) + 0))
#define BYTE1(data)  (*((char *)(&data) + 1))
#define BYTE2(data)  (*((char *)(&data) + 2))
#define BYTE3(data)  (*((char *)(&data) + 3))
	
//������ز����ṹ��
typedef struct{
	uint16_t angle;//ת�ӽǶ�  ��Χ0~8191  ��Ӧ0~360��
	int16_t speed;//ת���ٶ�
	int16_t current;//ʵ�ʵ���
	uint8_t temperature;//����¶�  ��λ���϶�
}launch_inf_Str;

//������͵����ṹ��
typedef struct{
	int16_t cur;
}launch_cur_Str;


extern launch_inf_Str launch_inf[8];
extern launch_cur_Str launch_cur[8];
void Get_launch_inf(CAN_RxHeaderTypeDef* RxMessage,u8* data);
void Send_cur_launch(void);

#ifdef __cplusplus
}
#endif
#endif


