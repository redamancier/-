
#include "loop.h"
#include <math.h>

extern MotorControl_typedef Motor_Control;
extern Mpu_DataInitTypedef Mpu_Data;
extern _pid_inf PID_gyro;
extern _pid_inf PID_angle;
extern float AnglePower;
extern	short gyro[3], accel[3];
extern float angle;

int StopFlag = 0;
float Motor1_Per = 0.f;
float Motor2_Per = 0.f;
float gyro_filter[50] = {0};
unsigned int FlagJudge = 0;

void Motor_Start(void)
{
  Motor_Control_Config();
	delay_ms(2500);
  PWM_Config(PWM_PERIOD, PWM_PERISCAR);
	MOTOR1_START;
	MOTOR2_START;
}

void Motor_Move_Judge(float *angle)
{	
	if ( *angle > MOTOR_ANGLE_MAX || *angle < -MOTOR_ANGLE_MAX)
	{
		MOTOR1_STOP;
		MOTOR2_STOP;
    FlagJudge = 1;		
	}
	if (FlagJudge == 1)
	{
		PID_angle.integrate = 0.f;
		PID_gyro.integrate = 0.f;
		Final_MOTOR1 = 0;
		Final_MOTOR2 = 0;
		MOTOR1_STOP;
		MOTOR2_STOP;
		StopFlag = 1;
	}
	if(HCSR04_Data.left_1.cur_data < 50
		|| HCSR04_Data.left_2.cur_data < 50
	  || HCSR04_Data.right_1.cur_data < 50
	  || HCSR04_Data.right_2.cur_data < 50)
	{
		if(HCSR04_Data.left_1.cur_data > 20
		|| HCSR04_Data.left_2.cur_data < 20
	  || HCSR04_Data.right_1.cur_data < 20
	  || HCSR04_Data.right_2.cur_data < 20)
		{
		Motor_Control.machine_central_store = -50;
		}
	}
}




int Balance_Pwm,Velocity_Pwm,Turn_Pwm;
u8 Flag_Target;
u32 Flash_R_Count;
int Voltage_Temp,Voltage_Count,Voltage_All;


int balance(float Angle ,float Gyro)
{  
   float Bias;    //����DΪ��
	 int balance;
	 Bias=Angle - (Angle_Balance + MACHINE_CENTRAL);          //===���ƽ��ĽǶ���ֵ �ͻ�е���
	
//	 if(Bias > -1.0f && Bias < 1.0f)
//	 {
//	 Bias = 0.f;
//	 }		 
//	
 	 PID_angle.integrate += Bias;
	 if(PID_angle.integrate > INF_INTEGRATE_MAX )
	 PID_angle.integrate = INF_INTEGRATE_MAX;
	 else if(PID_angle.integrate < -INF_INTEGRATE_MAX )
	 PID_angle.integrate = -INF_INTEGRATE_MAX;
	 
	 balance=BALAN_KP*Bias+BALAN_KI*PID_angle.integrate+BALAN_KD*Gyro;      //===����ƽ����Ƶĵ��PWM 
	 
	 
	 return balance;
}


int velocity(int velocity_left,int velocity_right)
{  
	  static float Encoder_Integral; 
    static float Velocity,Encoder_Least,Encoder,Movement;
	  static float Target_Velocity=TARGET_V;//7000
	  Target_Velocity += Motor_Control.machine_central_store; 
		if(1==Motor_Control.all_move_flag)    	Movement=Target_Velocity;	           //===ǰ����־λ��1 
		else if(0==Motor_Control.all_move_flag)	Movement=-Target_Velocity;           //===���˱�־λ��1
  	else  Movement=0;
   //=============�ٶ�PI������=======================//	
		Encoder_Least=Mean_Filter(velocity_left,velocity_right);          //�ٶ��˲�  
		Encoder *= 0.7f;		                                                //===һ�׵�ͨ�˲���       
		Encoder += Encoder_Least*0.3f;	                                    //===һ�׵�ͨ�˲���    
		Encoder_Integral +=Encoder;                                       //===���ֳ�λ�� 
		Encoder_Integral +=Movement;                                      //===����ң�������ݣ�����ǰ������
		if(Encoder_Integral>32000)  	Encoder_Integral=32000;            //===�����޷�
		if(Encoder_Integral<-32000)	Encoder_Integral=-32000;              //===�����޷�	
		Velocity=Encoder*VELOCITY_KP/100+Encoder_Integral*VELOCITY_KI/100;     //===�ٶȿ���	
//  	if(Turn_Off(Angle_Balance,Voltage)==1)    Encoder_Integral=0;      //===����رպ��������
	  return Velocity;
}


int turn(int velocity_left,int velocity_right)//ת�����
{
		static float Turn_Amplitude=1200,Turn_Target,Turn_Convert=0.3;     
	  static float Turn_Count,Encoder_temp;
	  	if(inrared.inrared_start_flag == TURN_RIGHT
				||inrared.inrared_start_flag == TURN_LEFT)                      //��һ������Ҫ�Ǹ�����תǰ���ٶȵ����ٶȵ���ʼ�ٶȣ�����С������Ӧ��
		{
			if(++Turn_Count==1)
			Encoder_temp=myabs(velocity_left+velocity_right);
			Turn_Convert=900/Encoder_temp;
			if(Turn_Convert<2)Turn_Convert=2;
			if(Turn_Convert>20)Turn_Convert=20;
		}	
	  else
		{
			Turn_Convert=6;
			Turn_Count=0;
			Encoder_temp=0;
		}			
		if(inrared.inrared_start_flag == TURN_RIGHT)	           Turn_Target+=Turn_Convert;
		else if(inrared.inrared_start_flag == TURN_LEFT)	     Turn_Target-=Turn_Convert; 
		else Turn_Target=0;
    if(Turn_Target>Turn_Amplitude)  Turn_Target=Turn_Amplitude;    //===ת���ٶ��޷�
	  if(Turn_Target<-Turn_Amplitude) Turn_Target=-Turn_Amplitude;
	  return Turn_Target;
}


