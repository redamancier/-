#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "stm32f4xx_conf.h"
#include "sys.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//Mini STM32������
//����1��ʼ��		   
//����ԭ��@ALIENTEK
//������̳:www.openedv.csom
//�޸�����:2011/6/14
//�汾��V1.4
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved
//********************************************************************************
//V1.3�޸�˵�� 
//֧����Ӧ��ͬƵ���µĴ��ڲ���������.
//�����˶�printf��֧��
//�����˴��ڽ��������.
//������printf��һ���ַ���ʧ��bug
//V1.4�޸�˵��
//1,�޸Ĵ��ڳ�ʼ��IO��bug
//2,�޸���USART_RX_STA,ʹ�ô����������ֽ���Ϊ2��14�η�
//3,������USART_REC_LEN,���ڶ��崮�����������յ��ֽ���(������2��14�η�)
//4,�޸���EN_USART1_RX��ʹ�ܷ�ʽ
////////////////////////////////////////////////////////////////////////////////// 	
#define USART_REC_LEN  			200  	//�����������ֽ��� 200
#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����

#define Font 		  (1 << 1)
#define Back 		  (1 << 2) 
#define FB_Stand 	(1 << 0)

#define Left 	  	(1 << 4)
#define Right 		(1 << 5)
#define LR_Stand 	(1 << 3)

#define Begin      1
#define Done       1
#define UnDone     0

#define CAR_RECEIVE_DATA_LENGTH	1

typedef enum
{
	Head_1      = 0,
	Head_2      = 1,
	Car_Event   = 2,
	Move_Speed  = 3,
	Turn_Speed  = 4,
	End         = 5,
}Data_Mean;
	  	
extern u8  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART_RX_STA;         		//����״̬���

typedef struct
{
	uint8_t Head1;
	uint8_t Head2;
	uint8_t End;
}_receive_flag;

typedef struct
{
	_receive_flag Flag;
	uint8_t Car_StatusEvent;
	uint8_t Car_Data[CAR_RECEIVE_DATA_LENGTH];
	int move_speed;
	int turn_speed;
}_receive_data;

extern _receive_data Receive_Data;

//����봮���жϽ��գ��벻Ҫע�����º궨��
void uart_init(u32 bound);
#endif


