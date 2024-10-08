cmake_minimum_required(VERSION 3.10.0)
project(labwork1 VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_COMPILER clang++)

add_executable(AnalyzeLog src/main.cpp)
target_include_directories(AnalyzeLog PUBLIC "${PROJECT_SOURCE_DIR}/src/log_parser")
target_include_directories(AnalyzeLog PUBLIC "${PROJECT_SOURCE_DIR}/src/args_struct_new")
target_include_directories(AnalyzeLog PUBLIC "${PROJECT_SOURCE_DIR}/src/statistic_struct")
target_include_directories(AnalyzeLog PUBLIC "${PROJECT_SOURCE_DIR}/src/strs")
target_include_directories(AnalyzeLog PUBLIC "${PROJECT_SOURCE_DIR}/src/time_stamp")
target_include_directories(AnalyzeLog PUBLIC "${PROJECT_SOURCE_DIR}/src/error_logs")