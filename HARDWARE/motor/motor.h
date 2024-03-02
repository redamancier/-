
#ifndef __MOTOR_H
#define __MOTOR_H

//����С���������˶�����

//���ű�� GPIOD 8&9
//���ű�� GPIOD13 & 15


//��Ҫ����һ�������Է����õ��ֹͣת��������С��
//��Ҫ����³���ԣ�ϵͳ�ȶ��ԣ�


#include <stm32f4xx.h>

#define GPIO_DIR        GPIOD
#define GPIO_LCK        RCC_AHB1Periph_GPIOD

#define GPIO_DIR1_PIN   GPIO_Pin_8
#define GPIO_DIR2_PIN   GPIO_Pin_11
#define GPIO_EN1_PIN    GPIO_Pin_13
#define GPIO_EN2_PIN    GPIO_Pin_15

#define MOTOR1_BACK     GPIO_SetBits(GPIO_DIR, GPIO_DIR1_PIN)
#define MOTOR1_MOVE     GPIO_ResetBits(GPIO_DIR, GPIO_DIR1_PIN)

#define MOTOR2_MOVE     GPIO_SetBits(GPIO_DIR, GPIO_DIR2_PIN)
#define MOTOR2_BACK     GPIO_ResetBits(GPIO_DIR, GPIO_DIR2_PIN)

#define MOTOR1_STOP     GPIO_SetBits(GPIO_DIR, GPIO_EN1_PIN)
#define MOTOR1_START    GPIO_ResetBits(GPIO_DIR, GPIO_EN1_PIN)

#define MOTOR2_STOP     GPIO_SetBits(GPIO_DIR, GPIO_EN2_PIN)
#define MOTOR2_START    GPIO_ResetBits(GPIO_DIR, GPIO_EN2_PIN)


void Motor_Control_Config(void);

void Control_stand(void);

#endif
