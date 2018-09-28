/**
  ******************************************************************************
  * @file    uart.h
  * @author  Denis
  * @version V0
  * @date    21-September-2018
  * @github  Oslomayor
  * @brief   uart configuration
  *
  */


#ifndef __UART_H
#define __UART_H

/* Includes ------------------------------------------------------------------*/
#include "stm8l15x.h"
#include "stm8l15x_usart.h"
#include "stdio.h"

/* variable ------------------------------------------------------------------*/
extern unsigned char recvFlag;


/* Functions -----------------------------------------------------------------*/
extern void uart_init();
/* uart中断处理函数位于 stm8l15x_it.c , 中断向量28*/


#endif

