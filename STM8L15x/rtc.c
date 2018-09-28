/**
  ******************************************************************************
  * @file    rtc.c
  * @author  Denis
  * @version V0
  * @date    21-September-2018
  * @github  Oslomayor
  * @brief   real time clock
  *
  */
#include "rtc.h"

RTC_InitTypeDef   RTC_InitStr;
RTC_TimeTypeDef   RTC_TimeStr;
RTC_DateTypeDef   RTC_DateStr;
RTC_AlarmTypeDef  RTC_AlarmStr;

void clock_init()
{
  /* 选择内部RC高速时钟 HSI 作为系统时钟*/
  CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSI);
  /* 选择外部RC低速时钟 LSE 作为系统时钟*/
  //CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_LSE);
  /* 分频系数 1 */
  CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);  
  /* 使能 HSI */
  CLK_HSICmd(ENABLE);
  /*  使能外部LSE */
  CLK_LSEConfig(CLK_LSE_ON);
  /* 等待外部低速时钟稳定 */
  while(CLK_GetFlagStatus(CLK_FLAG_LSERDY)!=SET);
  /* 等待内部高速时钟稳定 */
  while(CLK_GetFlagStatus(CLK_FLAG_HSIRDY)!=SET);
}

void rtc_init()
{
  /* 配置RTC时钟源 */
  CLK_RTCClockConfig(CLK_RTCCLKSource_LSE,CLK_RTCCLKDiv_1);
  /* 使能RTC时钟 */
  CLK_PeripheralClockConfig(CLK_Peripheral_RTC, ENABLE);
  /* RTC参数初始化24小时制 */
  RTC_InitStr.RTC_HourFormat = RTC_HourFormat_24;
  
  /* RTC同步异步预分频参考 http://www.cnblogs.com/fly2199/p/7692138.html */
  /* 计算公式 (127+1)*(255+1)=32768 */
  RTC_InitStr.RTC_AsynchPrediv = 127;
  RTC_InitStr.RTC_SynchPrediv = 255;
  RTC_Init(&RTC_InitStr);
  
  /* 配置初始日期 */
  RTC_DateStructInit(&RTC_DateStr);
  RTC_DateStr.RTC_WeekDay = RTC_Weekday_Saturday;
  RTC_DateStr.RTC_Date = 22;
  RTC_DateStr.RTC_Month = RTC_Month_September;
  RTC_DateStr.RTC_Year = 18;
  RTC_SetDate(RTC_Format_BIN, &RTC_DateStr);
  
  /* 配置初始时间 */
  RTC_TimeStructInit(&RTC_TimeStr);
  RTC_TimeStr.RTC_Hours   = 21;
  RTC_TimeStr.RTC_Minutes = 28;
  RTC_TimeStr.RTC_Seconds = 30;
  RTC_SetTime(RTC_Format_BIN, &RTC_TimeStr);
  
  
  
  
}