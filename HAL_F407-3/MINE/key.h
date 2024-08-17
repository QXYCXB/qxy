#ifndef __KEY_H__
#define __KEY_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

typedef struct{
	uint8_t key_down;
	uint8_t key_up;
	uint8_t key_old;
	uint8_t key_val;
	__IO uint32_t key_time;
}KEY_Str;


void KEY4_Proc(void);
void KEY3_Proc(void);
void KEY2_Proc(void);
#define K0_press 1
#define K1_press 2
#define K2_press 3
#define K3_press 4
#define K4_press 5
extern bool start_flag;
extern bool MODE;
extern bool circle;
#ifdef __cplusplus
}
#endif

#endif


