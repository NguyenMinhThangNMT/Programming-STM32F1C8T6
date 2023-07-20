/**
  ******************************************************************************
  * @file		delay.c
  * @author	www.hocdientu123.vn
  * @date		25/06/2019
  ******************************************************************************
  */
#include "delay.h"
// For store tick counts in us
static __IO uint32_t nTicks;
// SysTick_Handler function will be called every 1 us
void SysTick_Handler()
{
	if (nTicks != 0)
	{
		nTicks--;
	}
}

void DelayInit()
{
	// Update SystemCoreClock value
	SystemCoreClockUpdate();
	// Configure the SysTick timer to overflow every 1 us
	SysTick_Config(SystemCoreClock / 1000000);//cau hinh thoi gian ngat
	/****************************************
	 *SystemCoreClock/1000      1ms         *
	 *SystemCoreClock/100000    10us        *
	 *SystemCoreClock/1000000   1us         *
	 *****************************************/
}
/*******************************************************************************
Noi Dung      :   Tao delay_us
Tham Bien     :   value
Tra Ve        :   Khong.
*******************************************************************************/
void Delay_us(uint32_t n)
{
	// Reload us value
	nTicks = n;
	// Wait until usTick reach zero
	while (nTicks);
}
/*******************************************************************************
Noi Dung      :   Tao delay_ms
Tham Bien     :   value
Tra Ve        :   Khong.
*******************************************************************************/
void Delay_ms(uint32_t n)
{
	// Wait until ms reach zero
	while (n--)
	{
		// Delay 1ms
		Delay_us(100);
	}
}

/********************************* END OF FILE ********************************/
/******************************************************************************/
