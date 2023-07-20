//dieu khien 8 led
#include "stm32f10x.h"
#include "delay.h"

#define LED_PORT     GPIOC
#define LED1         GPIO_Pin_13
#define LED2         GPIO_Pin_14

#define BT_PORT     GPIOA
#define BT1         GPIO_Pin_2
#define BT2         GPIO_Pin_3


#define LEDCLock    RCC_APB2Periph_GPIOC
#define BTCLock     RCC_APB2Periph_GPIOA
void delay(void);
void delay(void)
{
	uint32_t i;
	for (i=0;i<0xfffff;++i){}
}
void GPIO_cofig()
{
	RCC_APB2PeriphClockCmd(LEDCLock|BTCLock,ENABLE);
  
	GPIO_InitTypeDef Structure;
	Structure.GPIO_Mode=GPIO_Mode_Out_OD;
	Structure.GPIO_Pin=LED1|LED2;
	Structure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(LED_PORT,&Structure);
	
	
	Structure.GPIO_Mode=GPIO_Mode_IPU;
	Structure.GPIO_Pin=BT1|BT2;
	GPIO_Init(BT_PORT,&Structure);
}
//Tao cofig ham ngat
void EXTI2_Interupt_Cofig(void)
{
	EXTI_InitTypeDef   EXTI_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;
//bat clock ngat ngoai
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	//Chon kenh ngat dong ngat
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource2);
	//xoa co ngat
	EXTI_ClearITPendingBit(EXTI_Line2);
	
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Line=EXTI_Line2;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	//Set vecto ngat
	NVIC_InitStructure.NVIC_IRQChannel=EXTI2_IRQn;
	//Chon do uu tien
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
uint32_t count=0;
void EXTI2_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line2) != RESET)
   {
		 EXTI_ClearITPendingBit(EXTI_Line2);
		 if(count<5){count++;}
		 else count=1;
	 }
}
int main(void){
	GPIO_cofig();
	GPIO_SetBits(LED_PORT,LED1|LED2);
	EXTI2_Interupt_Cofig();
	while(1)
		{
			if (count == 1){
				GPIO_SetBits(LED_PORT,LED1|LED2);
			  delay();
				GPIO_ResetBits(LED_PORT,LED1|LED2);
			  delay();}
			if (count == 2){
				GPIO_SetBits(LED_PORT,LED2);
				GPIO_ResetBits(LED_PORT,LED1);
			  }
			if (count == 3){
				GPIO_SetBits(LED_PORT,LED1);
				GPIO_ResetBits(LED_PORT,LED2);
			  ;}
			if (count == 4){
				GPIO_ResetBits(LED_PORT,LED2);
				GPIO_ResetBits(LED_PORT,LED1);
			  ;}
			if (count == 5){
				GPIO_SetBits(LED_PORT,LED2);
				GPIO_SetBits(LED_PORT,LED1);
			  ;}
	  }
}

