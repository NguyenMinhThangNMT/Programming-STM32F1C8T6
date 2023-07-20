/**
  ******************************************************************************
  * @file		main.c
  * @author	www.hocdientu123.vn
  * @date		25/06/2019
  ******************************************************************************
  */
#include "main.h"
//---------------------------KHAI BAO CAC BIEN VA HANG-------------------------//
uint16_t temp_adc=0;
//---------------------------KHAI BAO CAC HAM----------------------------------//
//---------------------------HAM MAIN------------------------------------------//
int main()
	{
		DelayInit();	// goi ham khoi tao du lieu cho cac ham delay
		GPIO_Configuration();	// goi ham cau hinh ngo vao ra cho cac PORT
		GPIO_PinRemapConfig (GPIO_Remap_SWJ_JTAGDisable, ENABLE);//bo che do nap JTAGD
		LCD16X2_Init();				//goi ham cau hinh LCD
		ADC_Configuration();	//goi ham cau hinh chuyen doi ADC
		LCD16X2_Clear();		//xoa man hinh
		LCD16X2_Gotoxy(0,0);//hien thi toa do x,y=(0,0)
		LCD16X2_PutString("GIA TRI ADC");//hien thi chuoi ky tu ra man hinh LCD
		while(1)
		{
			temp_adc=ADC1_Read();	//doc gia tri ADC
			LCD16X2_Gotoxy(0,1);	//hien thi tai toa do x,y=(0,1)
			LCD16X2_NumBer(temp_adc,4);//hien thi gia tri ADC ra man hinh LCD
		}
	}

