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
#define LED_PORT       GPIOC

#define LEDGREEN       GPIO_Pin_14
#define LEDRED         GPIO_Pin_13
#define LEDBLUE        GPIO_Pin_15

#define BT_PORT        GPIOB
#define BT1            GPIO_Pin_5
#define BT2            GPIO_Pin_6

#define SPI_PORT     GPIOB
#define SS          GPIO_Pin_12
#define SCK         GPIO_Pin_13
#define MISO        GPIO_Pin_14
#define MOSI        GPIO_Pin_15

#define LEDCLock    RCC_APB2Periph_GPIOC
#define BTCLock     RCC_APB2Periph_GPIOB

uint8_t Led[8]={0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};
uint8_t Led_I[8]={0x3c,0x18,0x18,0x18,0x18,0x18,0x18,0x3c};
uint8_t Led_love[8]={0x00,0x66,0xff,0xff,0xff,0x7e,0x3c,0x18};
uint8_t Led_U[8]={0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0x7e,0x3c};
// For store tick counts in us



void GPIO_cofig()
{
	RCC_APB2PeriphClockCmd(LEDCLock|BTCLock,ENABLE);
  
	GPIO_InitTypeDef Structure;
	Structure.GPIO_Mode=GPIO_Mode_Out_PP;
	Structure.GPIO_Pin=LEDRED |LEDGREEN|LEDBLUE;
	Structure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(LED_PORT,&Structure);
	
	
	Structure.GPIO_Mode=GPIO_Mode_IPU;
	Structure.GPIO_Pin=BT1|BT2;
	GPIO_Init(SPI_PORT,&Structure);
	//Cau hinh chan SS
	Structure.GPIO_Mode=GPIO_Mode_Out_PP;
	Structure.GPIO_Pin=SS;
	Structure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(SPI_PORT,&Structure);

	GPIO_ResetBits(SPI_PORT,SS);
	//Cau hinh chan SCK
	Structure.GPIO_Mode=GPIO_Mode_AF_PP;
	Structure.GPIO_Pin=SCK;
	Structure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(SPI_PORT,&Structure);
	//Cau hinh chan MISO
	Structure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	Structure.GPIO_Pin=MISO;
	Structure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(SPI_PORT,&Structure);
	//Cau hinh chan MOSI
	Structure.GPIO_Mode=GPIO_Mode_AF_PP;
	Structure.GPIO_Pin=MOSI;
	Structure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(SPI_PORT,&Structure);
}
void Spi2(void);
void Spi2()
{
	//Cau hinh SPI
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2,ENABLE);
	SPI_InitTypeDef Spi2Init;
	Spi2Init.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_4;
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
void spi_send(uint8_t u8Data)
{
	SPI_I2S_SendData(SPI2,u8Data);
	while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_BSY)==SET){}
}

int main(void){
	GPIO_cofig();
	GPIO_ResetBits(LED_PORT,LEDRED|LEDGREEN|LEDBLUE);
	DelayInit();
	Spi2();
	
	/* chon che do giai ma */
	/* giai ma led 7 doan tat ca 8 led */
	spi_send(0x09);
	spi_send(0);
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	
	/* chon do sang 7 / 32 */
	spi_send(0x0a);
	spi_send(0x03);
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	
	/* hien thi 8 led */
	spi_send(0x0b);
	spi_send(0x07);
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	
	/* che do hoat dong binh thuong */
	spi_send(0x0c);
	spi_send(0x07);
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	
	/* che do hoat dong binh thuong */
	spi_send(0x0f);
	spi_send(0x00);
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	
		for (int i =0;i<8;i++)
      {
				spi_send(Led[i]);
				spi_send(Led_I[i]);
				GPIO_SetBits(GPIOB, GPIO_Pin_12);
	      GPIO_ResetBits(GPIOB, GPIO_Pin_12);
				Delay_ms(500);
			}
			for (int i =0;i<8;i++)
      {
				spi_send(Led[i]);
				spi_send(Led_love[i]);
				GPIO_SetBits(GPIOB, GPIO_Pin_12);
	      GPIO_ResetBits(GPIOB, GPIO_Pin_12);
				Delay_ms(500);
			}
			for (int i =0;i<8;i++)
      {
				spi_send(Led[i]);
				spi_send(Led_U[i]);
				GPIO_SetBits(GPIOB, GPIO_Pin_12);
	      GPIO_ResetBits(GPIOB, GPIO_Pin_12);
				Delay_ms(500);
			}
	
	while(1)
		{
		
		
	  }
		return(0);
}

