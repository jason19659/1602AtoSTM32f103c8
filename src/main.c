#include "Systick.h"
#include "led.h"
#include "1602.h"

int main(void)
{
	u8 str[] = "!@##$%^$%&%^*";

	GPIO_Configuration();
//	setBits(GPIOB, GPIO_Pin_8,1);
//	setBits(GPIOB, GPIO_Pin_8,0);

	//0b10100101;



	//DATAOUT(0b1010);
//	DATAOUT(0b0101);
//
	LCD1602_Init();
	LCD1602_ClearScreen();
	LCD1602_Show_Str(2, 0, str);
 	LCD1602_Show_Str(2, 1, "ASDFJKKJASDFVCVC");


}
