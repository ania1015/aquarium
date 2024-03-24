#include "ReadingWriting.h"
#include "tim2.h"



void Tim2_Initialization(void)
{ 
    static unsigned long t; 

    //clock enable for Tim
    t=ReadPort(RCC_APB1ENR);
    t |= 0x1;
    WritePin(RCC_APB1ENR, t);


    t = 0x186A0 - 1;
    WritePin(TIM2_ARR, t);

    t = 99500; 
    WritePin(TIM2_CNT, t); 

    // direction 
    t=ReadPort(TIM2_CR1);
    t &= ~0x10;
    WritePin(TIM2_CR1, t);

    //PSC f cnt = fck_psc / psc+1
    t = 0xBB7F;
    WritePin(TIM2_PSC, t);

    t =255; 
    WritePin(TIM2_CCR2, t);

    t =755;  
    WritePin(TIM2_CCR3, t);

    // set OC1M to 0110 bity 16, 6,5,4
    t =ReadPort(TIM2_CCMR1);
    t &= 0xFFFEFF00;
    t |= 0x00000068; 
    WritePin(TIM2_CCMR1, t);

    //cc1p = 0 active = high
    t =ReadPort(TIM2_CCER);
    t &= ~(1 << 1);
    t |= (1 << 0);
    WritePin(TIM2_CCER, t);

    // CNT is updated every 2ms so 2000 is about 4seconds 
	t = 0x00000000;
    WritePin(TIM2_CCR1, t); // zmieniajac CCr zmieniam wypełnienie

    //en interrupt update cc1ie
    t=ReadPort(TIM2_DIER);
	t |= ((1<<2) | (1<<3));
    WritePin(TIM2_DIER, t);

    //enable isr
    t =ReadPort(NVIC_ISER0);
    t |= (1 << 28);
    WritePin(NVIC_ISER0, t);

    // enabling clock -- last 
    t=ReadPort(TIM2_CR1);
    t |= 0x1;
    WritePin(TIM2_CR1, t);
}

void setDutyPWM(unsigned int duty)
{   
    WritePin(TIM2_CCR1, duty);
}
