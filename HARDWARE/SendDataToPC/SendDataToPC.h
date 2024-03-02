
#ifndef __SENDDATA_H
#define __SENDDATA_H
#include <stm32f4xx.h>
#define Send_Data_ToPC(array,num) 	Usart_PC_SendArray((USART1),(array),(num))

#define BYTE0(Temp)		(*((unsigned char *)(&Temp)    ))
#define BYTE1(Temp)		(*((unsigned char *)(&Temp) + 1))
#define BYTE2(Temp)		(*((unsigned char *)(&Temp) + 2))
#define BYTE3(Temp)		(*((unsigned char *)(&Temp) + 3))
	
#define Font 		  (1 << 1)
#define Back 		  (1 << 2)
#define FB_Stand 	(1 << 0)

#define Left 	  	(1 << 4)
#define Right 		(1 << 5)
#define LR_Stand 	(1 << 3)

//typedef enum
//{
//	Head_1 = 0,
//	Head_2 = 1,
//	Car_Event =2,
//	Move_Speed = 3,
//	Turn_Speed = 4,
//	End = 5,
//}Data_Mean;

//typedef struct
//{
//	uint8_t Car_StatusEvent;
//	int move_speed;
//	int turn_speed;
//}_car_status;

///*car_receive_event*/

//#define CAR_RECEIVE_DATA_LENGTH	1

//typedef struct
//{
//	uint8_t Car_ReceiveEvent;
//	uint8_t Car_Data[CAR_RECEIVE_DATA_LENGTH];
//}_car_reveive;
//	
//extern _car_status Car_Status;

//void Send_Status_To_Car(void);
//	
//void Send_warningCalc_ToPC_F2(s32 err);
void Send_PIDCalc_ToPC_F1(s32 cur_data,s32 target);
void Usart_PC_Init(s32 bound);
void Send_HCSR04_ToPC_F1(s32 C1,s32 C2,s32 C3,s32 C4);

#endif
