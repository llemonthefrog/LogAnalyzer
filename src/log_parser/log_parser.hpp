#pragma once

#include "time_stamp.hpp"
#include "error_logs.hpp"
#include "args_struct.hpp"

constexpr uint32_t BUF_SIZE = 1024; 

enum Lengths {
    minLog = 50,
    code = 3 + 1,
    rawTime = 26 + 1,
};

uint32_t analyzeFifths(const Arguments& args);
uint32_t AddErrors(ErrorLog* logs, const Arguments& args, const uint32_t size);
void getStatsForFifths(ErrorLog* logs, const Arguments& args, const uint32_t size);
void fLongestPeriod(const Arguments& args);
