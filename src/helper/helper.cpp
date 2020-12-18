#include <stdlib.h>
#include <iostream>
#include "helper.h"

unsigned char* u32_to_u8(uint32_t value) {
    unsigned char* result = (unsigned char*)calloc(4, sizeof(unsigned char));
    for(int i = 0; i<4; i++) {
        result[i] = (value & (0xff << (3 - i)*8)) >> (3 - i)*8;
    }
    return result;
}

unsigned char* u64_to_u8(uint64_t value) {
    unsigned char* result = (unsigned char*)calloc(8, sizeof(unsigned char));
    for(int i = 0; i<8; i++) {
        result[i] = (value & (0xff << (3 - i)*8)) >> (3 - i)*8;
    }
    return result;
}

uint32_t u8_to_u32(unsigned char* value) {
    uint32_t result = 0;
    result = result | (value[0] << 24);
    result = result | (value[1] << 16);
    result = result | (value[2] << 8);
    result = result | value[3];
    return result;
}

uint64_t u8_to_u64(unsigned char* value) {
    uint64_t result = 0;
    for(int i = 0; i<8; i++) {
        result = result | (value[i] << (3 - i)*8);
    }
    return result;
}

uint32_t toggleEndianess(uint32_t value) {
    unsigned char* aob = u32_to_u8(value);
    for(int i = 0; i<2; i++) {
        unsigned char temp = aob[i];
        aob[i] = aob[3-i];
        aob[3-i] = temp;
    }
    uint32_t result = u8_to_u32(aob);
    free(aob);
    return result;
}

uint64_t toggleEndianess(uint64_t value) {
    unsigned char* aob = u64_to_u8(value);
    for(int i = 0; i<4; i++) {
        unsigned char temp = aob[i];
        aob[i] = aob[7-i];
        aob[7-i] = temp;
    }
    uint64_t result = u8_to_u64(aob);
    free(aob);
    return result;
}

void printUINT32(uint32_t v) {
    unsigned char* values = u32_to_u8(v);
    std::cout << (unsigned int)values[0] << " " << (unsigned int)values[1] << " " << (unsigned int)values[2] << " " << (unsigned int)values[3] << std::endl;
}