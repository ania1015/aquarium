#include "stdint.h"

#ifndef TIM2_H
#define TIM2_H

#define TIM2_BASEADDR 0x40000000U
#define RCC_BASEADDR 0x40021000U
#define NVIC_ISR0 0xE000E100U

#define RCC_APB1ENR (uint32_t *)(RCC_BASEADDR + 0x58)
#define NVIC_ISER0 (uint32_t *)(NVIC_ISR0)

#define TIM2_CNT ( uint32_t *)(TIM2_BASEADDR + 0x24)
#define TIM2_PSC ( uint32_t *)(TIM2_BASEADDR + 0x28)
#define TIM2_ARR ( uint32_t *)(TIM2_BASEADDR + 0x2C)
#define TIM2_SMCR ( uint32_t *)(TIM2_BASEADDR + 0x08) 
#define TIM2_CR1 ( uint32_t *)(TIM2_BASEADDR + 0x00)
#define TIM2_CR2 ( uint32_t *)(TIM2_BASEADDR + 0x04)
#define TIM2_EGR ( uint32_t *)(TIM2_BASEADDR + 0x14)
#define TIM2_CCR ( uint32_t *)(TIM2_BASEADDR + 0x0C) 
#define TIM2_SR ( uint32_t *)(TIM2_BASEADDR + 0x10)
#define TIM2_CCMR1 ( uint32_t *)(TIM2_BASEADDR + 0x18) 
#define TIM2_CCR1 ( uint32_t *)(TIM2_BASEADDR + 0x34)
#define TIM2_CCR1 ( uint32_t *)(TIM2_BASEADDR + 0x34)
#define TIM2_CCR2 ( uint32_t *)(TIM2_BASEADDR + 0x38)
#define TIM2_CCR3 ( uint32_t *)(TIM2_BASEADDR + 0x3C)
#define TIM2_CCR4 ( uint32_t *)(TIM2_BASEADDR + 0x40)
#define TIM2_DIER ( uint32_t *)(TIM2_BASEADDR + 0x0C)
#define TIM2_CCER ( uint32_t *)(TIM2_BASEADDR + 0x20)
#define TIM2_CCMR1 ( uint32_t *)(TIM2_BASEADDR + 0x18)

void Tim2_Initialization(void);
void setDutyPWM(unsigned int duty);

#endif
