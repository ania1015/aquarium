#include<stdint.h>
#include<stddef.h>
#include<string.h>
#include"tim2.h"
#include"ReadingWriting.h"
#include"usart.h"
#include "main.h"

#define SRAM_START 0x20000000U
#define SRAM_SIZE (48 * 1024) //48kb on a basis of 156 datasheet
#define SRAM_END ((SRAM_START) + (SRAM_SIZE))

#define STACK_START SRAM_END

#define RCC_BASEADDR 0x40021000U 
#define RCC_CR ( uint32_t *)(RCC_BASEADDR + 0x00)

#define TIM2_BASEADDR 0x40000000U
#define TIM2_SR ( uint32_t *)(TIM2_BASEADDR + 0x10)

#define SCB_VTOR ( uint32_t *)(0xE000ED08U)


extern uint32_t _s_data;
extern uint32_t _start_of_data;
extern uint32_t _end_of_data;
extern uint32_t _start_bss;
extern uint32_t _end_bss;


extern int main(void);

void CommonHandler(void)
{
	while(1);
}

void ResetHandler(void);
void NmiHandler(void) __attribute__((weak, alias("CommonHandler")));
void HardFaultHandler(void)  __attribute__((weak, alias("CommonHandler")));
void MemManageHandler(void)  __attribute__((weak, alias("CommonHandler")));
void BusFaultHandler(void)  __attribute__((weak, alias("CommonHandler")));
void UsageFaultHandler(void)  __attribute__((weak, alias("CommonHandler")));
void SVCallHandler(void)  __attribute__((weak, alias("CommonHandler")));
void DebugHandler(void)  __attribute__((weak, alias("CommonHandler")));
void PendSVHandler(void)  __attribute__((weak, alias("CommonHandler")));
void SysTickHandler(void)  __attribute__((weak, alias("CommonHandler")));
void WWDGHandler(void)  __attribute__((weak, alias("CommonHandler")));
void PVD_PVMHandler(void)  __attribute__((weak, alias("CommonHandler")));
void RTC_TAMP_STAMP_CSS_LSEHandler(void)  __attribute__((weak, alias("CommonHandler")));
void RTC_WKUPHandler(void)  __attribute__((weak, alias("CommonHandler")));
void FLASHHandler(void)  __attribute__((weak, alias("CommonHandler")));
void RCCHandler(void)  __attribute__((weak, alias("CommonHandler")));
void EXTI0Handler(void)  __attribute__((weak, alias("CommonHandler")));
void EXTI1Handler(void)  __attribute__((weak, alias("CommonHandler")));
void EXTI2Handler(void)  __attribute__((weak, alias("CommonHandler")));
void EXTI3Handler(void)  __attribute__((weak, alias("CommonHandler")));
void EXTI4Handler(void)  __attribute__((weak, alias("CommonHandler")));
void DMA1_CH1Handler(void)  __attribute__((weak, alias("CommonHandler")));
void DMA1_CH2Handler(void)  __attribute__((weak, alias("CommonHandler")));
void DMA1_CH3Handler(void)  __attribute__((weak, alias("CommonHandler")));
void DMA1_CH4Handler(void)  __attribute__((weak, alias("CommonHandler")));
void DMA1_CH5Handler(void)  __attribute__((weak, alias("CommonHandler")));
void DMA1_CH6Handler(void)  __attribute__((weak, alias("CommonHandler")));
void DMA1_CH7Handler(void)  __attribute__((weak, alias("CommonHandler")));
void ADc1_2Handler(void)  __attribute__((weak, alias("CommonHandler")));
void CAN1_TXHandler(void)  __attribute__((weak, alias("CommonHandler")));
void CAN1_RX0Handler(void)  __attribute__((weak, alias("CommonHandler")));
void CAN1_RX1Handler(void)  __attribute__((weak, alias("CommonHandler")));
void CAN1_SCEHandler(void)  __attribute__((weak, alias("CommonHandler")));
void EXTI9_5Handler(void)  __attribute__((weak, alias("CommonHandler")));
void TIM1_BRK_TIM15Handler(void)  __attribute__((weak, alias("CommonHandler")));
void TIM1_UP_TIM16Handler(void)  __attribute__((weak, alias("CommonHandler")));
void TIM1_TRG_COMHandler(void)  __attribute__((weak, alias("CommonHandler")));
void TIM1_CCHandler(void)  __attribute__((weak, alias("CommonHandler")));
extern void TIM2Handler(void) __attribute__((interrupt));
void I2C1_EVHandler(void)  __attribute__((weak, alias("CommonHandler")));
void I2C1_ERHandler(void)  __attribute__((weak, alias("CommonHandler")));
void SPI1Handler(void)  __attribute__((weak, alias("CommonHandler")));
void USART1Handler(void)  __attribute__((weak, alias("CommonHandler")));
void USART2Handler(void)  __attribute__((weak, alias("CommonHandler")));
void EXTI15_10Handler(void)  __attribute__((weak, alias("CommonHandler")));
void RTC_ALARMHandler(void)  __attribute__((weak, alias("CommonHandler")));
void SPI3Handler(void)  __attribute__((weak, alias("CommonHandler")));
void TIM6_DACUNDERHandler(void)  __attribute__((weak, alias("CommonHandler")));
void TIM7Handler(void)  __attribute__((weak, alias("CommonHandler")));
void DMA2_CH1Handler(void)  __attribute__((weak, alias("CommonHandler")));
void DMA2_CH2Handler(void)  __attribute__((weak, alias("CommonHandler")));
void DMA2_CH3Handler(void)  __attribute__((weak, alias("CommonHandler")));
void DMA2_CH4Handler(void)  __attribute__((weak, alias("CommonHandler")));
void DMA2_CH5Handler(void)  __attribute__((weak, alias("CommonHandler")));
void COMPHandler(void)  __attribute__((weak, alias("CommonHandler")));
void LPTIM1Handler(void)  __attribute__((weak, alias("CommonHandler")));
void LPTIM2Handler(void)  __attribute__((weak, alias("CommonHandler")));
void USB_FSHandler(void)  __attribute__((weak, alias("CommonHandler")));
void DMA2_CH6Handler(void)  __attribute__((weak, alias("CommonHandler")));
void DMA2_CH7Handler(void)  __attribute__((weak, alias("CommonHandler")));
void LPUART1Handler(void)  __attribute__((weak, alias("CommonHandler")));
void QUADSPIHandler(void)  __attribute__((weak, alias("CommonHandler")));
void I2C3_EVHandler(void)  __attribute__((weak, alias("CommonHandler")));
void I2C3_ERHandler(void)  __attribute__((weak, alias("CommonHandler")));
void SAI1Handler(void)  __attribute__((weak, alias("CommonHandler")));
void SWPMI1Handler(void)  __attribute__((weak, alias("CommonHandler")));
void TSCHandler(void)  __attribute__((weak, alias("CommonHandler")));
void RNGHandler(void)  __attribute__((weak, alias("CommonHandler")));
void FPUHandler(void)  __attribute__((weak, alias("CommonHandler")));
void CRSHandler(void)  __attribute__((weak, alias("CommonHandler")));

