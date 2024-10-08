#include "args_struct.hpp"

struct Arguments{
    char* File;
    char* Path; 
    uint32_t PLen = 0;
    bool Print = false;
    uint32_t Stats = 10;
    uint32_t Window = 0;
    uint64_t STime = 0;
    uint64_t ETime = 1000000000000;
};