
#ifndef __MPU_EXTI_H
#define __MPU_EXTI_H

#include <stm32f4xx.h>

#define MPU_INT_PORT     		GPIOC
#define MPU_INT_PIN      		GPIO_Pin_1
#define MPU_INT_CLK      		RCC_AHB1Periph_GPIOC
#define MPU_INT_PORTSOURCE  EXTI_PortSourceGPIOC
#define MPU_INT_PINSOURCE   EXTI_PinSource1
#define MPU_INT_LINE        EXTI_Line1
#define MPU_INT_IRQ         EXTI1_IRQn

#define MPUINT_ISR          EXTI1_IRQHandler

void MPU_Int_Config(void);





#endif
