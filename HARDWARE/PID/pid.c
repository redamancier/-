

#include "loop.h"

float AnglePower = ANGLEPOWER_SET;

_pid_inf PID_gyro = 
	{
		GYRO_KP,
		GYRO_KI,
		GYRO_KD,
		INF_INTEGRATE,
	  INF_INTEGRATE_MAX,
	  0.f,
	  0.f
	};
	
_pid_inf PID_angle = 
 {
	ANGLE_KP,
	ANGLE_KI,
	ANGLE_KD,
	INF_INTEGRATE,
	INF_INTEGRATE_MAX,
	0.f,
	0.f
 };
 
_pid_inf PID_turn = 
 {
	 TURN_KP,
	 TURN_KI,
	 TURN_KD,
	 INF_INTEGRATE,
	 INF_INTEGRATE_MAX,
	 0.f,
	 0.f
 };

float PID_Calc_angle(float input,float target)
{
	float Output = 0.f;
	
	PID_angle.bias = input - target;
	
	PID_angle.integrate += PID_angle.bias;
	
	if(PID_angle.integrate > PID_angle.integrate_max )
		PID_angle.integrate = PID_angle.integrate_max;
	else if(PID_angle.integrate < -PID_angle.integrate_max )
		PID_angle.integrate = -PID_angle.integrate_max;
	
	Output = PID_angle.Kp * PID_angle.bias * AnglePower + PID_angle.Ki * PID_angle.integrate * AnglePower + PID_angle.Kd * 
			(PID_angle.bias - PID_angle.last_bias) * AnglePower;
	
	PID_angle.last_bias = PID_angle.bias ;
	
	return Output;
}

float PID_Calc_gyro(float input,float target)
{
	float Output = 0.f;
	
	PID_gyro.bias = input - target;
	
	PID_gyro.integrate += PID_gyro.bias;
	
	if(PID_gyro.integrate > PID_gyro.integrate_max)
		PID_gyro.integrate = PID_gyro.integrate_max;
	else if(PID_gyro.integrate < -PID_gyro.integrate_max )
		PID_gyro.integrate = -PID_gyro.integrate_max;
	
	Output = PID_gyro.Kp * PID_gyro.bias  + PID_gyro.Ki * PID_gyro.integrate + PID_gyro.Kd * 
			(PID_gyro.bias - PID_gyro.last_bias) ;
	
	PID_gyro.last_bias = PID_gyro.bias ;
	
	return Output;
}

float PID_Clac_turn(float input, float target)
{
	float Output = 0.f;
	PID_turn.bias = input - target;
	PID_turn.integrate += PID_turn.bias;
	
	if(PID_turn.integrate > PID_turn.integrate_max)
		PID_turn.integrate = PID_turn.integrate_max;
	if(PID_turn.integrate < -PID_turn.integrate_max)
		PID_turn.integrate = -PID_turn.integrate_max;
	
	Output = PID_turn.Kp * PID_turn.bias + PID_turn.Ki * PID_turn.integrate + PID_turn.Kd * (PID_turn.last_bias - PID_turn.bias);
	PID_turn.last_bias = PID_turn.bias;
	
	return Output;
}





