#pragma once

#include "strs.hpp"

#include <iostream>
#include <string>

struct Arguments {
    char* File;
    char* Path; 
    uint32_t PLen = 0;
    bool Print = false;
    uint32_t Stats = 10;
    uint32_t Window = 0;
    uint64_t STime = 0;
    uint64_t ETime = 1000000000000;
};

void compareLongFlag(char* token, char* arg, Arguments& args);
void compareFlag(char* token, char* arg, Arguments& args);
void parseLongFlag(char* token, Arguments& args);
bool parseFlag(char* token, Arguments& args);
void parseArgs(int argc, char** argv, Arguments& args);
