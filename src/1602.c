#include "1602.h"
#include "Systick.h"

void setAllBits(GPIO_TypeDef* GPIOx,uint16_t pin1,uint16_t pin2,uint16_t pin3,uint16_t pin4,u8 cmd) {
	u8 p1 = (cmd & 0b00010000) >> 4;
	u8 p2 = (cmd & 0b00100000) >> 5;
	u8 p3 = (cmd & 0b01000000) >> 6;
	u8 p4 = (cmd & 0b10000000) >> 7;



	setBits(GPIOx,pin1,p1);
	setBits(GPIOx,pin2,p2);
	setBits(GPIOx,pin3,p3);
	setBits(GPIOx,pin4,p4);
}

void setBits(GPIO_TypeDef* GPIOx,uint16_t pin,u8 bits) {
	if(bits) {
		GPIO_SetBits(GPIOx, pin);
	} else {
		GPIO_ResetBits(GPIOx, pin);
	}
}

void GPIO_Configuration(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA,ENABLE);//打开时钟
       //dataIO GPIOA4~7 初始化
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(LCD_DATA_PORT, &GPIO_InitStructure);
        // RS RW E IO初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12 |GPIO_Pin_8|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}



/* 检测液晶忙不忙 */
void LCD1602_Wait_Ready(void)
{
	int8_t sta;

	DATAOUT(0xff);    //PA端口全部置1
	LCD_RS_Clr();     //RS 0
	LCD_RW_Set();     //RW 1
	do
	{
		LCD_EN_Set();   //EN 1
		SysTick_Delay_Ms(5);	//延时5MS
 		sta = GPIO_ReadInputDataBit(LCD_DATA_PORT, GPIO_Pin_8);//读取状态字
		LCD_EN_Clr();  //EN  0
	}while(sta & 0x80);//bit7等于1表示忙,重复检测到其为0停止
}

/*向1602写入一字节命令,cmd-待写入命令 */
//写入指令PA4-7 RS-0  RW-0
void LCD1602_Write_Cmd(u8 cmd)
{
	LCD1602_Wait_Ready();  //判断忙不忙
	LCD_RS_Clr();
	LCD_RW_Clr();
	DATAOUT(cmd);  //先传高四位
	LCD_EN_Set();
	LCD_EN_Clr();

	DATAOUT(cmd<<4); //低四位左移到高四位
	LCD_EN_Set();
	LCD_EN_Clr();
}

/* 向1602写入一字节数据*/
void LCD1602_Write_Dat(u8 dat)
{
	LCD1602_Wait_Ready(); //判断忙不忙
	LCD_RS_Set();   //1
	LCD_RW_Clr();   //0

	DATAOUT(dat);   //先传高四位
	LCD_EN_Set();
	LCD_EN_Clr();

	DATAOUT(dat<<4); //低四位左移到高四位
	LCD_EN_Set();
	LCD_EN_Clr();

}

/*清屏*/
void LCD1602_ClearScreen(void)
{
	LCD1602_Write_Cmd(0x01);

}

/* 设置RAM其实地址,即光标位置,（X,Y）对应屏幕上的字符坐标 */
void LCD1602_Set_Cursor(u8 x, u8 y)
{
	u8 addr;

	if (y == 0)
		addr = 0x00 + x;
	else
		addr = 0x40 + x;
	LCD1602_Write_Cmd(addr | 0x80);
}

/* 在液晶上显示字符串,（X,Y）-对应屏幕上的其实坐标，str-字符串指针 */
void LCD1602_Show_Str(u8 x, u8 y, u8 *str)
{
	LCD1602_Set_Cursor(x, y);
	while(*str != '\0')
	{
		LCD1602_Write_Dat(*str++);
	}
}

/* 初始化液晶 */
void LCD1602_Init(void)
{
	LCD1602_Write_Cmd(0x28);	//16*2显示，5*7点阵，4位数据口
	LCD1602_Write_Cmd(0x0C);	//开显示，光标关闭
	LCD1602_Write_Cmd(0x06);	//文字不动，地址自动+1
	LCD1602_Write_Cmd(0x01);	//清屏

}
