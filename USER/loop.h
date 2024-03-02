#ifndef __LOOP_H
#define __LOOP_H

#include <stm32f4xx.h>
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "pwm.h"
#include "motor.h"
#include "Time_Arrangement.h"
#include "oled.h"
#include "hcsr04.h"
#include "inrared.h"
#include "MPU6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "pid.h"
#include "SendDataToPC.h"
#include "tim_hcsr04.h"
#include "control.h"
#include "filter.h"
#include "myiic.h"
#include "mpu_exti.h"

#define devAddr  0xD0

extern float Acceleration_Z;

	//小车开始前，首先给予时间初始化
	//当角度持续为零时（超过3000ms）时开始输出pid
	//暂时关闭红外输出和超声波输出
	//设置时间片系统方便调度各模块

void loop(void);
void MyMPU_Init(void);
//void System_Init(void);
void IMU_CalcAvrOffset(void);

//test




typedef struct {
	float store_test_data;
	float pitch;
	float roll;
	float yaw;
	short ratePitch;
	short rateRoll;
	short rateYaw;
	float pitchOffset;
	float rollOffset;
	float yawOffset;
	float ratePitchOffset;
	float rateRollOffset;
	float rateYawOffset;
	short accPitch;
	short accYaw;
	short accRoll;
	float pitch_last;
	
}Mpu_DataInitTypedef;


#endif
