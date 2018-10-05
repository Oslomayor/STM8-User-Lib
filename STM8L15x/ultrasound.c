/**
  ******************************************************************************
  * @file    ultrasound.c
  * @author  Denis
  * @version V0
  * @date    5-October-2018
  * @github  Oslomayor
  * @brief   ultrasound configuration
  * @ultrasound module 
  *  https://item.taobao.com/item.htm?spm=a1z0d.6639537.1997196601.89.5b947484kZHk64&id=556599902719
  */

#include "ultrasound.h"


uint16_t ultrasound_buff[4];
uint8_t ultrasound_flag;


/* 取多次超声波测距结果的平均值 */
uint16_t get_avg_distance()
{
  uint16_t data[AVGTIMES];
  uint8_t  i,j;
  uint16_t avg = 0,temp;
  uint8_t timeout;
  
  /* 启动 AVGTIMES 次超声波测距，宏定义在 ultrasound.h 中 */
  for(i=0;i<AVGTIMES;i++)
  {
    timeout = 0;
    /* 进行一次超声波测距 */
    data[i] = get_one_distance();
    /* 若果测试结果为空，重新测量，超出10次为空跳过 */
    while(data[i] == 0 && timeout < 10) 
    {
      data[i] = get_one_distance();
      timeout++;
    }
    
    /* 留出超声波模块反应时间，延时小于500ms不稳定 */
    delay_ms(800);
  }
  
  /* 冒泡排序，从小到大排列 */
  for(i=0;i<AVGTIMES-1;i++)
    for(j=0;j<AVGTIMES-1-i;j++)
    {
      if(data[j]>data[j+1])
      {
        temp = data[j];
        data[j] = data[j+1];
        data[j+1] = temp;
      }
    }
  
  /* 去掉最大和最小，取平均值 */
  for(i=1;i<AVGTIMES-1;i++)
    avg = avg + data[i];
  
  avg = avg/(AVGTIMES-2);
  return avg;  
}


/* 返回一次超声波测距结果 */
uint16_t get_one_distance()
{
  uint16_t distance = 0;
  uint8_t i;
  
  /* UART1 发送 0x01 触发超声波模块启动测量 */
  USART_SendData8(USART1,0x01);
  
  /* 这里需要调节延时，大于超声波模块单次响应时间，延时小于75ms不稳定 */
  delay_ms(100);
  
  if(ultrasound_flag == 1)
  {
    ultrasound_flag = 0;
    /* 超声波模块返回4个8位数据, 第1个是0xFF，第4个是校验和*/
    if(ultrasound_buff[0] == 0xFF && ((ultrasound_buff[1]+ultrasound_buff[2])&0x00FF) == ultrasound_buff[3])
    {
      /* 超声波模块返回4个8位数据, 第2个是距离高8位，第3个是距离低8位 */
      /* 两个8位数据合成距离，单位是毫米 */
      distance = ultrasound_buff[1]*256 + ultrasound_buff[2];
      /*完成一次测量对缓存区清零*/
      for(i=0;i<4;i++)
        ultrasound_buff[i] = 0x00;
    }
  }
  else 
      /* 使用超声波模块的盲区为 110mm , 结果不可能是 0, 出现 0 代表测量出错*/
      distance = 0;
  
  /* 有个小 bug , 为什么 mian 收到返回结果存在 -1 的情况 */
  return distance;
}

/* 超声波模块接收中断 */
INTERRUPT_HANDLER(USART1_RX_TIM5_CC_IRQHandler,28)
{
    
  static uint8_t i = 0;
  
  if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)
  {
    ultrasound_buff[i]=(USART_ReceiveData8(USART1));
    i++;
    if(i >= 4)
    {
      i = 0;
      ultrasound_flag = 1;
      USART_ClearFlag(USART1, USART_IT_RXNE);
    }
  }
  
  
}
