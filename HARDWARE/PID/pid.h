#ifndef __PID_H
#define __PID_H

#include <stm32f4xx.h>
#include "motor.h"
#include "pwm.h"
#include "control.h"

#define TARGET_V          37.0f
#define MACHINE_CENTRAL   0.3f  //-0.3f

#define INF_INTEGRATE	    0.f
#define INF_INTEGRATE_MAX	11000

#define ANGLE_KP	        1.f  //MIN//1550                                  //MAX//1700
#define ANGLE_KI 	        0.f      //min//1                                        //max//1
#define ANGLE_KD	        0.f    

#define GYRO_KP	          200.0f   //min//2.5                      0.078                 //max//3.7
#define GYRO_KI 	        0.f
#define GYRO_KD	          0.f    //min//0.5                        0.08                    //max//0.71

#define FLAG_HCSR04       0

//还要再调
                         

#define BALAN_KP          -197.657f  //min -218.46f                                          //max -220.46f
#define BALAN_KI          -5.37f  //0.034     (-4.25f)    -9.86       -6.86     -4.86f
#define BALAN_KD          -0.087f  //0.02

#define VELOCITY_KP         -0.01797f   //-0.44f      -0.08               -0.093f                     //-0.74f
#define VELOCITY_KI         -0.00026f       //-0.00069                       // -0.003f
#define VELOCITY_KD         -0.5f        //-0.9

#define TURN_KP           10.0f
#define TURN_KI           0.f
#define TURN_KD           0.f

#define T_KP              15.0f

typedef struct
{
	float Kp;
	float Ki;
	float Kd;
	
	float integrate;
	float integrate_max;
	
	float bias;
	float last_bias;
}_pid_inf;

float PID_Calc_angle(float input,float target);
float PID_Calc_gyro(float input,float target);
float PID_Clac_turn(float input, float target);
void Inrared_Filter(float *turn_pwm);
	

//要是想实现转向功能，可以考虑抑制某个电机的速度，即增大ARR的值
//抑制哪个电机就往哪个方向转




#endif
