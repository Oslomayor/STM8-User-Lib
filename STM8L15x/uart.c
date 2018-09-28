/**
  ******************************************************************************
  * @file    uart.c
  * @author  Denis
  * @version V0
  * @date    21-September-2018
  * @github  Oslomayor
  * @brief   uart configuration
  *
  */
#include "uart.h"

/* variable ------------------------------------------------------------------*/



/* Functions -----------------------------------------------------------------*/

/* uart�жϴ�����λ�� stm8l15x_it.c , �ж�������28 */    
    

void uart_init()
{
  /*  USART1 ʱ�� */
  CLK_PeripheralClockConfig(CLK_Peripheral_USART1,ENABLE);
  
  /* ���� UART �� GPIO */
  GPIO_ExternalPullUpConfig(GPIOA,GPIO_Pin_2|GPIO_Pin_3,ENABLE);
  
  /* ��ӳ�� UART ������ PA2 -TX  PA3-RX ,Ĭ��Ϊ PC2 -RX  PC3-TX */
  // SYSCFG_REMAPPinConfig(REMAP_Pin_USART1TxRxPortA,ENABLE);
  
  /* ��ʼ������ */
  USART_Init(USART1,9600,USART_WordLength_8b,USART_StopBits_1,USART_Parity_No,USART_Mode_Rx|USART_Mode_Tx);
  
  /* ʹ�ܴ��ڽ����ж�,�ж�������Ϊ28 */
  //USART_ITConfig (USART1,USART_IT_OR,ENABLE);
  
  /* ʹ���ж��ܿ��� */
  //enableInterrupts();
  
  /* ʹ�� UART */
  USART_Cmd(USART1,ENABLE);
  
  /* ������ݼĴ����ͷ�����ɱ�־λ */
  //USART_ClearFlag(USART1,USART_FLAG_TXE|USART_FLAG_TC);
}

/* �ض��� putchar, ʹ printf �򴮿ڴ�ӡ */
int putchar(int c)
{ 
  /* �ض���������1 */
  USART_SendData8(USART1,c);
  while(RESET==USART_GetFlagStatus(USART1,USART_FLAG_TC));
  USART_ClearFlag(USART1,USART_FLAG_TC);
  return(c);
}

/* ����Ȥ�о�һ���ض��� getchar */
/* �� scanf �� printf ���ӣ���������������⣬��ʱ���ܲ���ϵͳ */

