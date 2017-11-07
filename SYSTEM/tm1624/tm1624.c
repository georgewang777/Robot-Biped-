#include "tm1624.h"
#include "delay.h"

#define DIO_H   GPIO_SetBits(GPIOB,GPIO_Pin_12)
#define DIO_L    GPIO_ResetBits(GPIOB,GPIO_Pin_12)
#define CLK_H   GPIO_SetBits(GPIOB,GPIO_Pin_13)
#define CLK_L    GPIO_ResetBits(GPIOB,GPIO_Pin_13)
#define STB_H   GPIO_SetBits(GPIOB,GPIO_Pin_14)
#define STB_L    GPIO_ResetBits(GPIOB,GPIO_Pin_14)

void TM1624_Write(u8 wr_data)
{
    u8 i;
    STB_L;                     
    
    for(i=0;i<8;i++)
    {
        CLK_L;
        if(wr_data&0x01)
        {
           DIO_H;
        } else
        {
            DIO_L;
        }
        CLK_H;
        wr_data>>=1;
    }
		CLK_L;
		DIO_L;
}
 //����������        
void Write_Com(u8 cmd)                  
{
    STB_L;
    TM1624_Write(cmd);
    STB_H;
    delay_ms(2);
}

void Clear_TM1624(void)
{
   u8 i;
   STB_L;
   TM1624_Write(0xc0);              
   for(i=0;i<16;i++)
   TM1624_Write(0x00);                
   STB_H;
}

void Tm1624_Init(void)
{
	CLK_H;                              
	STB_H;                              
	DIO_H;        
  Write_Com(0x89);    //����   10001111 ������������14/16 ��ʾ�� 	
	//Write_Com(0x03);  //������ʾģʽ��7λ11��        
	Write_Com(0x40);    //��������������õ�ַ�Զ���һģʽ
	Clear_TM1624();    
	Write_Com(0x44);    //�̶���ַ
}

void Tm1624_Dispaly(void)
{
	STB_L;
	TM1624_Write(0xC0);
	TM1624_Write(0xff);
	STB_H;
	delay_ms(1000);
	STB_L;
	TM1624_Write(0xC2);
	TM1624_Write(0xff);
	STB_H;
	delay_ms(1000);
	STB_L;
	TM1624_Write(0xC4);
	TM1624_Write(0xff);
}