void Set_Pwm(int moto1,int moto2)
{
      if(moto1>0)			     MOTOR1_MOVE;
			else 	               MOTOR1_BACK;   
	   	if(moto2>0)			     MOTOR2_MOVE; 
			else 	               MOTOR2_BACK;    
	    Final_MOTOR1=Linear_Conversion(moto1);  //���Ի�
    	Final_MOTOR2=Linear_Conversion(moto2);
}

void lit_Pwm(void)
{	
	  int Amplitude_H=11000, Amplitude_L=-11000;       
    if(Motor1_Per<Amplitude_L)  Motor1_Per=Amplitude_L;	
		if(Motor1_Per>Amplitude_H)  Motor1_Per=Amplitude_H;	
	  if(Motor2_Per<Amplitude_L)  Motor2_Per=Amplitude_L;	
		if(Motor2_Per>Amplitude_H)  Motor2_Per=Amplitude_H;	
}



extern float Angle_Balance;
extern float Gyro_Balance;

void Get_Angle(void)
{
  float Accel_Y,Accel_Angle,Accel_Z,Gyro_X,Gyro_Z;	

	
			Gyro_X=(I2C_ReadOneByte(devAddr,MPU_GYRO_XOUTH_REG)<<8)+I2C_ReadOneByte(devAddr,MPU_GYRO_XOUTL_REG);    //��ȡY��������
			Gyro_Z=(I2C_ReadOneByte(devAddr,MPU_GYRO_ZOUTH_REG)<<8)+I2C_ReadOneByte(devAddr,MPU_GYRO_ZOUTL_REG);    //��ȡZ��������
		  Accel_Y=(I2C_ReadOneByte(devAddr,MPU_ACCEL_YOUTH_REG)<<8)+I2C_ReadOneByte(devAddr,MPU_ACCEL_YOUTL_REG); //��ȡX����ٶȼ�
	  	Accel_Z=(I2C_ReadOneByte(devAddr,MPU_ACCEL_ZOUTH_REG)<<8)+I2C_ReadOneByte(devAddr,MPU_ACCEL_ZOUTL_REG); //��ȡZ����ٶȼ�
		  if(Gyro_X>32768)  Gyro_X-=65536;                       //��������ת��  Ҳ��ͨ��shortǿ������ת��
			if(Gyro_Z>32768)  Gyro_Z-=65536;                       //��������ת��
	  	if(Accel_Y>32768) Accel_Y-=65536;                      //��������ת��
		  if(Accel_Z>32768) Accel_Z-=65536;                      //��������ת��
	   	Accel_Angle=atan2(Accel_Y,Accel_Z)*180/PI;             //�������	
			Mpu_Data.ratePitch=Gyro_X;                                  //===����ƽ����ٶ�	
			Gyro_X=Gyro_X/16.4f;                                    //����������ת��	
      Kalman_Filter(Accel_Angle,Gyro_X);//�������˲�	
//			else if(Way_Angle==3)   Yijielvbo(Accel_Angle,Gyro_X);    //�����˲�
	    Mpu_Data.pitch=angle;                                   //����ƽ�����
			Acceleration_Z=Accel_Z;                                //===����Z����ٶȼ�	
}

int myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}

int Mean_Filter(int moto1,int moto2)
{
  u8 i;
  s32 Sum_Speed = 0; 
	s16 Filter_Speed;
  static  s16 Speed_Buf[FILTERING_TIMES]={0};
  for(i = 1 ; i<FILTERING_TIMES; i++)
  {
    Speed_Buf[i - 1] = Speed_Buf[i];
  }
  Speed_Buf[FILTERING_TIMES - 1] =moto1+moto2;

  for(i = 0 ; i < FILTERING_TIMES; i++)
  {
    Sum_Speed += Speed_Buf[i];
  }
  Filter_Speed = (s16)(Sum_Speed / FILTERING_TIMES);
	return Filter_Speed;
}


u16  Linear_Conversion(int moto)
{ 
	 u32 temp;
   u16 Linear_Moto;
   temp=36000000/(PWM_PERISCAR+1)/13000*5000/myabs(moto);
	 if(temp>65535) Linear_Moto=65535;
	 else Linear_Moto=(u16)temp;
	 return Linear_Moto;
}	


void  balance_auto(int moto1,int moto2)
{
	    static int  count;
     if(Motor_Control.machine_central_Flag == 0)
		 {
		    if(myabs(moto1)<100&&myabs(moto2)<100)  		count++;		//����
				else			                                	count=0;	
				if(count>300)  //����3�봦��ƽ��λ�ã���ȡ��ֵ
				{	
				Motor_Control.machine_central_store =(int)Angle_Balance;	
				Motor_Control.machine_central_Flag=1;
				}
		 } 
}











