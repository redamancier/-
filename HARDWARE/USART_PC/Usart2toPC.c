
#include "Usart2toPC.h"

//串口2是给头部摄像头进行传输数据的，因为一只openmv我怕不能处理另外一只openmv的数据————from lzh

unsigned char mv2_Tx_Buf_Uart2[15];
unsigned char mv2_Rx_Buf_Uart2[15];

int Flag_Tx_Uart2_Busy = 0;


void UsartToMv2_init(u32 Bound)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    DMA_InitTypeDef DMA_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);

    //DMA发送中断设置
    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream6_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	//DMA串口发通道配置
	DMA_DeInit(DMA1_Stream6);
	DMA_InitStructure.DMA_Channel = DMA_Channel_4;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART2->DR);
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)mv2_Tx_Buf_Uart2;
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
	DMA_InitStructure.DMA_BufferSize = MV_TX_LEN;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	
	DMA_Init(DMA1_Stream6, &DMA_InitStructure);
	DMA_ITConfig(DMA1_Stream6, DMA_IT_TC, ENABLE);
	//DMA串口收配置
	DMA_DeInit(DMA1_Stream5);
	DMA_InitStructure.DMA_Channel = DMA_Channel_4;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART2->DR);
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)mv2_Rx_Buf_Uart2;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
	DMA_InitStructure.DMA_BufferSize = MV_RX_LEN;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Init(DMA1_Stream5, &DMA_InitStructure);
	DMA_Cmd(DMA1_Stream5, ENABLE);
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource6, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_USART2);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6; // GPIOD5与GPIOD6
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;           //复用功能
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;      //速度50MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;         //推挽复用输出
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;           //上拉
    GPIO_Init(GPIOD, &GPIO_InitStructure);                 //初始化PD5，PD6
	
	USART_InitStructure.USART_BaudRate = Bound;
	USART_InitStructure.USART_WordLength =
        USART_WordLength_8b; //字长为8位数据格式
    USART_InitStructure.USART_StopBits = USART_StopBits_1; //一个停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;    //无奇偶校验位
    USART_InitStructure.USART_HardwareFlowControl =
        USART_HardwareFlowControl_None; //无硬件数据流控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //收发模式
    USART_Init(USART2, &USART_InitStructure); //初始化串口2
	// 中断配置
    USART_ITConfig(USART2, USART_IT_TC, DISABLE);
    USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);
    USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);
	// USART2 NVIC 配置
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn; //串口1中断通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5; //抢占优先级5
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;        //子优先级1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           // IRQ通道使能
    NVIC_Init(&NVIC_InitStructure); //根据指定的参数初始化NVIC寄存器、
	
	USART_DMACmd(USART2, USART_DMAReq_Tx, ENABLE);
	USART_DMACmd(USART2, USART_DMAReq_Rx, ENABLE);
	
	USART_ITConfig(USART2, USART_IT_TC, DISABLE);
    USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);
    USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
    USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);

    //启动串口
    USART_Cmd(USART2, ENABLE);
	
	
}

void Usart2_tx(uint8_t *data, uint16_t size) {
    while (Flag_Tx_Uart2_Busy);
    Flag_Tx_Uart2_Busy = 1;
    memcpy(mv2_Tx_Buf_Uart2, data, size);
    DMA_SetCurrDataCounter(DMA1_Stream6, size);
    DMA_Cmd(DMA1_Stream6, ENABLE);
}

uint8_t inf_Uart2_deal_irq_tx_end(void) {
    if (USART_GetITStatus(USART2, USART_IT_TC) != RESET) {
        USART_ITConfig(USART2, USART_IT_TC, DISABLE);
        Flag_Tx_Uart2_Busy = 0;

        return 1;
    }
    return 0;
}

uint8_t inf_Uart2_deal_irq_rx_end(uint8_t *buf) {
    uint16_t len = 0;

    if (USART_GetITStatus(USART2, USART_IT_IDLE) != RESET) {
        USART2->SR;
        USART2->DR;
        DMA_Cmd(DMA1_Stream5, DISABLE);
        DMA_ClearFlag(DMA1_Stream5, DMA_FLAG_TCIF5);
        len = MV_RX_LEN - DMA_GetCurrDataCounter(DMA1_Stream5);

        /***** test *****/
        // memcpy(buf, Rx_Buf_Uart6, len);//change
        memcpy(buf, mv2_Rx_Buf_Uart2, len);
        /***** test *****/
        
        DMA_SetCurrDataCounter(DMA1_Stream5, MV_RX_LEN);
        DMA_Cmd(DMA1_Stream5, ENABLE);
        return len;
    }
    return 0;
}

void DMA1_Stream6_IRQHandler(void) {
    //进入中断调用ucos系统函数
    OSIntEnter();
    if (DMA_GetITStatus(DMA1_Stream6, DMA_IT_TCIF6) != RESET) {
        //清除标志位
        DMA_ClearFlag(DMA1_Stream6, DMA_FLAG_TCIF6);
        //关闭DMA
        DMA_Cmd(DMA1_Stream6, DISABLE);
        USART_ITConfig(USART2, USART_IT_TC, ENABLE);
    }
    OSIntExit();
}

_MV_Rx mv2_Rx;

void USART2_IRQHandler(void) {
    OS_ERR err;
    OSIntEnter();
    inf_Uart2_deal_irq_tx_end();
    mv_Rx.len = inf_Uart2_deal_irq_rx_end(mv2_Rx.buf);
    if (mv2_Rx.len == 10) {
        OSSemPost(&VIO_proc, OS_OPT_POST_1, &err);
    }
    OSIntExit();
}


