#include "ReadingWriting.h"
#include "delay.h"

#define RCC_BASEADDR 0x40021000U 

void SysTick_Initialization(void)
{

    static unsigned long tmp; 
	tmp = 0xFFFFFF; 
	WritePin(STK_LOAD, tmp);

    tmp = 0x000000; 
	WritePin(STK_VAL, tmp);

    tmp = ReadPort(STK_CTRL);
	tmp |= (1<<2); 
	WritePin(STK_CTRL, tmp);

    tmp = ReadPort(STK_CTRL);
	tmp |= (1<<0); 
	WritePin(STK_CTRL, tmp);

}


