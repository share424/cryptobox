/**
 * Author: share424
 * 
 * src: https://en.wikipedia.org/wiki/MD5 
 * 
**/

#include <stdlib.h>
#include <cstring>
#include <math.h>
#include <iostream>
#include "hash.h"

namespace Hash {

    const uint32_t s[64] = { 
        7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22, 
        5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
        4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
        6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21 
    };

    const uint32_t K[64] = {
        0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
        0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
        0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
        0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
        0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
        0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
        0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
        0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
        0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
        0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
        0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
        0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
        0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
        0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
        0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
        0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
    };

    uint32_t leftrotate(uint32_t x, uint32_t c) {
        return (x << c) | (x >> (32-c));
    }

    unsigned char* MD5(const std::string input) {
        return MD5(input.c_str(), input.length());
    }

    unsigned char* MD5(const char* input, uint64_t length) {
        unsigned char* input_message;
        // input message length in bit must be congruent to 0 (mod 512)
        // char is 8 bit
        uint32_t m = (length) % 64;
        uint32_t leftover = 64 - m;
        input_message = (unsigned char*)calloc(length + leftover, sizeof(unsigned char));
        memcpy(input_message, input, length);
        uint32_t total_length = length + leftover;
        // append '1' bit
        input_message[length] = 0x80; // 1000 0000

        // append message length
        uint64_t message_bit_length = toggleEndianess(length*8);
        unsigned char* length_array = u64_to_u8(message_bit_length);
        for(unsigned int i = (total_length-8); i<total_length; i++) {
            input_message[i] = length_array[i - (total_length - 8)];
        }
        
        // initialize variables
        uint32_t a0 = 0x67452301;
        uint32_t b0 = 0xefcdab89;
        uint32_t c0 = 0x98badcfe;
        uint32_t d0 = 0x10325476;
        
        for(int k = 0; k<floor(total_length/64); k++) {
            uint32_t A = a0;
            uint32_t B = b0;
            uint32_t C = c0;
            uint32_t D = d0;
            // break into 16 chunk
            uint32_t M[16];
            for(int j = 0; j<16; j++) {
                unsigned char* buffer = (unsigned char*)calloc(4, sizeof(unsigned char));
                buffer[0] = input_message[k*64 + j*4];
                buffer[1] = input_message[k*64 + j*4 + 1];
                buffer[2] = input_message[k*64 + j*4 + 2];
                buffer[3] = input_message[k*64 + j*4 + 3];
                M[j] = u8_to_u32(buffer);
            }


            for(int i = 0; i<64; i++) {
                uint32_t F = 0;
                uint32_t g = 0;
                if(i < 16) {
                    F = (B & C) | ((~B) & D);
                    g = i;
                } else if(i < 32) {
                    F = (D & B) | ((~D) & C);
                    g = (5*i + 1) % 16;
                } else if(i < 48) {
                    F = B ^ C ^ D;
                    g = (3*i + 5) % 16;
                } else {
                    F = C ^ (B | (~D));
                    g = (7*i) % 16;
                }
                
                uint32_t mg = toggleEndianess(M[g]);
                F = F + A + K[i] + mg;
                A = D;
                D = C;
                C = B;
                B = B + leftrotate(F, s[i]);
                
            }
            a0 = a0 + A;
            b0 = b0 + B;
            c0 = c0 + C;
            d0 = d0 + D;
        }

        a0 = toggleEndianess(a0);
        b0 = toggleEndianess(b0);
        c0 = toggleEndianess(c0);
        d0 = toggleEndianess(d0);
        unsigned char* a_ = u32_to_u8(a0);
        unsigned char* b_ = u32_to_u8(b0);
        unsigned char* c_ = u32_to_u8(c0);
        unsigned char* d_ = u32_to_u8(d0);
        
        unsigned char* results = (unsigned char*)calloc(16, sizeof(unsigned char));
        for(int i = 0; i<4; i++) {
            results[i] = a_[i];
            results[4+i] = b_[i];
            results[8+i] = c_[i];
            results[12+i] = d_[i];
        }

        return results;

    }
}