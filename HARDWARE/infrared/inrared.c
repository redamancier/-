
#include <stm32f4xx.h>
#include "inrared.h"
#include "delay.h"
#include "sys.h"
#include "Time_Arrangement.h"

//there you can consider use the EXTI or TIM_IC to judge the Inrared_Data
//But now the EXTI can have occupy others' Cannel,if you can finnish the time_arrangement 
//you can don't use the EXTI

_inrared inrared = {0};

int FlagData = 0;
//static int store_v_m1 = 0, store_v_m2 = 0, counti;
int FilterOfInrared1;
int FilterOfInrared2;
int FilterOfInrared3;
int FilterOfInrared4;

void Inrared_Config(void)
{
	GPIO_InitTypeDef inrared;
	
	RCC_AHB1PeriphClockCmd(INRARED_GPIO_CLK, ENABLE);
	
	//gpio//
	inrared.GPIO_Mode = GPIO_Mode_IN;
	inrared.GPIO_PuPd = GPIO_PuPd_NOPULL;
	inrared.GPIO_Speed = GPIO_Speed_100MHz;
	inrared.GPIO_Pin = INRARED_GPIO_CHANNEL1;
	GPIO_Init(INRARED_GPIO_PORT1, &inrared);
	
	inrared.GPIO_Pin = INRARED_GPIO_CHANNEL2;
	GPIO_Init(INRARED_GPIO_PORT1, &inrared);
	
	inrared.GPIO_Pin = INRARED_GPIO_CHANNEL3;
	GPIO_Init(INRARED_GPIO_PORT1, &inrared);
	
	inrared.GPIO_Pin = INRARED_GPIO_CHANNEL4;
	GPIO_Init(INRARED_GPIO_PORT1, &inrared);
	
}

//正常
// 0 1 1 0//

//FlagData == -10
//0 1 0 0// or 
//1 1 0 1//
//turn left

//FlagData == 10
// 0 0 1 0// or 
//1 0 1 1//
//trun right

//FlagData == 50
//0 0 1 1//

//FlagData == -50
//1 1 0 0//

//FlagData == 30
//0 1 0 1//

//FlagData == -30
//1 0 1 0//


//FlagData == 40
//0 1 1 1// or
//0 0 0 1//
//miss a big turn, turn left

//FlagData == -40
//1 1 1 0// or
//1 0 0 0//
//miss a big turn, turn right

//warning//
//FlagData == 0
//First:  //0 1 1 0//
//Second: //0 0 0 0//
//third:  //1 0 0 1//
//if second NowSign = LastSign

void Inrared_Calculate(float angle)
{
	
	inrared.inrared_channel1 = GPIO_ReadInputDataBit(INRARED_GPIO_PORT1, INRARED_GPIO_CHANNEL1);
	inrared.inrared_channel2 = GPIO_ReadInputDataBit(INRARED_GPIO_PORT1, INRARED_GPIO_CHANNEL2);
	inrared.inrared_channel3 = GPIO_ReadInputDataBit(INRARED_GPIO_PORT1, INRARED_GPIO_CHANNEL3);
	inrared.inrared_channel4 = GPIO_ReadInputDataBit(INRARED_GPIO_PORT1, INRARED_GPIO_CHANNEL4);
	
	FlagData = inrared.inrared_channel1 * 40 + inrared.inrared_channel2 * 10 +
	inrared.inrared_channel3 * (-10) + inrared.inrared_channel4 * (-40);
	
//	switch(FlagData)
//	{
//		case 10:
//			inrared.inrared_start_flag = TURN_LEFT;
//		case 30:
//			inrared.inrared_start_flag = TURN_LEFT;
//		case 40:
//			inrared.inrared_start_flag = TURN_LEFT;
//		case 50:
//			inrared.inrared_start_flag = TURN_LEFT;
//		case 0:
//			inrared.inrared_start_flag = TURN_NOTURN;
//		case -10:
//			inrared.inrared_start_flag = TURN_RIGHT;
//		case -30:
//			inrared.inrared_start_flag = TURN_RIGHT;
//		case -40:
//			inrared.inrared_start_flag = TURN_RIGHT;		
//		case -50:
//			inrared.inrared_start_flag = TURN_RIGHT;
//		default:
//			inrared.inrared_start_flag = TURN_NOTURN;
//	}
	if(FlagData == -10 || FlagData == -40)
	{
    inrared.inrared_start_flag = TURN_RIGHT;		
	}
	else if(FlagData == 10 || FlagData == 40)
	{
    inrared.inrared_start_flag = TURN_LEFT;		
	}
	else if(FlagData == 0)
	{
		//keep move
		inrared.inrared_start_flag = TURN_NOTURN;
	}
	else
	{
		inrared.inrared_start_flag = TURN_NOTURN;
	}
//	if(angle > 5 || angle < -5)
//	{
//		//测量清零操作
//		inrared.inrared_start_flag = TURN_NOTURN;
//	}
	
}












