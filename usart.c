#include "usart.h"
#include "ReadingWriting.h"
#include "delay.h"

void UsartInitialize(void)
{
    //enable clock 
     uint32_t x;
    x = ReadPort(RCC_APB1ENR);
	x |= RCC_USART2_EN;
	WritePin(RCC_APB1ENR, x);
    
    //pins configure
        //AF7 = usart  PA2
        x = ReadPort(GPIOA_AFRL);
        x &= ~0xF00;
        x |= 0x700;//(1<<4 || 1<<5 || 1<<6);
        WritePin(GPIOA_AFRL, x);
        // AF7 = usart PA15 
        x = ReadPort(GPIOA_AFRH);
        x &= ~0xF0000000;
        x |= 0x30000000;
        WritePin(GPIOA_AFRH, x);

        //  moder  PA2
        x = ReadPort(GPIOA_MODER);
        x &= 0xFFFFFFCF ;
        x |= (1 << 5);
        x &= 0x3FFFFFFF;
        x |= (1 << 31);
        WritePin(GPIOA_MODER, x);


    //usart configure

        //8 bits cfg
        x = ReadPort(USART_CR1);
        x |= 0x00;
        WritePin(USART_CR1, x);

        // baud rate 
        x = 208;
        WritePin(USART_BRR, x);


        x = ReadPort(USART_CR1);
        x &= ~(1<<28);
        x &= ~(1<<12);
        WritePin(USART_CR1, x);

        //stop bits
        x = ReadPort(USART_CR2);
        x &= ~0x3000;
        WritePin(USART_CR2, x);

        //TE enable 
        x = ReadPort(USART_CR1);
        x |= (1<<3);
       
        x |= (1<<0);
         x |= (1<<2);
        WritePin(USART_CR1, x);
}

int disp_char(int c)
{
     while(ReadPin(USART_ISR, 7) != 1);
        WritePin(USART_TDR, c);

        return c;
}


void printHex(unsigned int n){
    unsigned char c;
    if (n <= 9){
        c = '0' + n;
    }
    else{
        c = 'A' + n -10; 
    }
    disp_char(c);
}

void printByte(unsigned int n)
{
    printHex((n>>4) & 0xF);
    printHex((n>>0) & 0xF);
}

unsigned int UartRead(void)
{
    return ReadPort(USART_RDR) & 0xFF;
}

unsigned int char2num(unsigned char c)
{
    unsigned int n  = 0;
    if (c <= '9'&& c>='0'){
        n = c - '0';
    }
    else if(c>='A' && c <= 'F'){
        n = c - 'A' + 10; 
    }
    return n;
}

unsigned int tab2num(unsigned int * tab, unsigned int n)
{
	/*
	zakładam ze zawsze mam Little endian czyli tablicę przesuwam o i*8 bitów 
	*/
 	unsigned int liczba = 0; 
	for(int i = 0; i < n; i++)
	{
		liczba |= tab[i] << 8*i;
	}
	return liczba;
}

void nextLine(void)
{
    disp_char('\r');
    disp_char('\n');
}
