#include "stm32f10x_it.h"
#include "usart1.h"
#include "usart2.h"
#include "string.h"
#include "esp8266.h"
#include "Lcd_Driver.h"
extern uint8_t QZ[2];  
int time = 0;
int Close = 0;
int Close_post = 0;
int secs = 0;
unsigned char  usart2_cmd_buf[256];
unsigned int   usart2_cmd_len=0;
unsigned char  usart2_buf[256];
unsigned int   usart2_len=0;
unsigned int  rcv_cmd_start=0;
int flag = 0;
int ZhFlag = 0;
int Biao = 0;
extern char HTTP[400];
extern char HTTP_Buf[400];
extern int len;
extern uint32_t SystickTime;
extern __IO uint32_t TimeDisplay;
extern void LED_CmdCtl(void);
void USART1_IRQHandler(void)
{
	#if 0
    unsigned int data=0;
		char *hh;
    if(USART1->SR & 0x0F)
    {
        data = USART1->DR;
    }
    else if(USART1->SR & USART_FLAG_RXNE)  
    {
        data = USART1->DR;
    }
    else
    {
			;
    }
	#endif
}

/**
  * @brief  This function handles usart2 global interrupt request.
  * @param  None
  * @retval : None
  */
u8 i=0;
u8 table[4];
u8 j;
u8 k;
void USART2_IRQHandler(void)
{
    unsigned char data;
#if 1
    if(USART2->SR & 0x0F)
    {
        data = USART2->DR;
    }
    else if(USART_GetITStatus(USART2, USART_IT_RXNE))   //Receive Data Reg Full Flag
    {
    data = USART2->DR;
		table[i]=data;
        usart2_rcv_buf[usart2_rcv_len++] = data; 	
		if(usart2_rcv_len >= MAX_RCV_LEN - 1) usart2_rcv_len = 0;	
		if(data == '<')
		{
			ZhFlag=0;
			return;
		}
		if(ZhFlag == 1)
		{
			TIM_Cmd(TIM2,ENABLE);
			usart2_buf[usart2_len++] = data;
			Biao = 1;
		}
		else
		{
			TIM_Cmd(TIM2,DISABLE);
			ZhFlag = 0;
			if(data == '{')
			{
				flag = 1;
				Lcd_SetRegion(0,0,127,127);
				return;
			}
			if(flag == 1)
			{
				i++;
				if(i==4)
				{
					i=0;
					for(k=0;k<4;k++)
					{
						if(table[k]<0x40)table[k]=table[k]-0x30;
						else
						{
							table[k]=table[k]-87;
						}
					}
					LCD_WriteData_16Bit(((table[0]*16+table[1])|((table[2]*16+table[3])<<8)));
				}
				if(data == '}')
				{
					flag=0;
					Biao = 0;
					TIM_Cmd(TIM2,ENABLE);
				}
		   }
	   }	
    }
//    else
//    {
//        USART2_Clear();
//    }
	if(USART_GetITStatus(USART2, USART_IT_IDLE))
    {
    USART_ReceiveData(USART2);
		if(Biao == 1)
		{
			LED_CmdCtl();
			memset(usart2_buf,0,usart2_len);
			usart2_len=0;
			ZhFlag = 0;
		}
    } 
#endif
}

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2 , TIM_IT_Update) != RESET ) 
	{	
		time++;
		if(time >= 1000)
		{
			time=0;
			secs++;
			if(secs < 30)
			{
				ZhFlag = 1;
				USART2_Clear();
				Http_GetSta(QZ);
			}
			if(Close == 1)
			{
				Close_post++;
				if(Close_post >= 1) //¼ÌµçÆ÷
				{
					ZhFlag = 1;
					USART2_Clear();
					Http_GetClose(QZ);
					Close_post = 0;
					Close = 0;
				}
			}
		}
		
		TIM_ClearITPendingBit(TIM2 , TIM_FLAG_Update);  		 
	}	
}




