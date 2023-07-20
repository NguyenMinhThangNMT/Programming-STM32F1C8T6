/**
  ******************************************************************************
  * @file		gpio.c
  * @author	www.hocdientu123.vn
  * @date		25/06/2019
  ******************************************************************************
  */
#include "main.h"	
#include "gpio.h"
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  //Enable clock AFIO
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	
/*==================================PORTB==========================================*/
	//Enable clock GPIOB
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
//_________________________________OUTPUT__________________________________________
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;	//khai bao các chân PB0 và PB1       		
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;			// ngõ ra kieu day keo
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		// thiet lap toc do ngo ra cac chan
 GPIO_Init(GPIOB,&GPIO_InitStructure);
 }
	
/********************************* END OF FILE ********************************/
/******************************************************************************/
