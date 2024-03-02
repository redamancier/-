
#include "mpu_exti.h"
#include "loop.h"

extern Mpu_DataInitTypedef Mpu_Data;

static void NVIC_Configuration(void)
 {
 NVIC_InitTypeDef NVIC_InitStructure;

 /* 配置 NVIC 为优先级组 1 */

 /* 配置中断源：按键 1 */
 NVIC_InitStructure.NVIC_IRQChannel = MPU_INT_IRQ;
 /* 配置抢占优先级：1 */
 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
 /* 配置子优先级：1 */
 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
 /* 使能中断通道 */
 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
 NVIC_Init(&NVIC_InitStructure);
 }

 void MPU_Int_Config(void)
 {
	 GPIO_InitTypeDef GPIO_InitStructure;
 EXTI_InitTypeDef EXTI_InitStructure;

 /* 开启按键 GPIO 口的时钟 */
 RCC_AHB1PeriphClockCmd(MPU_INT_CLK ,ENABLE);

 /* 使能 SYSCFG 时钟 ，使用 GPIO 外部中断时必须使能 SYSCFG 时钟 */
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

 /* 配置 NVIC */
 NVIC_Configuration();

 /* 选择按键 1 的引脚 */
 GPIO_InitStructure.GPIO_Pin = MPU_INT_PIN;
 /* 设置引脚为输入模式 */
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
 /* 设置引脚不上拉也不下拉 */
 GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
 /* 使用上面的结构体初始化按键 */
 GPIO_Init(MPU_INT_PORT, &GPIO_InitStructure);

 /* 连接 EXTI 中断源 到 key1 引脚 */
 SYSCFG_EXTILineConfig(MPU_INT_PORTSOURCE,
 MPU_INT_PINSOURCE);

 /* 选择 EXTI 中断源 */
 EXTI_InitStructure.EXTI_Line = MPU_INT_LINE;
 /* 中断模式 */
 EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
 /* 下降沿触发 */
 EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
 /* 使能中断/事件线 */
 EXTI_InitStructure.EXTI_LineCmd = ENABLE;
 EXTI_Init(&EXTI_InitStructure);
 }
 
 
 void MPUINT_ISR(void)
 {
	 if(EXTI_GetITStatus(MPU_INT_LINE) != RESET)
	 {
		 EXTI_ClearITPendingBit(MPU_INT_LINE);
	 }
 }
 
