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

/* uart中断处理函数位于 stm8l15x_it.c , 中断向量号28 */    
    

void uart_init()
{
  /*  USART1 时钟 */
  CLK_PeripheralClockConfig(CLK_Peripheral_USART1,ENABLE);
  
  /* 上拉 UART 的 GPIO */
  GPIO_ExternalPullUpConfig(GPIOA,GPIO_Pin_2|GPIO_Pin_3,ENABLE);
  
  /* 重映射 UART 引脚至 PA2 -TX  PA3-RX ,默认为 PC2 -RX  PC3-TX */
  // SYSCFG_REMAPPinConfig(REMAP_Pin_USART1TxRxPortA,ENABLE);
  
  /* 初始化参数 */
  USART_Init(USART1,9600,USART_WordLength_8b,USART_StopBits_1,USART_Parity_No,USART_Mode_Rx|USART_Mode_Tx);
  
  /* 使能串口接收中断,中断向量号为28 */
  //USART_ITConfig (USART1,USART_IT_OR,ENABLE);
  
  /* 使能中断总开关 */
  //enableInterrupts();
  
  /* 使能 UART */
  USART_Cmd(USART1,ENABLE);
  
  /* 清除数据寄存器和发送完成标志位 */
  //USART_ClearFlag(USART1,USART_FLAG_TXE|USART_FLAG_TC);
}

/* 重定义 putchar, 使 printf 向串口打印 */
int putchar(int c)
{ 
  /* 重定向至串口1 */
  USART_SendData8(USART1,c);
  while(RESET==USART_GetFlagStatus(USART1,USART_FLAG_TC));
  USART_ClearFlag(USART1,USART_FLAG_TC);
  return(c);
}

/* 有兴趣研究一下重定义 getchar */
/* 跑 scanf 比 printf 复杂，会造成阻塞的问题，暂时不跑操作系统 */

