#include "oneWire.h"
#include "ReadingWriting.h"
#include "delay.h"
#include "usart.h"
#include "main.h"

extern void enableIRQ(void);

extern void disableIRQ(void);

unsigned int  OneWireInitialization(unsigned int pin, uint32_t *address_Reset, uint32_t * address_Reg){
  		
		uint32_t temper; 
		temper = (1 << (16 + pin)); 

		disableIRQ();

		WritePin(address_Reset, temper);
		
		delay_us(500);

		temper = (1 << pin); 
		WritePin(address_Reset, temper);
		
		delay_us(70);

		unsigned int x= ReadPin(address_Reg, pin); // tczy to tak mozna
    	enableIRQ();
		delay_us(500);

    return x;

}

void WriteOne_OneWire(unsigned int pin, uint32_t *address){

		uint32_t temper; 
		temper = (1 << (16 + pin)); 
		disableIRQ();
		WritePin(address, temper);

		delay_us(2);
		
		temper = (1 << pin); 
		WritePin(address, temper);
		enableIRQ();

		delay_us(63);

}

void WriteZero_Onewire( unsigned int pin, uint32_t *address){
  		
		uint32_t temper; 
		temper = (1 << (16 + pin));

		disableIRQ(); 
		WritePin(address, temper);

		delay_us(70);
		
		temper = (1 << pin);
		WritePin(address, temper);
		enableIRQ();
		delay_us(15);
}

 unsigned int ReadOneWire(unsigned int pin, uint32_t *address_Reset, uint32_t * address_Reg){
  		
		uint32_t temper; 
		unsigned int ret = 0;
		temper = (1 << (16 + pin)); 

		disableIRQ(); 

		WritePin(address_Reset, temper);

		delay_us(2);

		temper = (1 << pin); 
		WritePin(address_Reset, temper);

		delay_us(12);

		ret = ReadPin(address_Reg, pin);

		enableIRQ();

		delay_us(45);

		return ret;
} 

void WriteBit(unsigned int bit, unsigned int pin, uint32_t *address_Reset)
{
  if(bit){
    WriteOne_OneWire(pin, address_Reset);
  }
  else{
    WriteZero_Onewire(pin, address_Reset);
  }
}

void WriteByte(unsigned int byte, unsigned int pin, uint32_t *address_Reset)
{
  unsigned int i;

  for(i =0 ; i < 8; i++)
  {
    WriteBit(byte & (1<<i), pin, address_Reset);
  }
}

unsigned int ReadByte(unsigned int pin, uint32_t *address_Reset,  uint32_t * address_Reg)
{
  unsigned int i;
  unsigned int v = 0;

  for(i =0 ; i < 8; i++)
  {
    v |= (ReadOneWire(pin,address_Reset,address_Reg) << i);
  }
  return v;
}

void ReadnBytes(unsigned int* buff, unsigned int n,unsigned int pin, uint32_t *address_Reset,  uint32_t * address_Reg)
{
  unsigned int i;
  for(i= 0; i<n; i++)
  {
    buff[i] = ReadByte(pin, address_Reset,address_Reg);
  }
}

unsigned int crcCheck(unsigned int n, unsigned int *tab)
{
	unsigned int multiple, remainder;

	remainder = 0;
	multiple = 0;

	for (unsigned int i = 0; i < n; i++) 
	{
         remainder ^= tab[i];
		for (unsigned int j = 0; j < 8; j++) 
		{
			multiple = (remainder & 1) ? 0x8c : 0;
			remainder = (remainder >> 1) ^ multiple;
        }
	}
	return remainder;
}


void fun(void * p)
{
	
}
