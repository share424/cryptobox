#ifndef HASH_H
#define HASH_H

#include <stdint.h>
#include <iostream>
#include "../helper/helper.h"

namespace Hash {
    unsigned char* MD5(const char* input, uint64_t length);
    unsigned char* MD5(const std::string input);
}

#endif