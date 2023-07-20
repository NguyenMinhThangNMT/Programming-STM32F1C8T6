#include "HSI.h"
void HSIcofig(){
	RCC_DeInit();
	RCC_HSICmd(ENABLE);
	while(!RCC_GetFlagStatus(RCC_FLAG_HSIRDY));
	FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
	FLASH_SetLatency(FLASH_Latency_0);
	RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);
	RCC_HCLKConfig(RCC_SYSCLK_Div1);
	RCC_PCLK1Config(RCC_HCLK_Div1);
	RCC_PCLK2Config(RCC_HCLK_Div1);
	while(RCC_GetSYSCLKSource() !=0x00);
}




