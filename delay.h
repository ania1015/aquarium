#include "stdint.h"
#include "ReadingWriting.h"

#ifndef DELAY_H
#define DELAY_H

#define STK_BASEADDR 0xE000E010

#define STK_CTRL ( uint32_t *)(STK_BASEADDR + 0x00)
#define STK_LOAD ( uint32_t *)(STK_BASEADDR + 0x04)
#define STK_VAL ( uint32_t *)(STK_BASEADDR + 0x08)
#define STK_CALIB ( uint32_t *)(STK_BASEADDR + 0x0C) 

static inline void delay_us( unsigned long useconds)
{
    unsigned long lastValue = ReadPort(STK_VAL);;
    while(((lastValue - ReadPort(STK_VAL)) & 0xffffff) < (useconds * 24));

}

void SysTick_Initialization(void);
#endif
