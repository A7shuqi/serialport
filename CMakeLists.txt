cmake_minimum_required(VERSION 3.0.0)
project(serialport VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(serialport main.cpp sport.h sport.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
