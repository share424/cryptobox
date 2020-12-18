#ifndef HELPER_H
#define HELPER_H

#include <stdint.h>


unsigned char* u32_to_u8(uint32_t value);
unsigned char* u64_to_u8(uint64_t value);
uint32_t u8_to_u32(unsigned char* value);
uint64_t u8_to_u64(unsigned char* value);
uint32_t toggleEndianess(uint32_t value);
uint64_t toggleEndianess(uint64_t value);
void printUINT32(uint32_t v);


#endif