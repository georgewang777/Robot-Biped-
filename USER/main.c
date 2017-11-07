#include "george_system.h"

char RxBuffer[15];     //接收串口数据数组
u8 RxCount;           //Index
u8 pre_cnt_rs2=0;    //数据标志
u8 tim2_count;    	//定时器3计数标志
u8 Mk_Usart1All=0;	 //串口1接收一组数据完成标志
u8 status;           //动作标志位
u8 Pulse1,Pulse2,Pulse3,Pulse4;

int main(void)
{
	SystemInit();  //配置系统时钟为72M
	delay_init(72);	    	 //延时函数初始化	  
	NVIC_Configuration();
	uart_init(115200);
	uart2_init(115200);
	Pulse1 = 140;
	Pulse2 = 130;
	Pulse3 = 150;
	Pulse4 = 130;
  TIM2_Int_Init(50-1,7200-1);        //定时器时钟72M，分频系数7200，所以72M/7200=10Khz的计数频率，计数50次为5ms  
  TIM3_PWM_Init(2000-1,720-1);      //72M/720=100k的计数频率，自动重装载为2000，那么PWM频率为100k/2000=50HZ，周期为20ms
	Step_Motor_GPIO_Init();
	Tm1624_Init();
	Tm1624_Dispaly();
	while(1)
	{
//		for(i = 0;i<500;i++)
//		{
//			Motorcw();
//		}
//		MotorStop();
//		delay_ms(500);
//		for(i = 0;i<500;i++)
//		{
//			Motorccw();
//		}
//		MotorStop();
//		delay_ms(500);
//		if (status==1)
//		{
//			printf("yulinjun\r\n");
//			Forward();
//			status = 0;
//		}
//		if(status==2)
//		{
//			Dance();
//			delay_ms(500);
//			shake();
//			status = 0 ;
//		}
//		if(status == 3)
//		{
//			shake();
//			status = 0;
//		}
//		if(status ==4)
//		{
//		   Turn_Right();
//			status  = 0 ;
//		}
//		if(status  ==5)
//		{
//			Turn_Left();
//			status = 0;
//		}
//		if(status==6)
//		{
//			Back();
//			status  = 0;
//		}
//		if(Mk_Usart1All==1)
//		{
//			Mk_Usart1All=0;
//			RxCount=0;
//			UsartRace_Data();
//			ClearUart2();
//		}
	}
}

//定时器3中断服务函数
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET) //溢出中断
	{
		if(RxCount!=0)  //有数据接收
		{
			if(RxCount == pre_cnt_rs2)    //接收完成
			{
				tim2_count++;
				if(tim2_count>=4)
				{
					  Mk_Usart1All=1;             //交给主函数处理
					  tim2_count=0;
				}
			}
			else
			{
				tim2_count = 0;
				pre_cnt_rs2 = RxCount;
			}
		}
		
	}
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);  //清除中断标志位
}
