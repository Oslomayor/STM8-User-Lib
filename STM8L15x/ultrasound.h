/**
  ******************************************************************************
  * @file    ultrasound.h
  * @author  Denis
  * @version V0
  * @date    3-October-2018
  * @github  Oslomayor
  * @brief   ultrasound configuration
  *
  */

#ifndef __ULTRASOUND_H
#define __ULTRASOUND_H


/* Includes ------------------------------------------------------------------*/
#include "uart.h"
#include "stm8l15x.h"



/* Macro definition ----------------------------------------------------------*/
/* 操作 PMOS, 暂时不能加，改好MOS管才能用 */
#define ultrasound_on()   GPIO_WriteBit(GPIOE,GPIO_Pin_0,RESET)
#define ultrasound_off()  GPIO_WriteBit(GPIOE,GPIO_Pin_0,SET)
/* 宏定义，取平均值的次数 */
#define AVGTIMES 5

/* variable ------------------------------------------------------------------*/
extern uint16_t ultrasound_buff[4];
extern uint8_t ultrasound_flag;


/* Functions -----------------------------------------------------------------*/
extern uint16_t get_avg_distance();
extern uint16_t get_one_distance();


#endif