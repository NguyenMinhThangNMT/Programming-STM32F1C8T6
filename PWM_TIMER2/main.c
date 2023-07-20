#include  <stdarg.h>//xu ly so
#include  <string.h>//xu ly kieu chuoi ky tu
#include  <ctype.h>//bao gom cac hoam dung de phan lop cac ky tu boi cac kieu hay dung chuyen doi viet hoa va viet thuong
#include  <stdlib.h>//cac phep toan
#include  <stdio.h>//Cung cap cac dinh dang IN/OUT trong C
//------------------------GOI THU VIEN DUNG CHO PROJECT DANG VIET---------------//
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
//------------------------GOI THU VIEN HAM NGUOI DUNG VIET------------------------//
#include "delay.h"
#include "gpio.h"


//---------------------------KHAI BAO CAC BIEN VA HANG----------------------------------//
//---------------------------KHAI BAO CAC HAM----------------------------------//
//---------------------------HAM MAIN------------------------------------------//
#define LED_PORT     GPIOC
#define LED1         GPIO_Pin_13
#define LED2         GPIO_Pin_14

#define I2C_PORT     GPIOB
#define SS          GPIO_Pin_12
#define SCK         GPIO_Pin_13
#define MISO        GPIO_Pin_14
#define MOSI        GPIO_Pin_15

#define PWM_PORT     GPIOA
#define CH1         GPIO_Pin_0
#define CH2         GPIO_Pin_1
#define CH3         GPIO_Pin_2
#define CH4         GPIO_Pin_3

#define LEDCLock    RCC_APB2Periph_GPIOC
#define BTCLock     RCC_APB2Periph_GPIOB
#define PWMCLock    RCC_APB2Periph_GPIOA

// For store tick counts in us


