#ifndef __USART5TOFLOW_H
#define __USART5TOFLOW_H

#include "DronePara.h"
#include "Task.h"
#include <os.h>
#include <string.h>

extern _Data_Rx Flow_rx;        //一个全局变量，储存光流的数据

void Usart5toFlow_Init(u32 Bound);
void Usart5_tx(uint8_t *data,uint16_t size);   //将数据通过通道5由DMA传输出去

#endif

