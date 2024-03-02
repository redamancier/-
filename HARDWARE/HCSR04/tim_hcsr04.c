#include "tim_hcsr04.h"
_hcsr04 hcsr04={0,0,0,0,0,UnCatch,UnCatch,UnCatch,UnCatch};
static void TIM_HCSR04_NVIC_Config(void)
{
	NVIC_InitTypeDef nvic;
	nvic.NVIC_IRQChannel=TIM_HCSR04_IRQn;
	nvic.NVIC_IRQChannelCmd=ENABLE;
	nvic.NVIC_IRQChannelPreemptionPriority=2;
	nvic.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&nvic);
}
void TIM_HCSR04_Config(uint16_t psc,uint16_t arr)
{
	TIM_TimeBaseInitTypeDef tim_base;
	GPIO_InitTypeDef gpio;
	TIM_ICInitTypeDef tim_ic;
	
	TIM_HCSR04_NVIC_Config();
	RCC_AHB1PeriphClockCmd(HCSR04_1_CLK|HCSR04_2_CLK|HCSR04_3_CLK|HCSR04_4_CLK,ENABLE);
	RCC_APB1PeriphClockCmd(TIM_HCSR04_CLK,ENABLE);
	
	gpio.GPIO_Mode=GPIO_Mode_AF;
	gpio.GPIO_OType=GPIO_OType_PP;
	gpio.GPIO_Pin=HCSR04_1_GPIO_Pin;
	gpio.GPIO_PuPd=GPIO_PuPd_DOWN;
	gpio.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(HCSR04_1_GPIO_Port,&gpio);
	GPIO_PinAFConfig(HCSR04_1_GPIO_Port,HCSR04_1_Pinsource,TIM_HCSR04_AF);
	
	gpio.GPIO_Pin=HCSR04_2_GPIO_Pin;
	GPIO_Init(HCSR04_2_GPIO_Port,&gpio);
	GPIO_PinAFConfig(HCSR04_2_GPIO_Port,HCSR04_2_Pinsource,TIM_HCSR04_AF);
	
	gpio.GPIO_Pin=HCSR04_3_GPIO_Pin;
	GPIO_Init(HCSR04_3_GPIO_Port,&gpio);
	GPIO_PinAFConfig(HCSR04_3_GPIO_Port,HCSR04_3_Pinsource,TIM_HCSR04_AF);
	
	gpio.GPIO_Pin=HCSR04_4_GPIO_Pin;
	GPIO_Init(HCSR04_4_GPIO_Port,&gpio);
	GPIO_PinAFConfig(HCSR04_4_GPIO_Port,HCSR04_4_Pinsource,TIM_HCSR04_AF);
	
	tim_base.TIM_ClockDivision=TIM_CKD_DIV1;
	tim_base.TIM_CounterMode=TIM_CounterMode_Up;
	tim_base.TIM_Period=arr;
	tim_base.TIM_Prescaler=psc;
	tim_base.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM_HCSR04,&tim_base);
	
	tim_ic.TIM_Channel=HCSR04_1;
	tim_ic.TIM_ICFilter=0;
	tim_ic.TIM_ICPolarity=TIM_ICPolarity_Rising;
	tim_ic.TIM_ICPrescaler=TIM_ICPSC_DIV1;
	tim_ic.TIM_ICSelection=TIM_ICSelection_DirectTI;
	TIM_ICInit(TIM_HCSR04,&tim_ic);
	
	tim_ic.TIM_Channel=HCSR04_2;
	TIM_ICInit(TIM_HCSR04,&tim_ic);
	
	tim_ic.TIM_Channel=HCSR04_3;
	TIM_ICInit(TIM_HCSR04,&tim_ic);
	
	tim_ic.TIM_Channel=HCSR04_4;
	TIM_ICInit(TIM_HCSR04,&tim_ic);
	
	TIM_ClearFlag(TIM_HCSR04, TIM_FLAG_Update|TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4);
	TIM_ITConfig(TIM_HCSR04,TIM_IT_Update|TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4,ENABLE);
	
	TIM_Cmd(TIM_HCSR04,DISABLE);
}

void HCSR04_TIM_Start(void)
{
	hcsr04.channel_1_flag=UnCatch;
	hcsr04.channel_2_flag=UnCatch;
	hcsr04.channel_3_flag=UnCatch;
	hcsr04.channel_4_flag=UnCatch;
	hcsr04.data_channel_1=0;
	hcsr04.data_channel_2=0;
	hcsr04.data_channel_3=0;
	hcsr04.data_channel_4=0;
	hcsr04.upcount_time=0;
	
	TIM_HCSR04->CNT=0;
	TIM_HCSR04->CCR1=0;
	TIM_HCSR04->CCR2=0;
	TIM_HCSR04->CCR3=0;
	TIM_HCSR04->CCR4=0;
	TIM_OC1PolarityConfig(TIM_HCSR04,TIM_ICPolarity_Rising);
	TIM_OC2PolarityConfig(TIM_HCSR04,TIM_ICPolarity_Rising);
	TIM_OC3PolarityConfig(TIM_HCSR04,TIM_ICPolarity_Rising);
	TIM_OC4PolarityConfig(TIM_HCSR04,TIM_ICPolarity_Rising);
	
	TIM_Cmd(TIM_HCSR04,ENABLE);
}
void HCSR04_TIM_StopAndRead(float *channel_1 ,float *channel_2,float *channel_3,float *channel_4) //µ¥Î» cm
{
	TIM_Cmd(TIM_HCSR04,DISABLE);
	
	if(hcsr04.channel_1_flag==Finish && hcsr04.data_channel_1 < 1710 )
		*channel_1=(float)hcsr04.data_channel_1 * 0.3502f;
	else *channel_1=-1;
	
	if(hcsr04.channel_2_flag==Finish && hcsr04.data_channel_2 < 1710)
		*channel_2=(float)hcsr04.data_channel_2 * 0.3502f;
	else *channel_2=-1;
	
	if(hcsr04.channel_3_flag==Finish && hcsr04.data_channel_3 < 1710)
		*channel_3=(float)hcsr04.data_channel_3 * 0.3502f;
	else *channel_3=-1;
	
	if(hcsr04.channel_4_flag==Finish && hcsr04.data_channel_4 < 1710)
		*channel_4=(float)hcsr04.data_channel_4 * 0.3502f;
	else *channel_4=-1;
}

