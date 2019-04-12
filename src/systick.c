#include "stm32f10x.h"
#include "Systick.h"
#include "core_cm3.h"  //Systick ���ں�Ƭ������
/*
	�����δ�ʱ��
*/


// 1΢����ʱ
void SysTick_Delay_Us( unsigned int us)
{
	uint32_t i;
	SysTick_Config(SystemCoreClock/1000000);

	for(i=0;i<us;i++)
	{
		while( !((SysTick->CTRL)&(1<<16)) );
	}
	SysTick->CTRL &=~SysTick_CTRL_ENABLE_Msk;
}

//1������ʱ
void SysTick_Delay_Ms( unsigned int  ms)
{
	uint32_t i;
	SysTick_Config(SystemCoreClock/1000);

	for(i=0;i<ms;i++)
	{
		while( !((SysTick->CTRL)&(1<<16)) );
	}
	SysTick->CTRL &=~ SysTick_CTRL_ENABLE_Msk;
}
