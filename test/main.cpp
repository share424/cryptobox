#include <iostream>
#include <bitset>
#include <sstream>
#include <math.h>
#include "../src/hash/hash.h"

using namespace std;

string to_binary(unsigned char c) {
    unsigned int a = (int)c;
    if(c == 0) {
        return "0000 0000";
    }
    ostringstream result;
    unsigned int idx = 0;
    while(a != 0) {
        int remainder = a % 2;
        // unsigned int b = a;
        a = floor(a / 2);
        // cout << b << ":2 = " << a << " + " << remainder << endl;
        result << remainder;
        if(++idx == 4) {
            result << " ";
        }
    }
    int le = result.str().length();
    for(int i = 0; i<9-le; i++) {
        result << 0;
        if(++idx == 4) {
            result << " ";
        }
    }
    string output = result.str();
    ostringstream s;
    for(int i = output.length() - 1; i>=0; i--) {
        s << output[i];
    }
    return s.str();
}

int main() {
    string input = "aaaa";
    unsigned char* b = Hash::MD5(input);
    for(int i=0; i<16; ++i) {
        std::cout << std::hex << (int)b[i] << " ";
    }
    cout << endl;
    return 0;
}