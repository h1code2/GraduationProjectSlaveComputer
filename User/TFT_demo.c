#include "stm32f10x.h"
#include "Lcd_Driver.h"
#include "delay.h"
#include "Picture.h"
#include "TFT_demo.h"
unsigned char Num[10]={0,1,2,3,4,5,6,7,8,9};
//ȡģ��ʽ ˮƽɨ�� ������ ��λ��ǰ
void showimage(const unsigned char *p) //��ʾ40*40 QQͼƬ
{
  	int i,j,k; 
	unsigned char picH,picL;
	Lcd_Clear(WHITE); //����  
	
	for(k=0;k<3;k++)
	{
	   	for(j=0;j<3;j++)
		{	
			Lcd_SetRegion(40*j,40*k,40*j+39,40*k+39);		//��������
		    for(i=0;i<40*40;i++)
			 {	
			 	picL=*(p+i*2);	//���ݵ�λ��ǰ
				picH=*(p+i*2+1);				
				LCD_WriteData_16Bit(picH<<8|picL);  						
			 }	
		 }
	}		
}


//ȡģ��ʽ ˮƽɨ�� ������ ��λ��ǰ
void Fullscreen_showimage(const unsigned char *p) //��ʾ128*128 ͼƬ
{
  	int i; 
	unsigned char picH,picL;
	
	Lcd_Clear(WHITE); //����  
	
	
			Lcd_SetRegion(0,0,127,127);		//��������:ɨ����㵽�յ�0��127���պ�128����
		    for(i=0;i<128*128;i++)
				 {	
					picL=*(p+i*2);	//���ݵ�λ��ǰ
					picH=*(p+i*2+1);				
					LCD_WriteData_16Bit(picH<<8|picL); 
//					LCD_WriteData_16Bit(0xffaa); 					 
				 }	
		
}


void Test_Demo(void)
{
	Lcd_Init();
	Lcd_Clear(WHITE); //���� 
	Fullscreen_showimage((gImage_cJSON));//ͼƬ��ʾʾ��
}
