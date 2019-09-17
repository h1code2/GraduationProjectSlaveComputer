#include "led.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
extern unsigned char  usart2_buf[256];
extern int Close;
//�������LED/�̵���
void LED_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Pin =GPIO_Pin_8|GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_SetBits(GPIOA,GPIO_Pin_8|GPIO_Pin_7);
}


//����״̬
void LED_CmdCtl(void)
{
	if((NULL != strstr((const char *)usart2_buf, "{1}")))
	{ 
		GPIOA->ODR&=~(1<<8);//A8����:�̵�������
		GPIOA->ODR&=~(1<<7);//A7����:��������
		Close = 1;
		
	}
	if((NULL != strstr((const char *)usart2_buf, "{0}"))) 
	{
		GPIOA->ODR|=1<<8;
		GPIOA->ODR|=1<<7;
	}

}