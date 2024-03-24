#include "stdint.h"
#include "ReadingWriting.h"

#ifndef ONEWIRE_H
#define ONEWIRE_H

unsigned int OneWireInitialization(unsigned int pin, uint32_t *address_Reset, uint32_t * address_Reg);
void WriteOne_OneWire(unsigned int pin, uint32_t *address);
void WriteZero_Onewire( unsigned int pin, uint32_t *address);
unsigned int ReadOneWire(unsigned int pin, uint32_t *address_Reset, uint32_t * address_Reg);

void WriteBit(unsigned int bit, unsigned int pin, uint32_t *address_Reset);
void WriteByte(unsigned int byte, unsigned int pin, uint32_t *address_Reset);
unsigned int ReadByte(unsigned int pin, uint32_t *address_Reset,  uint32_t * address_Reg);
void ReadnBytes(unsigned int* buff, unsigned int n,unsigned int pin, uint32_t *address_Reset,  uint32_t * address_Reg);
unsigned int crcCheck(unsigned int n, unsigned int *tab);
void fun(void * p);

#endif
