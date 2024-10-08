#include <iostream>

#include "strs.hpp"
#include "args_struct.hpp"
#include "log_parser.hpp"
#include "error_logs.hpp"

int main(int argc, char *argv[]){
    char path[256];

    Arguments args;
    args.Path = &path[0];
    parseArgs(argc, argv, args);

    if(args.PLen > 0) {
        uint32_t sizeOfStats = analyzeFifths(args);
        if (sizeOfStats > 0) {
            ErrorLog buf[sizeOfStats];
            uint32_t size = AddErrors(&buf[0], args, sizeOfStats);
            getStatsForFifths(&buf[0], args, size);
        }
    }

    if(args.Window > 0) {
        fLongestPeriod(args);
    }
}