uint32_t *vectors[] __attribute__((section(".isr_vector")))={
	(uint32_t *)SRAM_END,
	(uint32_t *)&ResetHandler, // 0x04
	(uint32_t *)&NmiHandler, //0x08
    (uint32_t *)&HardFaultHandler, //0x0C
	(uint32_t *)&MemManageHandler, //0x10 
	(uint32_t *)&BusFaultHandler, //0x14
	(uint32_t *)&UsageFaultHandler, // 0x18
	0, //0x1C
	0, // 0x20
	0,  // 0x24
	0, //0x28
	(uint32_t *)&SVCallHandler, //0x2C
	(uint32_t *)&DebugHandler, //0x30
	0, //0x34
	(uint32_t *)&PendSVHandler, //0x38
	(uint32_t *)&SysTickHandler, //0x3C
	(uint32_t *)&WWDGHandler, // 0x40
	(uint32_t *)&PVD_PVMHandler, //0x44
	(uint32_t *)&RTC_TAMP_STAMP_CSS_LSEHandler, // 0x48
	(uint32_t *)&RTC_WKUPHandler, //0x4C
	(uint32_t *)&FLASHHandler, //0x50
	(uint32_t *)&RCCHandler, //0x54
	(uint32_t *)&EXTI0Handler, //0x58
    (uint32_t *)&EXTI1Handler, //0x5C
	(uint32_t *)&EXTI2Handler, //0x60
	(uint32_t *)&EXTI3Handler, //0x64
	(uint32_t *)&EXTI4Handler, //0x68
	(uint32_t *)&DMA1_CH1Handler, //0x6C
	(uint32_t *)&DMA1_CH2Handler, //0x70
	(uint32_t *)&DMA1_CH3Handler, //0x74
	(uint32_t *)&DMA1_CH4Handler, //0x78
	(uint32_t *)&DMA1_CH5Handler, //0x7C
	(uint32_t *)&DMA1_CH6Handler, //0x80
	(uint32_t *)&DMA1_CH7Handler, //0x84
 	(uint32_t *)&ADc1_2Handler, //0x88
    (uint32_t *)&CAN1_TXHandler, //0x8C
	(uint32_t *)&CAN1_RX0Handler, //0x90
	(uint32_t *)&CAN1_RX1Handler, //0x94
	(uint32_t *)&CAN1_SCEHandler, //0x98
	(uint32_t *)&EXTI9_5Handler, //0x9C
	(uint32_t *)&TIM1_BRK_TIM15Handler, //0xA0
	(uint32_t *)&TIM1_UP_TIM16Handler, //0xA4
	(uint32_t *)&TIM1_TRG_COMHandler, //0xA8
	(uint32_t *)&TIM1_CCHandler, //0xAC
	(uint32_t *)&TIM2Handler, //0xB0
	0, //(uint32_t)&TIM3H6Handler, 0xb4
	0, //0xb8
	(uint32_t *)&I2C1_EVHandler, //0xbc
	(uint32_t *)&I2C1_ERHandler, //0xc0
	0, //(uint32_t)&I2C2_EVHandler, //0xc4
	0, //(uint32_t)&I2C2_ERHandler, //0xC8
	(uint32_t *)&SPI1Handler, //0xcc 
	0, //(uint32_t)&SPI2Handler, //0xD0
	(uint32_t *)&USART1Handler, //0xd4
	(uint32_t *)&USART2Handler, //0xd8
	0, //(uint32_t)&USART3Handler, //0xdc
	(uint32_t *)&EXTI15_10Handler, //0xe0
	(uint32_t *)&RTC_ALARMHandler, //0xe4
	0, //0xe8
	0, //0xec
	0, //0xf0
	0, //0xf4
	0, //0xf8
	0, //0xfc
	0, //0x100
	0, //(uint32_t)&SDMMC1Handler, //0x104
	0, //0x108
	(uint32_t *)&SPI3Handler, //0x10C
	0, //(uint32_t)&UART4Handler, // 0x110
	0, //0x114 
	(uint32_t *)&TIM6_DACUNDERHandler, //0x118
	(uint32_t *)&TIM7Handler, //0x11C 
	(uint32_t *)&DMA2_CH1Handler, //0x120
	(uint32_t *)&DMA2_CH2Handler, //0x124
	(uint32_t *)&DMA2_CH3Handler, //0x128
	(uint32_t *)&DMA2_CH4Handler, //0x12C
	(uint32_t *)&DMA2_CH5Handler, //0x130
 	0, //(uint32_t)&DFSDM1_FLT0Handler, //0x134
	0, //(uint32_t)&DFSDM1_FLT1Handler, //0x138
	0, //0x13C
	(uint32_t *)&COMPHandler, //0x140
	(uint32_t *)&LPTIM1Handler, //0x144
	(uint32_t *)&LPTIM2Handler, //0x148
	(uint32_t *)&USB_FSHandler, //0x14C
 	(uint32_t *)&DMA2_CH6Handler, //0x150 
 	(uint32_t *)&DMA2_CH7Handler, //0x154
 	(uint32_t *)&LPUART1Handler, //0x158
 	(uint32_t *)&QUADSPIHandler, //0x15C
 	(uint32_t *)&I2C3_EVHandler, //0x160
 	(uint32_t *)&I2C3_ERHandler, //0x164
 	(uint32_t *)&SAI1Handler, //0x168
	0, //0x16c
	(uint32_t *)&SWPMI1Handler, //0x170
	(uint32_t *)&TSCHandler, //0x174
	0, //(uint32_t)&LCDHandler, //0x178
	0, //(uint32_t)&AESHandler, //0x17C
	(uint32_t *)&RNGHandler, //0x180
	(uint32_t *)&FPUHandler, //0x184
	(uint32_t *)&CRSHandler, //0x188
	0, //0x18C
	0 //0x190
};

void *memcpy(void *dest, const void*src, size_t n){
	unsigned char *t = dest;
	const unsigned char* p= src;

	for(unsigned int i = 0; i < n; i++)
	{
		*t++ = *p++;
	}
	return dest;
}
void *memset(void *s, int c, size_t n){

	unsigned char *t = s;

	for(unsigned int i = 0; i < n; i++)
	{
		*t++ = c;
	}
	return s;
}

void ResetHandler(void)
{
	uint32_t size = (uint32_t)&_end_of_data - (uint32_t)&_start_of_data;
        uint8_t *pSrc  = (uint8_t*)&_s_data;
        uint8_t *pDst  = (uint8_t*)&_start_of_data; //sram
        for(uint32_t i = 0; i < size; i++)
                *pDst++ = *pSrc++;
        size = (uint32_t)&_end_bss - (uint32_t)&_start_bss;
        pDst  = (uint8_t*)&_start_bss;
        for(uint32_t i = 0; i < size; i++)
                *pDst++ = 0;

	WritePin(SCB_VTOR, 0x08000000);
	__asm__ __volatile__("dsb":::"memory");

	//call main
	main();

	while(1);
} 

