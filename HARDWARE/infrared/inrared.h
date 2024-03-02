
#ifndef __INRARED_H
#define __INRARED_H

#include <stm32f4xx.h>
#include "delay.h"
#include "sys.h"
#include "Time_Arrangement.h"


typedef struct
{
	uint8_t inrared_start_flag;
	uint8_t inrared_send_data;
	uint8_t inrared_black;
	uint8_t inrared_OtherColor;
	uint8_t inrared_channel1;  //outside right
	uint8_t inrared_channel2;  //central right
	uint8_t inrared_channel3;  //central left
	uint8_t inrared_channel4;  //outside left
}_inrared;

#define inrared_start               1
#define inrared_stop                0
#define black                       1
#define OtherColor                  0

#define TURN_RIGHT                  0
#define TURN_LEFT                   1
#define TURN_NOTURN                 2

#define INRARED_TIM_AF              GPIO_AF_TIM5
#define INRARED_TIM                 TIM5
#define INRARED_TIM_CLK             RCC_APB1Periph_TIM5
#define INRARED_TIM_IRQn            TIM5_IRQn
#define INRARED_ISR                 TIM5_IRQHandler
#define INRARED_TIM_PERIOD          65535
#define INRARED_TIM_PSC             71
#define INRARED_TIM_CCR1            5
#define INRARED_TIM_CCR2            5
#define INRARED_TIM_CCR3            5
#define INRARED_TIM_CCR4            5

#define INRARED_GPIO_PORT1          GPIOA       //TIM5 PA0~4 CH1~4
#define INRARED_GPIO_CLK           RCC_AHB1Periph_GPIOA

//#define INRARED_GPIO_PORT2          GPIOB       //TIM4 PB6~7 CH1~2
//#define INRARED_GPIO_CLK2           RCC_AHB1Periph_GPIOB

#define INRARED_GPIO_CHANNEL1       GPIO_Pin_0
#define INRARED_GPIO_PINSOURCE1     GPIO_PinSource0
#define INRARED_GPIO_AF1            GPIO_AF_TIM5
#define INRARED_1                   TIM_Channel_1

#define INRARED_GPIO_CHANNEL2       GPIO_Pin_1
#define INRARED_GPIO_PINSOURCE2     GPIO_PinSource1
#define INRARED_GPIO_AF2            GPIO_AF_TIM5
#define INRARED_2                   TIM_Channel_2

#define INRARED_GPIO_CHANNEL3       GPIO_Pin_2
#define INRARED_GPIO_PINSOURCE3     GPIO_PinSource2
#define INRARED_GPIO_AF3            GPIO_AF_TIM5
#define INRARED_3                   TIM_Channel_3

#define INRARED_GPIO_CHANNEL4       GPIO_Pin_3
#define INRARED_GPIO_PINSOURCE4     GPIO_PinSource3
#define INRARED_GPIO_AF4            GPIO_AF_TIM5
#define INRARED_4                   TIM_Channel_4

void Inrared_Config(void);
void Inrared_SendDataToPID(uint8_t *OutRig, uint8_t *CenRig, uint8_t *CenLef, uint8_t *OutLef);
void Inrared_Calculate(float angle);


extern _inrared inrared;



#endif
