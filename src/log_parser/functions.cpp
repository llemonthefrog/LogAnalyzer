#include "args_struct.hpp"
#include "log_parser.hpp"
#include "time_stamp.hpp"
#include "error_logs.hpp"

#include <fstream>

const uint32_t BUF_SIZE = 1024; 

enum Lengths {
    minLog = 50,
    code = 3 + 1,
    rawTime = 26 + 1,
};

uint32_t analyzeFifths(const Arguments& args) {
    std::ifstream inputStream;
    std::ofstream outputStream;

    inputStream.open(args.File);
    outputStream.open(args.Path);

    if((!inputStream.is_open()) || (!outputStream.is_open())) {
        std::cerr << "[ERROR] error while opening file\n";
        exit(1);
    }

    char buf[BUF_SIZE];
    uint32_t fifLogCounter = 0;

    while(!inputStream.eof()) {
        inputStream.getline(buf, BUF_SIZE);
        uint32_t size = inputStream.gcount();
        buf[size] = '\0';

        if(size > Lengths::minLog) {
            char rawLog[size + 1];
            copyStrs(&buf[0], &rawLog[0]);

            char rawTime[Lengths::rawTime];
            uint32_t i = 0;
            for(; rawLog[i] != '\0'; i++) {
                if(rawLog[i] == '[') {
                    break;
                }
            }

            getSubStr(rawLog, &rawTime[0], i + 1, Lengths::rawTime - 1);

            char code[Lengths::rawTime];
            i = size;
            for(; i > 0; i--) {
                if(rawLog[i] == ' ') {
                    break;
                }
            }
            
            getSubStr(rawLog, &code[0], i - 3, 3);

            uint64_t time = GetTimestamp(&rawTime[0]);
            if(args.STime < time && time < args.ETime) {
                if(code[0] == '5') {
                    outputStream << rawLog << "\n";
                    fifLogCounter++;

                    if(args.Print == true) {
                        std::cout << rawLog << "\n"; 
                    }
                }
            } else if (time > args.ETime){
                break;
            }
        }
    }

    outputStream.close();
    inputStream.close();

    return fifLogCounter;
}


uint32_t AddErrors(ErrorLog* logs, const Arguments& args, const uint32_t size) {
    std::ifstream inputStream;
    inputStream.open(args.Path);

    if(!inputStream.is_open()) {
        std::cerr << "[ERROR] error while opening file\n";
        exit(1);
    }

    uint32_t entries = 0;
    char buf[BUF_SIZE];
    uint32_t counters = 0;
        
    while(!inputStream.eof() && counters < size) {
        inputStream.getline(buf, BUF_SIZE);
        uint32_t size = inputStream.gcount();
        buf[size] = '\0';

        uint32_t len = 0;
        uint32_t index = 0;
        uint32_t count = 0;
        for(int i = 0; i < size; i++) {
            if(buf[i] == '"') {
                count++;
            }

            if(count == 0) {
                index++;
            } else if(count == 1) {
                len++;
            } else {
                break;
            }
        }


        char request[len];
        getSubStr(&buf[0], &request[0], index, len + 1);

        addOrUpdateString(&request[0], logs, entries, args);
        counters++;
    }
    
    inputStream.close();
    return entries;
}

void getStatsForFifths(ErrorLog* logs, const Arguments& args, const uint32_t size) {
    if(size <= 0) {
        return;
    }

    for(uint32_t i = 1; i < size; i++) {
        ErrorLog elem = logs[i];

        int j = i - 1;
        for(;j >= 0 && elem.Count < logs[j].Count; j--) {
                logs[j + 1] = logs[j];
        }

        logs[j + 1] = elem;
    }   

    std::cout << "\n";
    std::cout << "[5XX stats]:\n\n";

    for(uint32_t i = size - 1, counter = 0; i > 0 && counter < args.Stats; i--) {
        if(logs[i].Count == 0 && logs[i].Request[0] != '\n') {
            continue;
        }

        std::cout << "*  " << logs[i].Request << " - "  << logs[i].Count << " request(s)\n";
        counter++;
    }

    std::cout << "\n";
}


void fLongestPeriod(const Arguments& args) {
    std::ifstream input(args.File);

    if (!input.is_open()) {
        std::cerr << "[ERROR] error while opening file\n";
        exit(1);
    }

    uint32_t max = 0;
    uint64_t startTime = 0;
    uint64_t endTime = 0;

    char charBuf[BUF_SIZE];
    uint64_t buf[BUF_SIZE];
    uint32_t count = 0;

    while (count < BUF_SIZE && input.getline(charBuf, BUF_SIZE)) {
        uint32_t i = 0;
        while (charBuf[i] != '\0') {
            if (charBuf[i] == '[') {
                break;
            }
            i++;
        }

        char rawTime[Lengths::rawTime];
        getSubStr(&charBuf[i + 1], &rawTime[0], 0, Lengths::rawTime - 1);
        uint64_t timestamp = GetTimestamp(&rawTime[0]);

        if (timestamp >= args.STime && timestamp <= args.ETime) {
            buf[count] = timestamp;
            count++;
        }
    }

    while (input.getline(charBuf, BUF_SIZE)) {
        uint32_t i = 0;
        while (charBuf[i] != '\0') {
            if (charBuf[i] == '[') {
                break;
            }
            i++;
        }

        char rawTime[Lengths::rawTime];
        getSubStr(&charBuf[i + 1], &rawTime[0], 0, Lengths::rawTime - 1);
        uint64_t elem = GetTimestamp(&rawTime[0]);

        if (elem >= args.STime && elem <= args.ETime) {
            for(uint32_t j = 1; j < BUF_SIZE; j++) {
                buf[j - 1] = buf[j];
            }
            buf[BUF_SIZE - 1] = elem;

            uint32_t currentLength = 1;
            while (currentLength < BUF_SIZE && buf[0] + (args.Window - 1) >= buf[currentLength]) {
                currentLength++;
            }

            if (currentLength > max) {
                max = currentLength;
                startTime = buf[0];
                endTime = buf[currentLength - 1];
            }
        }
    }

    std::cout << "\n";
    std::cout << "[Maximum requests in window]:\n\n";
    std::cout << "for window: " << args.Window << "\n";
    std::cout << "from " << startTime << " to " << endTime << " maximum will be: " << max;
    std::cout << "\n\n";

}
