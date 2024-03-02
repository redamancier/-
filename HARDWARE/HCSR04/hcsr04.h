#ifndef __HCSR04_H
#define __HCSR04_H
#include <stm32f4xx.h>
#define HCSR04_TRIG_1_Port		GPIOD
#define HCSR04_TRIG_1_Pin		GPIO_Pin_0
#define HCSR04_TRIG_1_CLK		RCC_AHB1Periph_GPIOD

#define HCSR04_TRIG_2_Port		GPIOD
#define HCSR04_TRIG_2_Pin		GPIO_Pin_1
#define HCSR04_TRIG_2_CLK		RCC_AHB1Periph_GPIOD

#define HCSR04_TRIG_3_Port		GPIOD
#define HCSR04_TRIG_3_Pin		GPIO_Pin_2
#define HCSR04_TRIG_3_CLK		RCC_AHB1Periph_GPIOD

#define HCSR04_TRIG_4_Port		GPIOD
#define HCSR04_TRIG_4_Pin		GPIO_Pin_3
#define HCSR04_TRIG_4_CLK		RCC_AHB1Periph_GPIOD
//
#define HCSR04_TRIG_1_Set		GPIO_SetBits(HCSR04_TRIG_1_Port,HCSR04_TRIG_1_Pin)
#define HCSR04_TRIG_1_Reset		GPIO_ResetBits(HCSR04_TRIG_1_Port,HCSR04_TRIG_1_Pin)

#define HCSR04_TRIG_2_Set		GPIO_SetBits(HCSR04_TRIG_2_Port,HCSR04_TRIG_2_Pin)
#define HCSR04_TRIG_2_Reset		GPIO_ResetBits(HCSR04_TRIG_2_Port,HCSR04_TRIG_2_Pin)

#define HCSR04_TRIG_3_Set		GPIO_SetBits(HCSR04_TRIG_3_Port,HCSR04_TRIG_3_Pin)
#define HCSR04_TRIG_3_Reset		GPIO_ResetBits(HCSR04_TRIG_3_Port,HCSR04_TRIG_3_Pin)

#define HCSR04_TRIG_4_Set		GPIO_SetBits(HCSR04_TRIG_4_Port,HCSR04_TRIG_4_Pin)
#define HCSR04_TRIG_4_Reset		GPIO_ResetBits(HCSR04_TRIG_4_Port,HCSR04_TRIG_4_Pin)

#define HCSR04_Read(channel_1,channel_2,channel_3,channel_4) HCSR04_TIM_StopAndRead(channel_1 ,channel_2,channel_3,channel_4)

typedef struct
{
	float cur_data;
	float last_data;
}_hcsr04_obj;

typedef struct
{
	_hcsr04_obj left_1;
	_hcsr04_obj left_2;
	_hcsr04_obj right_1;
	_hcsr04_obj right_2;
}_hcsr04_data_t;

void HCSR04_Init(void);
void HCSR04_Start(void);
void HCSR04_UpdateData(void);

extern _hcsr04_data_t HCSR04_Data;

#endif
