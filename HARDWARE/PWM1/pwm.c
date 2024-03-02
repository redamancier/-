
#include "stm32f4xx.h"
#include "pwm.h"

extern float Final_MOTOR1;
extern float Final_MOTOR2;


void PWM_NVIC_Config(void)
{
	NVIC_InitTypeDef pwm_nvic;
	
	pwm_nvic.NVIC_IRQChannel = PWM_IRQ;
	pwm_nvic.NVIC_IRQChannelPreemptionPriority = 1 ;
	pwm_nvic.NVIC_IRQChannelSubPriority = 0;
	pwm_nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&pwm_nvic);
	
}

void PWM_Config(uint32_t arr, uint32_t per)
{
	GPIO_InitTypeDef pwm_gpio;
	TIM_TimeBaseInitTypeDef pwm_tim;
	TIM_OCInitTypeDef pwm_tim_oc;
	//clk
	RCC_AHB1PeriphClockCmd(GPIO_PWM_CLK, ENABLE);
	RCC_APB1PeriphClockCmd(GPIO_PWM_TIM_CLK, ENABLE);
	//复用
	GPIO_PinAFConfig(GPIO_PWM, GPIO_PWM1_Pinsource, GPIO_PWM1_AF);
	GPIO_PinAFConfig(GPIO_PWM, GPIO_PWM3_Pinsource, GPIO_PWM3_AF);
	
	//gpio
	pwm_gpio.GPIO_Mode = GPIO_Mode_AF;
	pwm_gpio.GPIO_OType = GPIO_OType_PP;
	pwm_gpio.GPIO_Pin = GPIO_PWM1_PIN;
	pwm_gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
	pwm_gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_PWM, &pwm_gpio);
	
	pwm_gpio.GPIO_Pin = GPIO_PWM3_PIN;
	GPIO_Init(GPIO_PWM, &pwm_gpio);
	
	
	//tim
	pwm_tim.TIM_Period = arr;
	pwm_tim.TIM_Prescaler = per;
	pwm_tim.TIM_ClockDivision = 0;
	pwm_tim.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(GPIO_TIM, &pwm_tim);
	//tim_oc
	pwm_tim_oc.TIM_OCMode = TIM_OCMode_Toggle;
	pwm_tim_oc.TIM_OutputState = TIM_OutputState_Enable;
	pwm_tim_oc.TIM_Pulse = 0;
	pwm_tim_oc.TIM_OCPolarity = TIM_CounterMode_Up;
	TIM_OC1Init(GPIO_TIM, &pwm_tim_oc);
	TIM_OC3Init(GPIO_TIM, &pwm_tim_oc);
	//nvic
	PWM_NVIC_Config();
	//enable
	TIM_OC1PreloadConfig(GPIO_TIM, TIM_OCPreload_Disable);
	TIM_OC3PreloadConfig(GPIO_TIM, TIM_OCPreload_Disable);
	
	TIM_ITConfig(GPIO_TIM, TIM_IT_CC1|TIM_IT_CC3, ENABLE);
	
	TIM_Cmd(GPIO_TIM, ENABLE);
	
}

void PWM_IRQHandler(void)
{
	float Capture1,Capture3;
	if(TIM_GetITStatus(GPIO_TIM, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(GPIO_TIM, TIM_IT_Update);
	}
	if(TIM_GetITStatus(GPIO_TIM, TIM_IT_CC1)!=RESET)
	{
		
		Capture1 = TIM_GetCapture1(GPIO_TIM);
    TIM_SetCompare1(GPIO_TIM, Capture1 + Final_MOTOR1 );//设置TIMx自动重装载寄存器值
		
		TIM_ClearITPendingBit(GPIO_TIM, TIM_IT_CC1);
	}
	
	if(TIM_GetITStatus(GPIO_TIM, TIM_IT_CC3)!=RESET)
	{
		Capture3 = TIM_GetCapture3(GPIO_TIM);
    TIM_SetCompare3(GPIO_TIM, Capture3 + Final_MOTOR2 );//设置TIMx自动重装载寄存器值
		TIM_ClearITPendingBit(GPIO_TIM, TIM_IT_CC3);
	}
}



