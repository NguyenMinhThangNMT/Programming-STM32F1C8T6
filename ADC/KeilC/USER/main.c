//dieu khien 8 led
#include "stm32f10x.h"


#define LED_PORT     GPIOB
#define LED1         GPIO_Pin_0
#define LED2         GPIO_Pin_1

#define BT_PORT     GPIOB
#define BT1         GPIO_Pin_2
#define BT2         GPIO_Pin_3


#define LEDCLock    RCC_APB2Periph_GPIOB
#define BTCLock     RCC_APB2Periph_GPIOB
void delay(void);
void delay(void)
{
	uint32_t i;
	for (i=0;i<0xfffff;++i){}
	}
void GPIO_Input_cofig()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	GPIO_InitTypeDef Structure;
	Structure.GPIO_Mode=GPIO_Mode_AIN;
	Structure.GPIO_Pin=GPIO_Pin_1;
	GPIO_Init(GPIOA,&Structure);
}

void ADC_cofig()
{
	ADC_InitTypeDef ADC_InitStruct;
	//cap xung cho bo adc 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	//cho che do cho adc
	ADC_InitStruct.ADC_Mode=ADC_Mode_Independent;
	//tat che do scan
	ADC_InitStruct.ADC_ScanConvMode=DISABLE;
	//bat che do chuyen doi lien tuc
  ADC_InitStruct.ADC_ContinuousConvMode=ENABLE;
	//chon kieu luu tru du lieu
	ADC_InitStruct.ADC_DataAlign=ADC_DataAlign_Right;
	//Chon so luong kenh adc su dung
	ADC_InitStruct.ADC_NbrOfChannel=1;
	//cau hinh adc
	ADC_Init(ADC1,&ADC_InitStruct);
	//kich hoat adc
	ADC_Cmd(ADC1,ENABLE);
	//bat che do hieu chinh adc
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1));
}

uint16_t ADC1_Read()
{ 
	//Chon kenh chuyern doi va so kenh,chu ki chuyen doi
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,1,ADC_SampleTime_55Cycles5);
	//bat dau chuyen doi
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	//doi den khi chuyen doi xong
	while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));
	//tra gia tri ve adc
	return(ADC_GetConversionValue(ADC1));
}
	
	
	
	
int main(void){
	GPIO_Input_cofig();
	ADC_cofig();
	delay();
	while(1)
		{
			
	  }
}

