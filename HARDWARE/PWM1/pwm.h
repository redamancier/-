#ifndef __PWM_H
#define __PWM_H

#include "stm32f4xx.h"
 
#define GPIO_PWM              GPIOD
#define GPIO_TIM              TIM4
#define PWM_IRQ               TIM4_IRQn

#define GPIO_PWM1_PIN         GPIO_Pin_12
#define GPIO_PWM1_Pinsource   GPIO_PinSource12
#define GPIO_PWM1_AF          GPIO_AF_TIM4

#define GPIO_PWM3_PIN         GPIO_Pin_14
#define GPIO_PWM3_Pinsource   GPIO_PinSource14
#define GPIO_PWM3_AF          GPIO_AF_TIM4

#define GPIO_PWM_CLK          RCC_AHB1Periph_GPIOD
#define GPIO_PWM_TIM_CLK      RCC_APB1Periph_TIM4

#define PWM_PERIOD            65535     //max-max 50khz ³öÏÖ¶Â×ª   //max 47khz  //min 1khz //min(arr) 22     max(arr) 999
#define PWM_PERISCAR          33

#define PWM_IRQHandler        TIM4_IRQHandler

void PWM_Config(uint32_t arr, uint32_t per);
void PWM_NVIC_Config(void);

#endif

