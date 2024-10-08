#include "time_stamp.hpp"
#include "strs.hpp"

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

bool isLeap(uint32_t year) {
    if (year % 4 == 0) {
        if (year % 100 == 0) {
            return year % 400 == 0;
        }
        return true;
    }
    return false;
}

uint32_t getMonthIndex(char *month) {
    const char* months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    for (uint32_t i = 0; i < 12; ++i) {
        if (compareStrings(months[i], month)) {
            return i + 1;
        }
    }

    return 0;
}

uint32_t daysInMonth(uint32_t year, uint32_t month) {
    const uint32_t daysPerMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && isLeap(year)) {
        return 29;
    }
    return daysPerMonth[month - 1];
}

uint64_t GetTimestamp(char* timeString) {
    //подразумевается, что входит строка "03/Jul/1995:10:55:30 -0400"
    
    char dateStr[3] = "";
    getSubStr(timeString, dateStr, IndexedTime::date, TimeLengths::dateL); 
    char monthStr[4] = "";
    getSubStr(timeString, monthStr, IndexedTime::month, TimeLengths::monthL);
    char yearStr[5] = "";
    getSubStr(timeString, yearStr, IndexedTime::year, TimeLengths::yearL);
    char hour[3] = "";
    getSubStr(timeString, hour, IndexedTime::hour, TimeLengths::hourL);
    char minute[3] = "";
    getSubStr(timeString, minute, IndexedTime::minute, TimeLengths::minuteL);
    char second[3] = "";
    getSubStr(timeString, second, IndexedTime::second, TimeLengths::secondL);
    char timeZone[4] = "";
    getSubStr(timeString, timeZone, IndexedTime::timeZone, TimeLengths::timeZoneL);

    uint32_t month = getMonthIndex(monthStr);

    uint64_t days = 0;

    for (uint32_t y = 1970; y < StringToUint(yearStr); ++y) {
        days += isLeap(y) ? 366 : 365;
    }

    for (uint32_t m = 1; m < month; ++m) {
        days += daysInMonth(StringToUint(yearStr), m);
    }

    days += StringToUint(dateStr) - 1;

    uint64_t seconds = days * 24 * 3600;
    seconds += StringToUint(hour) * 3600;
    seconds += StringToUint(minute) * 60;
    seconds += StringToUint(second);

    timeZone[0] == '-' ? seconds -= StringToUint(timeZone) * 3600 : seconds += StringToUint(timeZone) * 3600;

    return seconds;
}