void GPIO_cofig()
{
	RCC_APB2PeriphClockCmd(LEDCLock|BTCLock,ENABLE);
  
	GPIO_InitTypeDef Structure;
	Structure.GPIO_Mode=GPIO_Mode_Out_OD;
	Structure.GPIO_Pin=LED1|LED2;
	Structure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(LED_PORT,&Structure);
	//Cau hinh chan CS
	Structure.GPIO_Mode=GPIO_Mode_Out_PP;
	Structure.GPIO_Pin=SS;
	Structure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(I2C_PORT,&Structure);
	//Cau hinh chan SCK
	Structure.GPIO_Mode=GPIO_Mode_AF_PP;
	Structure.GPIO_Pin=SCK;
	Structure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(I2C_PORT,&Structure);
	//Cau hinh chan MISO
	Structure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	Structure.GPIO_Pin=MISO;
	Structure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(I2C_PORT,&Structure);
	//Cau hinh chan MOSI
	Structure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	Structure.GPIO_Pin=MOSI;
	Structure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(I2C_PORT,&Structure);
	//Cau hinh SPI
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2,ENABLE);
	SPI_InitTypeDef Spi2Init;
	Spi2Init.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_32;
	Spi2Init.SPI_CPHA=SPI_CPHA_1Edge;
	Spi2Init.SPI_CPOL=SPI_CPOL_Low;
	Spi2Init.SPI_DataSize=SPI_DataSize_8b;
	Spi2Init.SPI_Direction=SPI_Direction_2Lines_FullDuplex;
	Spi2Init.SPI_FirstBit=SPI_FirstBit_MSB;
	Spi2Init.SPI_Mode=SPI_Mode_Master;
	Spi2Init.SPI_NSS=SPI_NSS_Soft;
	
	SPI_Init(SPI2,&Spi2Init);
	SPI_Cmd(SPI2,ENABLE);
}
void TIMER2_Configuration(void);
void TIMER2_Configuration(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
	NVIC_InitTypeDef NVIC_Struct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	TIM_TimeBaseStruct.TIM_Prescaler=19;
	TIM_TimeBaseStruct.TIM_Period=19;
	TIM_TimeBaseStruct.TIM_CounterMode=0;
	TIM_TimeBaseStruct.TIM_ClockDivision=TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStruct);
	
	//bat interupt
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM2,ENABLE);
	
	//thiet lap nvic ngat
	NVIC_Struct.NVIC_IRQChannel=TIM2_IRQn;
	NVIC_Struct.NVIC_IRQChannelPreemptionPriority=0x00;
	NVIC_Struct.NVIC_IRQChannelSubPriority=0x00;
	NVIC_Struct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_Struct);
}
void PWM(void);
void PWM(void){
	TIM_OCInitTypeDef PWMInit;
	//Cau hinh kenh 1 duty 25%
	PWMInit.TIM_OCMode=TIM_OCMode_PWM1;
	//Tich cuc muc cao
	PWMInit.TIM_OCPolarity=TIM_OCPolarity_High;
	//Phan tram xung muc cao
	PWMInit.TIM_Pulse=10;
	//cho phep xung dau ra
	PWMInit.TIM_OutputState=ENABLE;
	//thiet lap kenh 1
	TIM_OC1Init(TIM2,&PWMInit);
	
	//Cau hinh kenh 2 duty 50%
	PWMInit.TIM_OCMode=TIM_OCMode_PWM1;
	//Tich cuc muc cao
	PWMInit.TIM_OCPolarity=TIM_OCPolarity_High;
	//Phan tram xung muc cao
	PWMInit.TIM_Pulse=25;
	//cho phep xung dau ra
	PWMInit.TIM_OutputState=ENABLE;
	//thiet lap kenh 1
	TIM_OC2Init(TIM2,&PWMInit);
	
	//Cau hinh kenh 2 duty 75%
	PWMInit.TIM_OCMode=TIM_OCMode_PWM1;
	//Tich cuc muc cao
	PWMInit.TIM_OCPolarity=TIM_OCPolarity_High;
	//Phan tram xung muc cao
	PWMInit.TIM_Pulse=50;
	//cho phep xung dau ra
	PWMInit.TIM_OutputState=ENABLE;
	//thiet lap kenh 1
	TIM_OC3Init(TIM2,&PWMInit);
	
	//Cau hinh kenh 2 duty 100%
	PWMInit.TIM_OCMode=TIM_OCMode_PWM1;
	//Tich cuc muc cao
	PWMInit.TIM_OCPolarity=TIM_OCPolarity_High;
	//Phan tram xung muc cao
	PWMInit.TIM_Pulse=100;
	//cho phep xung dau ra
	PWMInit.TIM_OutputState=ENABLE;
	//thiet lap kenh 1
	TIM_OC4Init(TIM2,&PWMInit);
		
}
void PWM_cofig(void);
void PWM_cofig(void)
{
	RCC_APB2PeriphClockCmd(PWMCLock,ENABLE);
	GPIO_InitTypeDef PWMStucture;
	PWMStucture.GPIO_Mode=GPIO_Mode_AF_PP;
	PWMStucture.GPIO_Pin=CH1|CH2|CH3|CH4;
	PWMStucture.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(PWM_PORT,&PWMStucture);
}
uint8_t x=0;
int main(void){
	GPIO_cofig();
	GPIO_SetBits(LED_PORT,LED1|LED2);
	DelayInit();
	
	TIMER2_Configuration();
	PWM_cofig();
	PWM();
	while(1)
		{
			
				
				
			 
	  }
}
void TIM2_IRQHandler()
{
	// Checks whether the TIM2 interrupt has occurred or not
	if (TIM_GetITStatus(TIM2, TIM_IT_Update))
	{
		// chop tat led o PB0

		if(x==1)
			{
				GPIO_SetBits(LED_PORT,LED1);
				x=0;
			}
		else
			{
				x=1;
				GPIO_ResetBits(LED_PORT,LED1);
				}
		// Clears the TIM2 interrupt pending bit
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}

