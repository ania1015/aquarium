#include "stdio.h"

#ifndef USART_H
#define USART_H

#define RCC_BASEADDR 0x40021000U 
#define RCC_APB1ENR (uint32_t *)(RCC_BASEADDR + 0x58)
#define RCC_AHB2ENR ( uint32_t *)(RCC_BASEADDR + 0x4C)
#define GPIOA_BASEADDR 0x48000000U

#define USART_BASEADDR 0x40004400U

#define USART_CR1 (uint32_t *)(USART_BASEADDR + 0x00)//bity 28 i 12 00 - 8 bitow 
#define USART_BRR (uint32_t *)(USART_BASEADDR + 0x0C) // baud rate
#define USART_CR2 (uint32_t *)(USART_BASEADDR + 0x04) // bits 13 i 12 - stop bits 00 1
#define USART_RQR (uint32_t *)(USART_BASEADDR + 0x18) 
#define USART_RDR   (uint32_t *)(USART_BASEADDR + 0x24)
#define USART_TDR   (uint32_t *)(USART_BASEADDR + 0x28)
#define USART_ISR  (uint32_t *)(USART_BASEADDR + 0x1C)

#define GPIOA_MODER	( uint32_t *)(GPIOA_BASEADDR + 0x00)
#define GPIOA_ODR	( uint32_t *)(GPIOA_BASEADDR + 0x14)
#define GPIOA_OTYPER ( uint32_t *)(GPIOA_BASEADDR + 0x04)
#define GPIOA_BRR 	( uint32_t *)(GPIOA_BASEADDR + 0x28)
#define GPIOA_PUPDR ( uint32_t *)(GPIOA_BASEADDR + 0x0C)
#define GPIOA_BSRR 	( uint32_t *)(GPIOA_BASEADDR + 0x18)
#define GPIOA_IDR 	( uint32_t *)(GPIOA_BASEADDR + 0x10)
#define GPIOA_OSPEEDR ( uint32_t *)(GPIOA_BASEADDR + 0x08)
#define GPIOA_AFRL ( uint32_t *)(GPIOA_BASEADDR + 0x20)
#define GPIOA_AFRH ( uint32_t *)(GPIOA_BASEADDR + 0x24)

#define RCC_USART2_EN (1<<17)
#define RCC_PAEN (1<<0)
#define PA_2 (1<<2)
#define PA_15 (1<<15)

void UsartInitialize(void);
int disp_char(int c);
void printHex(unsigned int n);
void printByte(unsigned int n);
void nextLine(void);
unsigned int UartRead(void);
unsigned int tab2num(unsigned int * tab, unsigned int n);
unsigned int char2num(unsigned char c);
#endif
