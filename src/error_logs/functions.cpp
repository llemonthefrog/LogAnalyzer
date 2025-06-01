#include "error_logs.hpp"

void init(const char* inputString, ErrorLog& err) {
    int i = 0;
    
    for (i = 0; i < 256 - 1 && inputString[i] != '\0'; ++i) {
        err.Request[i] = inputString[i];
    }

    err.Request[i] = '\0';
    err.Count = 1;
}

void addOrUpdateString(const char* newStr, ErrorLog* logs, uint32_t& entr, const Arguments& args) {
    for (uint32_t i = 0; i < entr; ++i) {
        if (CompareStringsInErrors(newStr, logs[i].Request)) {
            logs[i].Count++;
            return;
        }
    }

    ErrorLog err;
    init(newStr, err);
    logs[entr] = err;
    entr++;
}