void TIM_HCSR04_ISR(void)
{
	if(TIM_GetITStatus(TIM_HCSR04,TIM_IT_Update)!=RESET)
	{
		hcsr04.upcount_time++;
		TIM_ClearITPendingBit(TIM_HCSR04,TIM_IT_Update);
	}
	else if(TIM_GetITStatus(TIM_HCSR04,TIM_IT_CC1)!=RESET)
	{
		if(hcsr04.channel_1_flag==UnCatch)
		{
			TIM_OC1PolarityConfig(TIM_HCSR04,TIM_ICPolarity_Falling);
			
			hcsr04.data_channel_1=TIM_HCSR04->CCR1;
			hcsr04.channel_1_flag=Catched;
		}
		else if(hcsr04.channel_1_flag==Catched)
		{
			TIM_OC1PolarityConfig(TIM_HCSR04,TIM_ICPolarity_Rising);
			if(hcsr04.upcount_time==0)
			{
				hcsr04.data_channel_1=TIM_HCSR04->CCR1 - hcsr04.data_channel_1;
				hcsr04.channel_1_flag=Finish;
			}
			else 
			{
				hcsr04.data_channel_1=0;
				hcsr04.channel_1_flag=Fail;
			}
		}
		TIM_ClearITPendingBit(TIM_HCSR04,TIM_IT_CC1);
	}
	else if(TIM_GetITStatus(TIM_HCSR04,TIM_IT_CC2)!=RESET)
	{
		if(hcsr04.channel_2_flag==UnCatch)
		{
			TIM_OC2PolarityConfig(TIM_HCSR04,TIM_ICPolarity_Falling);
			
			hcsr04.data_channel_2=TIM_HCSR04->CCR2;
			hcsr04.channel_2_flag=Catched;
		}
		else if(hcsr04.channel_2_flag==Catched)
		{
			TIM_OC2PolarityConfig(TIM_HCSR04,TIM_ICPolarity_Rising);
			if(hcsr04.upcount_time==0)
			{
				hcsr04.data_channel_2=TIM_HCSR04->CCR2 - hcsr04.data_channel_2;
				hcsr04.channel_2_flag=Finish;
			}
			else 
			{
				hcsr04.data_channel_2=0;
				hcsr04.channel_2_flag=Fail;
			}
		}
		TIM_ClearITPendingBit(TIM_HCSR04,TIM_IT_CC2);
	}
	else if(TIM_GetITStatus(TIM_HCSR04,TIM_IT_CC3)!=RESET)
	{
		if(hcsr04.channel_3_flag==UnCatch)
		{
			TIM_OC3PolarityConfig(TIM_HCSR04,TIM_ICPolarity_Falling);
			
			hcsr04.data_channel_3=TIM_HCSR04->CCR3;
			hcsr04.channel_3_flag=Catched;
		}
		else if(hcsr04.channel_3_flag==Catched)
		{
			TIM_OC3PolarityConfig(TIM_HCSR04,TIM_ICPolarity_Rising);
			if(hcsr04.upcount_time==0)
			{
				hcsr04.data_channel_3=TIM_HCSR04->CCR3 - hcsr04.data_channel_3;
				hcsr04.channel_3_flag=Finish;
			}
			else 
			{
				hcsr04.data_channel_3=0;
				hcsr04.channel_3_flag=Fail;
			}
		}
		TIM_ClearITPendingBit(TIM_HCSR04,TIM_IT_CC3);
	}
	else if(TIM_GetITStatus(TIM_HCSR04,TIM_IT_CC4)!=RESET)
	{
		if(hcsr04.channel_4_flag==UnCatch)
		{
			TIM_OC4PolarityConfig(TIM_HCSR04,TIM_ICPolarity_Falling);
			
			hcsr04.data_channel_4=TIM_HCSR04->CCR4;
			hcsr04.channel_4_flag=Catched;
		}
		else if(hcsr04.channel_4_flag==Catched)
		{
			TIM_OC4PolarityConfig(TIM_HCSR04,TIM_ICPolarity_Rising);
			if(hcsr04.upcount_time==0)
			{
				hcsr04.data_channel_4=TIM_HCSR04->CCR4 - hcsr04.data_channel_4;
				hcsr04.channel_4_flag=Finish;
			}
			else 
			{
				hcsr04.data_channel_4=0;
				hcsr04.channel_4_flag=Fail;
			}
		}
		TIM_ClearITPendingBit(TIM_HCSR04,TIM_IT_CC4);
	}
}
