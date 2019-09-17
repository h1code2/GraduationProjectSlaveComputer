#include "stm32f10x.h"
#include "delay.h"
#include "TFT_demo.h"
#include "Lcd_Driver.h"
#include "esp8266.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "usart1.h"
#include "usart2.h"
#include "utils.h"
#include "esp8266.h"
#include "Picture.h"
#include "time.h"
#include "misc.h"
#include "led.h"
#include "key.h"


uint8_t QZ[2]="AD";  // ÃÅËøid
char HTTP_Buf[400];
char HTTP[400];
char HTTP_Close[400];

int len;
extern int flag;
extern int time;
extern int secs;
int min=0;
int kk = 0;
extern int ZhFlag;
uint32_t Http_GetPkt(uint8_t *pkt);
uint32_t Http_GetSta(char *pkt);
uint32_t Http_GetClose(char *pkt);
int main(void)
{
//  SystemInit();	//System init.  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
  delay_init(72);//Delay init.
	Test_Demo();
	Key_Init();
	LED_Config();
	USART1_Config();       
  USART2_Config();
	LED_CmdCtl();
  ESP8266_Init(); 
	printf("ESP8266 init over\r\n");
	Time2_Init(); 	
	Http_GetPkt(QZ);
  while(1)
  {  
		if(secs >= 30)
		{
			secs = 0;
			TIM_Cmd(TIM2,DISABLE);
			USART2_Clear();
			Http_GetPkt(QZ);
			delay_ms(1000);
			USART2_Clear();
			TIM_Cmd(TIM2,ENABLE);
		}
		else
		{
			if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1) == 0)
			{
				delay_ms(50);
				while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1) == 0);
				ZhFlag = 1;
				USART2_Clear();
				Http_GetClose(QZ); 
			}
		}


}
}
