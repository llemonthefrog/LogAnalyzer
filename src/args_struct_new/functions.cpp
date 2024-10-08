#include "args_struct.hpp"
#include "strs.hpp"
#include <iostream>

void compareLongFlag(char* token, char* arg, Arguments& args) {
    if(compareStrings(token, "--output")) {
        int i = 0;
        for(; i < length(arg); i++) {
            args.Path[i] = arg[i];
        }

        args.Path[i] = '\0';
        args.PLen = i++;
    } else if(compareStrings(token, "--stats")) {
        args.Stats = StringToUint(arg);
    } else if(compareStrings(token, "--window")) {
        args.Window = StringToUint(arg);
    } else if(compareStrings(token, "--from")) {
        args.STime = StringToUint(arg);
    } else if(compareStrings(token, "--to")) {
        args.ETime = StringToUint(arg);
    } else if(compareStrings(token, "--print")) {
        args.Print = true;
    } else {
        std::cout << "[FATAL] provided incorrect flag\n";
        exit(1);
    }
}

void compareFlag(char* token, char* arg, Arguments& args) {
    if(compareStrings(token, "-o")) {
        int i = 0;
        for(; i < length(arg); i++) {
            args.Path[i] = arg[i];
        }

        args.Path[i] = '\0';
        args.PLen = i++;
    } else if(compareStrings(token, "-s")) {
        args.Stats = StringToUint(arg);
    } else if(compareStrings(token, "-w")) {
        args.Window = StringToUint(arg);
    } else if(compareStrings(token, "-f")) {
        args.STime = StringToUint(arg);
    } else if(compareStrings(token, "-e")) {
        args.ETime = StringToUint(arg);
    } else {
        std::cout << "[FATAL] provided incorrect flag\n";
        exit(1);
    }
}

void parseLongFlag(char* token, Arguments& args) {
    uint32_t tokenLength = length(token);

    int32_t len = 0;
    for(int i = 0; i < tokenLength; i++) {
        if(token[i] != '=') {
            len++;
        } else if(token[i] == '=') {
            break;
        }
    }

    int argLength = tokenLength - len + 1;
    if (argLength > 0) {
        char arg[argLength];
        getSubStr(token, &arg[0], len + 1, tokenLength - len);
        arg[argLength - 1] = '\0';
        
        char subToken[len + 1];
        getSubStr(token, &subToken[0], 0, len);
        subToken[len] = '\0';

        compareLongFlag(&subToken[0], &arg[0], args);
    } else {
        char arg[1];
        compareLongFlag(token, &arg[0], args);
    }


}

bool parseFlag(char* token, Arguments& args){
    if(token[1] == 'p') {
        args.Print = true;
        return false;
    }
        
    return true;
}


void parseArgs(int argc, char** argv, Arguments& args) {

    bool skipNext = false;
    for(int i = 1; i < argc; i++) {
        if(!skipNext) {
            char* token = argv[i];

            if(token[0] == '-' && token[1] == '-') {
                parseLongFlag(token, args);
            } else if(token[0] == '-') {
                skipNext = parseFlag(token, args);
            } else {
                args.File = token;
            }

        } else {
            compareFlag(argv[i - 1], argv[i], args);

            skipNext = false;
        }
    }

}