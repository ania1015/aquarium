#include "stdint.h"

#ifndef READINGWRITING_H
#define READINGWRITING_H

static inline uint32_t ReadPort(uint32_t* address)
{
        return  *(volatile uint32_t *) address;
}

static inline unsigned int ReadPin(uint32_t* address, unsigned int pin)
{
        return ((ReadPort(address) & (1 << pin)) != 0);
}

static inline void WritePin(uint32_t* address, uint32_t value)
{
        *(volatile uint32_t *) address = value;
}

#endif
