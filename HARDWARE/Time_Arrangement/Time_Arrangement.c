
#include "loop.h"

extern Mpu_DataInitTypedef Mpu_Data;
extern float Final_MOTOR1;
extern float Final_MOTOR2;
extern uint8_t pass_flag;

extern _pid_inf PID_gyro;
extern _pid_inf PID_angle;

extern float Motor1_Per;
extern float Motor2_Per;

int MpuCount0 = 0;
int MpuCount1 = 0;
int MpuCount2 = 0;
int MpuFilter[5] = {0};
float flag_test;

s32 error_flag = 0;


_sub_class System_TimeArrange[TaskNumber_Max] = 
{
  0
};

int Handler_task0(void)
{ //不可用
	int errorFlag = 1;
	//此处添加ADC及遥控器函数
//	Send_PIDCalc_ToPC_F1(System_TimeArrange[Send_To_PID].Task_TimeToDelay, System_TimeArrange[Inrared].Task_TimeToDelay);
	return errorFlag;
}

int Handler_task1(void)
{ //可用 
	int errorFlag = 2;

		    
	
	

	return errorFlag;
		
}

int Handler_task2(void)
{ //不可用
	//此处添加蓝牙发送函数
	int errorFlag = 3;
//	Send_HCSR04_ToPC_F1(Mpu_Data.pitch, Mpu_Data.ratePitch, PID_angle.bias, error_flag);
	
//	  
	return errorFlag;
}

int Handler_task3(void)
{ //不可用
	int errorFlag = 4;
	//此处添加红外寻线处理函数
//	  Inrared_Calculate();
//    Inrared_GiveToTurn();
	return errorFlag;
}

int Handler_task4(void)
{ //不可用
	int errorFlag = 5;
  //此处添加超声波函数
	return errorFlag;
}




void System_Init(void)
{
	Time_Arrangement_init();
	System_TimeArrange[System_Control].Task_Run_Flag = TASK_RUNNING;
	System_TimeArrange[System_Control].Task_TimeToDelay = 0;
	System_TimeArrange[System_Control].Task_TimeFlag = 0;
	System_TimeArrange[System_Control]._function = Handler_task0;
	System_TimeArrange[System_Control].Task_Finish_Flag = Task_UnFinish;
	
	System_TimeArrange[Send_To_PID].Task_Run_Flag = TASK_RUNNING;
	System_TimeArrange[Send_To_PID].Task_TimeToDelay = 0;
	System_TimeArrange[Send_To_PID].Task_TimeFlag = 0;
	System_TimeArrange[Send_To_PID]._function = Handler_task1;
	System_TimeArrange[Send_To_PID].Task_Finish_Flag = Task_UnFinish;
	
	System_TimeArrange[Send_To_PC].Task_Run_Flag = TASK_RUNNING;
	System_TimeArrange[Send_To_PC].Task_TimeToDelay = 0;
	System_TimeArrange[Send_To_PC].Task_TimeFlag = 0;
	System_TimeArrange[Send_To_PC]._function = Handler_task2;
	System_TimeArrange[Send_To_PC].Task_Finish_Flag = Task_UnFinish;
	
	System_TimeArrange[Inrared].Task_Run_Flag = TASK_RUNNING;
	System_TimeArrange[Inrared].Task_TimeToDelay = 0;
	System_TimeArrange[Inrared].Task_TimeToDelay = 0;
	System_TimeArrange[Inrared]._function = Handler_task3;
	System_TimeArrange[Inrared].Task_Finish_Flag = Task_UnFinish;
	
	System_TimeArrange[HCSR04].Task_Run_Flag = TASK_RUNNING;
	System_TimeArrange[HCSR04].Task_TimeToDelay = 0;
	System_TimeArrange[HCSR04].Task_TimeFlag = 0;
	System_TimeArrange[HCSR04]._function = Handler_task4;
	System_TimeArrange[HCSR04].Task_Finish_Flag = Task_UnFinish;
	
}

void Time_Arrangement_init(void)
{
	TIM_TimeBaseInitTypeDef time_table;
	NVIC_InitTypeDef system_nvic;
	
	//clk
	RCC_APB1PeriphClockCmd(SYSTEM_CLK, ENABLE);
	
	//time_table//
	time_table.TIM_Period = SYSTEM_PERIOD;
	time_table.TIM_Prescaler = SYSTEM_PSC;
	time_table.TIM_CounterMode = TIM_CounterMode_Up;
	time_table.TIM_ClockDivision = 0;
	time_table.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(SYSTEM, &time_table);
	//nvic//
	system_nvic.NVIC_IRQChannel = SYSTEM_IRQ_CHANNEL;
	system_nvic.NVIC_IRQChannelCmd = ENABLE;
	system_nvic.NVIC_IRQChannelPreemptionPriority = 0;
	system_nvic.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&system_nvic);
	
	TIM_ITConfig(SYSTEM, TIM_IT_Update, ENABLE);
	
	TIM_Cmd(SYSTEM, ENABLE);
	
}



void SYSTEM_IRQ(void)
{
//	float Balance_Pwm;	
	if(TIM_GetFlagStatus(SYSTEM, TIM_IT_Update) != RESET)
	{
//				unsigned int TaskNum = 0;
//		for(TaskNum = 0; TaskNum < TaskNumber_Max; TaskNum++)
//		{
//			if(System_TimeArrange[TaskNum].Task_Run_Flag == TASK_NORUNNING)
//			{
//				System_TimeArrange[TaskNum].Task_TimeToDelay--;
//			}
//		}																												
		TIM_ClearITPendingBit(SYSTEM, TIM_IT_Update);
	}
}



