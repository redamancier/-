
#ifndef __CONTROL_H
#define __CONTROL_H

#include "stm32f4xx.h"
#include "pid.h"
#include "motor.h"
#include "sys.h"
#include "delay.h"
#include "pwm.h"
#include "filter.h"
#include <math.h>



void Control_Config(void);

extern float Angle_Balance;
extern float Gyro_Balance;
extern float Final_MOTOR1;
extern float Final_MOTOR2;

#define MOTOR_MIN        25.0f
#define MOTOR_MAX   		 999.0f
#define MOTOR_ANGLE_MAX  50
#define ANGLEPOWER_SET   1.0f



//void Control_filter(void);
//void Control_Trun(u8 right, u8 left);
//void Control_Balance(u32 motor1, u32 motor2);

typedef struct
{
	u8 motor1_run_Flag;
	u8 motor1_move_flag;
	u8 motor1_back_flag;
	u8 motor2_move_flag;
	u8 motor2_back_flag;
	u8 all_move_flag;
	u8 all_back_flag;
	u8 motor2_run_Flag;
	u8 motor_enable;
	u8 machine_central_Flag;
	s32 machine_central_store;
	//u8 motor_stay;
}MotorControl_typedef;

//置0，为启动，置1，为关闭
//machine_central_Flag例外，置1为启动，置0为关闭

//void PID_ARR_GIVE(uint32_t *final_motor1, float *angle, float *gyro);

float PID_Handler(float *final_motor1, float *final_motor2, float angle, float gyro);
void Motor_Move_Judge(float *angle);
void Motor_Start(void);
void ReStand(float anlge_judge);
void PID_COPY(void);








#define PI 3.14159265
#define FILTERING_TIMES  10
extern	int Balance_Pwm,Velocity_Pwm,Turn_Pwm;
int EXTI15_10_IRQHandler(void);
int balance(float Angle ,float Gyro);
int velocity(int velocity_left,int velocity_right);
int turn(int velocity_left,int velocity_right);
void Set_Pwm(int moto1,int moto2);
void Key(void);
void lit_Pwm(void);
u8 Turn_Off(float angle, int voltage);
void Get_Angle(void);
int myabs(int a);
int Pick_Up(float Acceleration,float Angle,int encoder_left,int encoder_right);
int Put_Down(float Angle,int encoder_left,int encoder_right);
void speed_filter(void);
int Mean_Filter(int moto1,int moto2);
u16  Linear_Conversion(int moto);
void  Get_MC6(void);
void  balance_auto(int moto1,int moto2);












#endif
