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
  /* ѡ���ڲ�RC����ʱ�� HSI ��Ϊϵͳʱ��*/
  CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSI);
  /* ѡ���ⲿRC����ʱ�� LSE ��Ϊϵͳʱ��*/
  //CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_LSE);
  /* ��Ƶϵ�� 1 */
  CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);  
  /* ʹ�� HSI */
  CLK_HSICmd(ENABLE);
  /*  ʹ���ⲿLSE */
  CLK_LSEConfig(CLK_LSE_ON);
  /* �ȴ��ⲿ����ʱ���ȶ� */
  while(CLK_GetFlagStatus(CLK_FLAG_LSERDY)!=SET);
  /* �ȴ��ڲ�����ʱ���ȶ� */
  while(CLK_GetFlagStatus(CLK_FLAG_HSIRDY)!=SET);
}

void rtc_init()
{
  /* ����RTCʱ��Դ */
  CLK_RTCClockConfig(CLK_RTCCLKSource_LSE,CLK_RTCCLKDiv_1);
  /* ʹ��RTCʱ�� */
  CLK_PeripheralClockConfig(CLK_Peripheral_RTC, ENABLE);
  /* RTC������ʼ��24Сʱ�� */
  RTC_InitStr.RTC_HourFormat = RTC_HourFormat_24;
  
  /* RTCͬ���첽Ԥ��Ƶ�ο� http://www.cnblogs.com/fly2199/p/7692138.html */
  /* ���㹫ʽ (127+1)*(255+1)=32768 */
  RTC_InitStr.RTC_AsynchPrediv = 127;
  RTC_InitStr.RTC_SynchPrediv = 255;
  RTC_Init(&RTC_InitStr);
  
  /* ���ó�ʼ���� */
  RTC_DateStructInit(&RTC_DateStr);
  RTC_DateStr.RTC_WeekDay = RTC_Weekday_Saturday;
  RTC_DateStr.RTC_Date = 22;
  RTC_DateStr.RTC_Month = RTC_Month_September;
  RTC_DateStr.RTC_Year = 18;
  RTC_SetDate(RTC_Format_BIN, &RTC_DateStr);
  
  /* ���ó�ʼʱ�� */
  RTC_TimeStructInit(&RTC_TimeStr);
  RTC_TimeStr.RTC_Hours   = 21;
  RTC_TimeStr.RTC_Minutes = 28;
  RTC_TimeStr.RTC_Seconds = 30;
  RTC_SetTime(RTC_Format_BIN, &RTC_TimeStr);
  
  
  
  
}