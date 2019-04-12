
/*1602.h 文件*/
#ifndef __LCD1602_H
#define __LCD1602_H	  
#include "stm32f10x.h"
#define LCD_DATA_PORT GPIOB

//1602指令/数据 引脚
#define	LCD_RS_Set()	GPIO_SetBits(GPIOB, GPIO_Pin_10)
#define	LCD_RS_Clr()	GPIO_ResetBits(GPIOB, GPIO_Pin_10)

//1602读写引脚
#define	LCD_RW_Set()	GPIO_SetBits(GPIOB, GPIO_Pin_11)
#define	LCD_RW_Clr()	GPIO_ResetBits(GPIOB, GPIO_Pin_11)

//1602使能引脚
#define	LCD_EN_Set()	GPIO_SetBits(GPIOB, GPIO_Pin_12)
#define	LCD_EN_Clr()	GPIO_ResetBits(GPIOB, GPIO_Pin_12)


void setAllBits(GPIO_TypeDef* GPIOx,uint16_t pin1,uint16_t pin2,uint16_t pin3,uint16_t pin4,u8 cmd);
void setBits(GPIO_TypeDef* GPIOx,uint16_t pin,u8 bits);


//1602数据端口	PD4~7
#define	DATAOUT(x)	setAllBits(LCD_DATA_PORT,GPIO_Pin_5,GPIO_Pin_6,GPIO_Pin_7,GPIO_Pin_8, x);

#define u8  unsigned char

void GPIO_Configuration(void);
void LCD1602_Wait_Ready(void);
void LCD1602_Write_Cmd(u8 cmd);
void LCD1602_Write_Dat(u8 dat);
void LCD1602_ClearScreen(void);
void LCD1602_Set_Cursor(u8 x, u8 y);
void LCD1602_Show_Str(u8 x, u8 y, u8 *str);
void LCD1602_Init(void);

#endif
