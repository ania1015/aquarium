#include "stdint.h"

#ifndef MAIN_H
#define MAIN_H

#define RCC_BASEADDR 0x40021000U 
#define GPIOA_BASEADDR 0x48000000U
#define PWR_BASEADDR 0x40007000U
#define FLASH_BASEADDR 0x40022000U

#define PWR_CR1	( uint32_t *)(PWR_BASEADDR + 0x00)
#define FLASH_ACR ( uint32_t *)(FLASH_BASEADDR + 0x00)
#define RCC_AHB2ENR ( uint32_t *)(RCC_BASEADDR + 0x4C)
#define RCC_AHB1ENR ( uint32_t *)(RCC_BASEADDR + 0x48)
#define RCC_CR ( uint32_t *)(RCC_BASEADDR + 0x00)
#define RCC_CSR ( uint32_t *)(RCC_BASEADDR + 0x94)

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

#define RCC_PBEN (1<<1)
#define RCC_PAEN (1<<0)
#define GPIOB3 	(1UL<<3)
#define ONE_WIRE (1<<7) //PA7
#define ONE_WIRE_PIN_NR 7 


void reqTemp(void);
void readTemp(unsigned int *tab, int n);
unsigned int Regulator(unsigned int y, const unsigned int w);
unsigned int take_line_buf(int N, unsigned char *r, unsigned int * n);
unsigned int odbior_nastaw(int L, int H, unsigned int* n);
unsigned int PrzetworzDane(unsigned char* r, int l);
#endif
