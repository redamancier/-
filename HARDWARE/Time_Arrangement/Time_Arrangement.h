
#ifndef __TIME_ARRANGEMENT_H
#define __TIME_ARRANGEMENT_H

#include <stm32f4xx.h>

#define TASK_RUNNING    0
#define TASK_NORUNNING  1
#define TASK_WAIT       2

#define Task_Finish     0
#define Task_UnFinish   1

#define TASK_ERROR      3

//ʵ��Ŀ�꣺
//���Դ��ԵĴ����жϵ�Ч��
//ʹ�ø�������ִ��ʱ��õ�����
//����ʹ�������и�����
//����ϵͳ�ȶ���
//��ÿ��Ի�ȡϵͳʱ��

#define SYSTEM                 TIM2
#define SYSTEM_CLK             RCC_APB1Periph_TIM2
#define SYSTEM_PERIOD          (1000-1) //1ms�ж�һ��
#define SYSTEM_PSC             (168-1)
#define SYSTEM_IRQ_CHANNEL     TIM2_IRQn
#define SYSTEM_IRQ             TIM2_IRQHandler

#define TaskNumber_Max         5

typedef enum
{
	System_Control = 0,
	Send_To_PID    = 1,
	Send_To_PC     = 2,
	Inrared        = 3,
	HCSR04         = 4,
}Task;


typedef struct
{
	unsigned int TaskNumber[TaskNumber_Max];
	uint32_t Task_Finish_Flag;
	int32_t Task_TimeToDelay;
	uint8_t  Task_Run_Flag;
	int8_t Task_TimeFlag;
	int (*_function)(void);
}_sub_class;

void Time_Arrangement_init(void);
void System_Init(void);
int Handler_task1(void);
int Handler_task2(void);
int Handler_task3(void);
int Handler_task4(void);
int Handler_task5(void);

#endif
