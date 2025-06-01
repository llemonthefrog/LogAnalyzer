#pragma once

#include "strs.hpp"
#include "args_struct.hpp"

struct ErrorLog {
    char Request[256];
    uint32_t Count;
};

void init(const char* inputString, ErrorLog& err);
void addOrUpdateString(const char* newStr, ErrorLog* logs, uint32_t& entr, const Arguments& args);
