#pragma once

#include <cinttypes>

uint32_t length(const char* str);
void getSubStr(const char* strInput, char* strOutput, uint32_t index, uint32_t length);
bool compareStrings(const char* str1, const char* str2);
bool CompareStringsInErrors(const char* string1, const char* string2);
uint32_t StringToUint(const char* str);
void copyStrs(char* strInput, char* strOutput);
