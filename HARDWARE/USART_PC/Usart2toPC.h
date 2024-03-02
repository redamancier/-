#ifndef __USART5TOPC_H
#define __USART5TOPC_H

#include "DronePara.h"
#include "Task.h"
#include <os.h>
#include <string.h>

extern _Data_Rx Flow_rx;        //一个全局变量，储存传输到电脑的数据  //此数据不同于遥控器的数据，用于传输视觉数据————from lzh
extern _MV_Rx mv2_Rx;
void UsartToMv2_init(u32 Bound);
void Usart2_tx(uint8_t *data,uint16_t size);   //将数据通过通道5由DMA传输出去

#endif

