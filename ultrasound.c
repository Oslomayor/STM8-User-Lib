/**
  ******************************************************************************
  * @file    ultrasound.c
  * @author  Denis
  * @version V0
  * @date    3-October-2018
  * @github  Oslomayor
  * @brief   ultrasound configuration
  *
  */

#include "ultrasound.h"


uint16_t ultrasound_buff[4];
uint8_t ultrasound_flag;


/* ȡ5�γ������������ƽ��ֵ */
uint16_t get_avg_distance()
{
  uint16_t data[5];
  uint8_t  i,j;
  uint16_t avg,temp;
  
  /* ����5�γ�������� */
  for(i=0;i<5;i++)
    data[i] = get_one_distance();
  
  /* ð�����򣬴�С�������� */
  for(i=0;i<4;i++)
    for(j=0;j<4-i;j++)
    {
      if(data[j]>data[j+1])
      {
        temp = data[j];
        data[j] = data[j+1];
        data[j+1] = temp;
      }
    }
  
  /* ȥ��������С��ȡƽ��ֵ */
  avg = (data[1]+data[2]+data[3])/3;
  
  return avg;  
}


/* ȡһ�γ���������� */
uint16_t get_one_distance()
{
  uint16_t distance;
  uint8_t i;
  
  /* UART1 ���� 0x01 ����������ģ���������� */
  //USART_SendData8(USART1,0x01);
  
  /* ������Ҫ������ʱ�����ڳ�����ģ�鵥����Ӧʱ�� */
  delay_ms(1);
  
  if(ultrasound_flag == 1)
  {
    ultrasound_flag = 0;
    /* ������ģ�鷵��4��8λ����, ��1����0xFF����4����У���*/
    if(ultrasound_buff[0] == 0xFF && ((ultrasound_buff[1]+ultrasound_buff[2])&0x00FF) == ultrasound_buff[3])
    {
      /* ������ģ�鷵��4��8λ����, ��2���Ǿ����8λ����3���Ǿ����8λ */
      /* ����8λ���ݺϳɾ��룬��λ�Ǻ��� */
      /* Ϊʲô����8λ������ԣ�������256����һ���� */
      distance = ultrasound_buff[1]*256 + ultrasound_buff[2];
      for(i=0;i<4;i++)
        ultrasound_buff[0] = 0;
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
