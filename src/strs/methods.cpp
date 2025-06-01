#include "strs.hpp"

uint32_t length(const char* str) {
    uint32_t count = 0;
    while(str[count] != '\0') {
        count++;
    }

    return count;
}

void getSubStr(const char* strInput, char* strOutput, uint32_t index, uint32_t length) {
    uint32_t j = 0;
    for(uint32_t i = index; j < length; ++i, ++j) {
        strOutput[j] = strInput[i];
    }
    strOutput[j] = '\0';
}


bool compareStrings(const char* str1, const char* str2) {
    uint32_t i = 0;
    uint32_t j = 0;
    while(str1[i] != '\0' || str2[j] != '\0') {
        if(str1[i] != str2[j]) {
            return false;
        }
        i++;
        j++;
    }

    if(i - length(str1) == 0 && j - length(str2) == 0) {
        return true;
    }
    
    return false;
}

bool CompareStringsInErrors(const char* string1, const char* string2) {
    int i = 0;
    while (string1[i] != '\0' && string2[i] != '\0') {
        if (string1[i] != string2[i]) {
            return false;
        }
        ++i;
    }
    return string1[i] == '\0' && string2[i] == '\0';
}

uint32_t StringToUint(const char* str) {
    uint32_t number = 0;
    uint32_t len = length(str);
    for(int i = 0; i < len; i++) {
        char c = str[i];
        if(c >= '0' && c <= '9') {
            number = number * 10 + (c - '0');
        }
    }
    return number;
}


void copyStrs(char* strInput, char* strOutput) {
    uint32_t j = 0;
    while(strInput[j] != '\0') {
        strOutput[j] = strInput[j];
        j++;
    }
    strOutput[j++] = '\0';
}
