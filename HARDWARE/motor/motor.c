
#include "stm32f4xx.h"
#include "motor.h"
#include "control.h"
#include "pid.h"

MotorControl_typedef Motor_Control = {0};



extern float Angle_Balance;
extern float Final_MOTOR1;
extern float Final_MOTOR2;

void Motor_Control_Config(void)
{
	GPIO_InitTypeDef dir_gpio;
	
	RCC_AHB1PeriphClockCmd(GPIO_LCK, ENABLE);
	
	dir_gpio.GPIO_Mode = GPIO_Mode_OUT;
	dir_gpio.GPIO_OType = GPIO_OType_PP;
	dir_gpio.GPIO_Pin = GPIO_DIR1_PIN;
	dir_gpio.GPIO_PuPd = GPIO_PuPd_UP;
	dir_gpio.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIO_DIR, &dir_gpio);
	
	dir_gpio.GPIO_Pin = GPIO_DIR2_PIN;
	GPIO_Init(GPIO_DIR, &dir_gpio);
	
	dir_gpio.GPIO_Pin = GPIO_EN1_PIN;
	GPIO_Init(GPIO_DIR, &dir_gpio);

	dir_gpio.GPIO_Pin = GPIO_EN2_PIN;
	GPIO_Init(GPIO_DIR, &dir_gpio);

	MOTOR1_BACK;
	MOTOR2_BACK;
	MOTOR1_STOP;
	MOTOR2_STOP;
}

