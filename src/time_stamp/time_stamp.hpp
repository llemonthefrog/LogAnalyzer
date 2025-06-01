#pragma once

#include "strs.hpp"
#include <cinttypes>

enum TimeLengths {
    //подразумевается, что входит строка "03/Jul/1995:10:55:30 -0400"
    dateL = 2,
    monthL = 3, 
    yearL = 4,
    hourL = 2,
    minuteL = 2,
    secondL = 2,
    timeZoneL = 3,
};

enum IndexedTime {
    //подразумевается, что входит строка "03/Jul/1995:10:55:30 -0400"
    date = 0,
    month = 3,
    year = 7,
    hour = 12,
    minute = 15,
    second = 18,
    timeZone = 21,
};

bool isLeap(uint32_t year);
uint32_t getMonthIndex(char *month);
uint32_t daysInMonth(uint32_t year, uint32_t month);
uint64_t GetTimestamp(char* timeString);
