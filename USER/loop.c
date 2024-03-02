
#include "loop.h"

Mpu_DataInitTypedef Mpu_Data = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
extern _sub_class System_TimeArrange[TaskNumber_Max];
extern MotorControl_typedef Motor_Control;                      //the struct of Motor
extern _hcsr04 hcsr04;
extern s32 error_flag;
extern float flag_test;
extern float Motor1_Per;
extern float Motor2_Per;
extern int Balance_Pwm, Velocity_Pwm, Turn_Pwm, FlagData;

float Angle_Balance = 0.f;
float Gyro_Balance = 0.f;
float Acceleration_Z = 0;
float Final_MOTOR1 = 0.0f;
float Final_MOTOR2 = 0.0f;

float showdata1 = 0;
float showdata2 = 0;
float showdata3 = 0;
float showdata4 = 0;

uint8_t pass_flag = 0;
float Turn_speed = 100.0f;
s32 test_flag;

void loop(void) {
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
    HCSR04_Init();
    Inrared_Config();
    delay_init(168);
    uart_init(115200);
    MyMPU_Init();
    Time_Arrangement_init();
    Motor_Start();
    System_Init();
    Set_Pwm(Motor1_Per, Motor2_Per);

    while (1) {
        //////////test///////////
        Get_Angle();
        Inrared_Calculate(Mpu_Data.pitch);
        Angle_Balance = velocity(Motor1_Per, Motor2_Per);
        Balance_Pwm = balance(Mpu_Data.pitch, Mpu_Data.ratePitch);
        Turn_Pwm = turn(Motor1_Per, Motor2_Per);
        //		  Turn_Pwm = PID_Clac_turn(Mpu_Data.yaw, Turn_Pwm);
        Motor1_Per = Balance_Pwm + Turn_Pwm * T_KP; //===计算左轮电机最终PWM
        Motor2_Per = Balance_Pwm - Turn_Pwm * T_KP; //===计算右轮电机最终PWM
        lit_Pwm();
        Set_Pwm(Motor1_Per, Motor2_Per);
        Motor_Move_Judge(&Mpu_Data.pitch);
        if (Motor_Control.machine_central_store != 0) {
        }
        balance_auto(Motor1_Per, Motor2_Per);
        HCSR04_TIM_StopAndRead(&showdata1, &showdata2, &showdata3, &showdata4);
        //		delay_ms(20);
        Send_HCSR04_ToPC_F1(showdata1, showdata2, showdata3, showdata4);
        //			Send_PIDCalc_ToPC_F1(Mpu_Data.pitch,
        //Mpu_Data.ratePitch);
        //		//////////test///////////
    }
}

void IMU_CalcAvrOffset(void) {
    uint16_t i;
    delay_ms(1);
    // 读取陀螺仪角度
    mpu_dmp_get_data(&Mpu_Data.roll, &Mpu_Data.pitch, &Mpu_Data.yaw);
    for (i = 0; i < 250; i++) {
        MPU_Get_Gyroscope(&Mpu_Data.ratePitch, &Mpu_Data.rateRoll,
                          &Mpu_Data.rateYaw);
        Mpu_Data.ratePitchOffset += Mpu_Data.ratePitch;
        Mpu_Data.rateYawOffset += Mpu_Data.rateYaw;
    }
    Mpu_Data.ratePitchOffset = (Mpu_Data.ratePitchOffset / 250);
    Mpu_Data.rateYawOffset = (Mpu_Data.rateYawOffset / 250);
}

void MyMPU_Init(void) {
    mpu_init();
    mpu_dmp_init();
    //	MPU_Int_Config();
    delay_ms(100);
    IMU_CalcAvrOffset();
}
