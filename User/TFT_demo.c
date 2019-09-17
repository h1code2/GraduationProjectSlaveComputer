#include "stm32f10x.h"
#include "Lcd_Driver.h"
#include "delay.h"
#include "Picture.h"
#include "TFT_demo.h"
unsigned char Num[10]={0,1,2,3,4,5,6,7,8,9};
//取模方式 水平扫描 从左到右 低位在前
void showimage(const unsigned char *p) //显示40*40 QQ图片
{
  	int i,j,k; 
	unsigned char picH,picL;
	Lcd_Clear(WHITE); //清屏  
	
	for(k=0;k<3;k++)
	{
	   	for(j=0;j<3;j++)
		{	
			Lcd_SetRegion(40*j,40*k,40*j+39,40*k+39);		//坐标设置
		    for(i=0;i<40*40;i++)
			 {	
			 	picL=*(p+i*2);	//数据低位在前
				picH=*(p+i*2+1);				
				LCD_WriteData_16Bit(picH<<8|picL);  						
			 }	
		 }
	}		
}


//取模方式 水平扫描 从左到右 低位在前
void Fullscreen_showimage(const unsigned char *p) //显示128*128 图片
{
  	int i; 
	unsigned char picH,picL;
	
	Lcd_Clear(WHITE); //清屏  
	
	
			Lcd_SetRegion(0,0,127,127);		//坐标设置:扫描起点到终点0到127，刚好128个点
		    for(i=0;i<128*128;i++)
				 {	
					picL=*(p+i*2);	//数据低位在前
					picH=*(p+i*2+1);				
					LCD_WriteData_16Bit(picH<<8|picL); 
//					LCD_WriteData_16Bit(0xffaa); 					 
				 }	
		
}


void Test_Demo(void)
{
	Lcd_Init();
	Lcd_Clear(WHITE); //清屏 
	Fullscreen_showimage((gImage_cJSON));//图片显示示例
}
