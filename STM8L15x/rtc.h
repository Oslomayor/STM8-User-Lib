/**
  ******************************************************************************
  * @file    rtc.h
  * @author  Denis
  * @version V0
  * @date    21-September-2018
  * @github  Oslomayor
  * @brief   real time clock
  *
  */


#ifndef __RTC_H
#define __RTC_H


/* Includes ------------------------------------------------------------------*/
#include "stm8l15x.h"
#include "stm8l15x_clk.h"
#include "stm8l15x_rtc.h"

/* Time ----------------------------------------------------------------------*/
extern RTC_InitTypeDef   RTC_InitStr;
extern RTC_TimeTypeDef   RTC_TimeStr;
extern RTC_DateTypeDef   RTC_DateStr;
extern RTC_AlarmTypeDef  RTC_AlarmStr;


/* Functions -----------------------------------------------------------------*/
extern void clock_init();
extern void rtc_init();


#endif

