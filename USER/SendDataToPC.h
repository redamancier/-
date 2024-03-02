
#ifndef __SENDDATA_H
#define __SENDDATA_H
#include <stm32f4xx.h>
#define Send_Data_ToPC(array,num) 	Usart_PC_SendArray((USART1),(array),(num))

#define BYTE0(Temp)		(*((unsigned char *)(&Temp)    ))
#define BYTE1(Temp)		(*((unsigned char *)(&Temp) + 1))
#define BYTE2(Temp)		(*((unsigned char *)(&Temp) + 2))
#define BYTE3(Temp)		(*((unsigned char *)(&Temp) + 3))


void Send_PIDCalc_ToPC_F1(s32 cur_data,s32 target);
void Usart_PC_Init(u32 bound);

void Send_HCSR04_ToPC_F1(s32 C1,s32 C2,s32 C3,s32 C4);
#endif
