#include "hcsr04.h"
#include "tim_hcsr04.h"
#include "delay.h"

_hcsr04_data_t HCSR04_Data = {0};

void HCSR04_Init(void)
{
	GPIO_InitTypeDef gpio;
	RCC_AHB1PeriphClockCmd(HCSR04_TRIG_1_CLK|HCSR04_TRIG_2_CLK|HCSR04_TRIG_3_CLK|HCSR04_TRIG_4_CLK,ENABLE);
	
	gpio.GPIO_Mode=GPIO_Mode_OUT;
	gpio.GPIO_OType=GPIO_OType_PP;
	gpio.GPIO_Pin=HCSR04_TRIG_1_Pin;
	gpio.GPIO_PuPd=GPIO_PuPd_DOWN;
	gpio.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(HCSR04_TRIG_1_Port,&gpio);
	
	gpio.GPIO_Pin=HCSR04_TRIG_2_Pin;
	GPIO_Init(HCSR04_TRIG_2_Port,&gpio);
	
	gpio.GPIO_Pin=HCSR04_TRIG_3_Pin;
	GPIO_Init(HCSR04_TRIG_3_Port,&gpio);
	
	gpio.GPIO_Pin=HCSR04_TRIG_4_Pin;
	GPIO_Init(HCSR04_TRIG_4_Port,&gpio);

	TIM_HCSR04_Config(UPData-1,65535);
}
void HCSR04_Start(void)
{
	HCSR04_TRIG_1_Reset;
	HCSR04_TRIG_2_Reset;
	HCSR04_TRIG_3_Reset;
	HCSR04_TRIG_4_Reset;
	
	delay_us(5);
	
	HCSR04_TRIG_1_Set;
	HCSR04_TRIG_2_Set;
	HCSR04_TRIG_3_Set;
	HCSR04_TRIG_4_Set;
	
	delay_us(20);
	
	HCSR04_TRIG_1_Reset;
	HCSR04_TRIG_2_Reset;
	HCSR04_TRIG_3_Reset;
	HCSR04_TRIG_4_Reset;
	
//	delay_us(20);
	
	HCSR04_TIM_Start();
}

void HCSR04_Data_Filter(_hcsr04_obj *structure)
{
	if((structure->cur_data < 0 || structure->cur_data - structure->last_data > 10 )&&structure->cur_data != 0)
		structure->cur_data = structure->last_data;
}
void HCSR04_UpdateData(void)
{
	HCSR04_Read(&HCSR04_Data.left_1.cur_data,&HCSR04_Data.left_2.cur_data,
					&HCSR04_Data.right_1.cur_data,&HCSR04_Data.right_2.cur_data);
	HCSR04_Data_Filter(&HCSR04_Data.left_1);
	HCSR04_Data_Filter(&HCSR04_Data.left_2);
	HCSR04_Data_Filter(&HCSR04_Data.right_1);
	HCSR04_Data_Filter(&HCSR04_Data.right_2);
}

