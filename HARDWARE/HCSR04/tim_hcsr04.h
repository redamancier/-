#ifndef __TIM_HCSR04_H
#define __TIM_HCSR04_H
#include <stm32f4xx.h>
#define TIM_HCSR04 		TIM3
#define TIM_HCSR04_AF	GPIO_AF_TIM3
#define TIM_HCSR04_CLK	RCC_APB1Periph_TIM3
#define TIM_HCSR04_ISR	TIM3_IRQHandler
#define TIM_HCSR04_IRQn	TIM3_IRQn

#define HCSR04_1 		TIM_Channel_1
#define HCSR04_2 		TIM_Channel_2
#define HCSR04_3		TIM_Channel_3
#define HCSR04_4		TIM_Channel_4

#define HCSR04_1_GPIO_Port	GPIOB
#define HCSR04_1_GPIO_Pin	GPIO_Pin_4
#define HCSR04_1_CLK		RCC_AHB1Periph_GPIOB
#define HCSR04_1_Pinsource	GPIO_PinSource4

#define HCSR04_2_GPIO_Port	GPIOB
#define HCSR04_2_GPIO_Pin	GPIO_Pin_5
#define HCSR04_2_CLK		RCC_AHB1Periph_GPIOB
#define HCSR04_2_Pinsource	GPIO_PinSource5

#define HCSR04_3_GPIO_Port	GPIOB
#define HCSR04_3_GPIO_Pin	GPIO_Pin_0
#define HCSR04_3_CLK		RCC_AHB1Periph_GPIOB
#define HCSR04_3_Pinsource	GPIO_PinSource0

#define HCSR04_4_GPIO_Port	GPIOB
#define HCSR04_4_GPIO_Pin	GPIO_Pin_1
#define HCSR04_4_CLK		RCC_AHB1Periph_GPIOB
#define HCSR04_4_Pinsource	GPIO_PinSource1

#define UPData 	420

#define UnCatch 0
#define Catched	1
#define Finish  3
#define Fail    4
typedef struct
{
	uint32_t upcount_time;
	uint16_t data_channel_1;
	uint16_t data_channel_2;
	uint16_t data_channel_3;
	uint16_t data_channel_4;
	uint8_t channel_1_flag;
	uint8_t channel_2_flag;
	uint8_t channel_3_flag;
	uint8_t channel_4_flag;
}_hcsr04;

extern _hcsr04 hcsr04;
void TIM_HCSR04_Config(uint16_t psc,uint16_t arr);
void HCSR04_TIM_Start(void);
void HCSR04_TIM_StopAndRead(float *channel_1 ,float *channel_2,float *channel_3,float *channel_4);
#endif
