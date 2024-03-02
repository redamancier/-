
#include <stm32f4xx.h>
#include "SendDataToPC.h"

void Usart_PC_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
	/* 发送一个字节数据到USART */
	USART_SendData(pUSARTx,ch);
		
	/* 等待发送数据寄存器为空 */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

void Usart_PC_SendArray( USART_TypeDef * pUSARTx, uint8_t *array, uint16_t num)
{
  uint8_t i;
	
	for(i=0; i<num; i++)
  {
	    /* 发送一个字节数据到USART */
	    Usart_PC_SendByte(pUSARTx,array[i]);	
  
  }
	/* 等待发送完成 */
	while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET);
}

//



void Send_PIDCalc_ToPC_F1(s32 cur_data,s32 target)
{
	uint16_t cnt=0;
	uint8_t DataToSend[30];
	uint8_t sc=0;
	uint8_t ac=0;
	uint8_t i=0;
	
	DataToSend[cnt++]=0xaa;
	DataToSend[cnt++]=0xff;
	DataToSend[cnt++]=0xf1;
	DataToSend[cnt++]=8;
	
	DataToSend[cnt++]=BYTE0(cur_data);
	DataToSend[cnt++]=BYTE1(cur_data);
	DataToSend[cnt++]=BYTE2(cur_data);
	DataToSend[cnt++]=BYTE3(cur_data);
	
	DataToSend[cnt++]=BYTE0(target);
	DataToSend[cnt++]=BYTE1(target);
	DataToSend[cnt++]=BYTE2(target);
	DataToSend[cnt++]=BYTE3(target);
	
	for(i=0;i<DataToSend[3]+4;i++)
	{
		sc+=DataToSend[i];
		ac+=sc;
	}
	
	DataToSend[cnt++]=sc;
	DataToSend[cnt++]=ac;
	
	Send_Data_ToPC(DataToSend,cnt);
}

void Send_HCSR04_ToPC_F1(s32 C1,s32 C2,s32 C3,s32 C4)
{
	uint16_t cnt=0;
	uint8_t DataToSend[50];
	uint8_t sc=0;
	uint8_t ac=0;
	uint8_t i=0;
	
	DataToSend[cnt++]=0xaa;
	DataToSend[cnt++]=0xff;
	DataToSend[cnt++]=0xf1;
	DataToSend[cnt++]=16;
	
	DataToSend[cnt++]=BYTE0(C1);
	DataToSend[cnt++]=BYTE1(C1);
	DataToSend[cnt++]=BYTE2(C1);
	DataToSend[cnt++]=BYTE3(C1);
	
	DataToSend[cnt++]=BYTE0(C2);
	DataToSend[cnt++]=BYTE1(C2);
	DataToSend[cnt++]=BYTE2(C2);
	DataToSend[cnt++]=BYTE3(C2);
	
	DataToSend[cnt++]=BYTE0(C3);
	DataToSend[cnt++]=BYTE1(C3);
	DataToSend[cnt++]=BYTE2(C3);
	DataToSend[cnt++]=BYTE3(C3);
	
	DataToSend[cnt++]=BYTE0(C4);
	DataToSend[cnt++]=BYTE1(C4);
	DataToSend[cnt++]=BYTE2(C4);
	DataToSend[cnt++]=BYTE3(C4);
	
	for(i=0;i<DataToSend[3]+4;i++)
	{
		sc+=DataToSend[i];
		ac+=sc;
	}
	
	DataToSend[cnt++]=sc;
	DataToSend[cnt++]=ac;
	
	Send_Data_ToPC(DataToSend,cnt);
}
