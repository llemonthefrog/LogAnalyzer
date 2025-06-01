cmake_minimum_required(VERSION 3.10)
project(LOGANALYZER)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES
    src/args_struct/*.cpp
    src/error_logs/*.cpp
    src/log_parser/*.cpp
    src/strs/*.cpp
    src/time_stamp/*.cpp
    src/main.cpp
)

include_directories(
    src/args_struct
    src/error_logs
    src/log_parser
    src/strs
    src/time_stamp
)

add_executable(${PROJECT_NAME} ${SOURCES})
