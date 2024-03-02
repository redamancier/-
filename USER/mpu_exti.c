
#include "mpu_exti.h"
#include "loop.h"

extern Mpu_DataInitTypedef Mpu_Data;

static void NVIC_Configuration(void)
 {
 NVIC_InitTypeDef NVIC_InitStructure;

 /* ���� NVIC Ϊ���ȼ��� 1 */

 /* �����ж�Դ������ 1 */
 NVIC_InitStructure.NVIC_IRQChannel = MPU_INT_IRQ;
 /* ������ռ���ȼ���1 */
 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
 /* ���������ȼ���1 */
 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
 /* ʹ���ж�ͨ�� */
 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
 NVIC_Init(&NVIC_InitStructure);
 }

 void MPU_Int_Config(void)
 {
	 GPIO_InitTypeDef GPIO_InitStructure;
 EXTI_InitTypeDef EXTI_InitStructure;

 /* �������� GPIO �ڵ�ʱ�� */
 RCC_AHB1PeriphClockCmd(MPU_INT_CLK ,ENABLE);

 /* ʹ�� SYSCFG ʱ�� ��ʹ�� GPIO �ⲿ�ж�ʱ����ʹ�� SYSCFG ʱ�� */
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

 /* ���� NVIC */
 NVIC_Configuration();

 /* ѡ�񰴼� 1 ������ */
 GPIO_InitStructure.GPIO_Pin = MPU_INT_PIN;
 /* ��������Ϊ����ģʽ */
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
 /* �������Ų�����Ҳ������ */
 GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
 /* ʹ������Ľṹ���ʼ������ */
 GPIO_Init(MPU_INT_PORT, &GPIO_InitStructure);

 /* ���� EXTI �ж�Դ �� key1 ���� */
 SYSCFG_EXTILineConfig(MPU_INT_PORTSOURCE,
 MPU_INT_PINSOURCE);

 /* ѡ�� EXTI �ж�Դ */
 EXTI_InitStructure.EXTI_Line = MPU_INT_LINE;
 /* �ж�ģʽ */
 EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
 /* �½��ش��� */
 EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
 /* ʹ���ж�/�¼��� */
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
 
