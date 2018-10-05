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


/* ȡ��γ������������ƽ��ֵ */
uint16_t get_avg_distance()
{
  uint16_t data[AVGTIMES];
  uint8_t  i,j;
  uint16_t avg = 0,temp;
  uint8_t timeout;
  
  /* ���� AVGTIMES �γ�������࣬�궨���� ultrasound.h �� */
  for(i=0;i<AVGTIMES;i++)
  {
    timeout = 0;
    /* ����һ�γ�������� */
    data[i] = get_one_distance();
    /* �������Խ��Ϊ�գ����²���������10��Ϊ������ */
    while(data[i] == 0 && timeout < 10) 
    {
      data[i] = get_one_distance();
      timeout++;
    }
    
    /* ����������ģ�鷴Ӧʱ�䣬��ʱС��500ms���ȶ� */
    delay_ms(800);
  }
  
  /* ð�����򣬴�С�������� */
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
  
  /* ȥ��������С��ȡƽ��ֵ */
  for(i=1;i<AVGTIMES-1;i++)
    avg = avg + data[i];
  
  avg = avg/(AVGTIMES-2);
  return avg;  
}


/* ����һ�γ���������� */
uint16_t get_one_distance()
{
  uint16_t distance = 0;
  uint8_t i;
  
  /* UART1 ���� 0x01 ����������ģ���������� */
  USART_SendData8(USART1,0x01);
  
  /* ������Ҫ������ʱ�����ڳ�����ģ�鵥����Ӧʱ�䣬��ʱС��75ms���ȶ� */
  delay_ms(100);
  
  if(ultrasound_flag == 1)
  {
    ultrasound_flag = 0;
    /* ������ģ�鷵��4��8λ����, ��1����0xFF����4����У���*/
    if(ultrasound_buff[0] == 0xFF && ((ultrasound_buff[1]+ultrasound_buff[2])&0x00FF) == ultrasound_buff[3])
    {
      /* ������ģ�鷵��4��8λ����, ��2���Ǿ����8λ����3���Ǿ����8λ */
      /* ����8λ���ݺϳɾ��룬��λ�Ǻ��� */
      distance = ultrasound_buff[1]*256 + ultrasound_buff[2];
      /*���һ�β����Ի���������*/
      for(i=0;i<4;i++)
        ultrasound_buff[i] = 0x00;
    }
  }
  else 
      /* ʹ�ó�����ģ���ä��Ϊ 110mm , ����������� 0, ���� 0 �����������*/
      distance = 0;
  
  /* �и�С bug , Ϊʲô mian �յ����ؽ������ -1 ����� */
  return distance;
}

/* ������ģ������ж� */
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
