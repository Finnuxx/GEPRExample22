cmake_minimum_required(VERSION 3.16)
project(GEPRExample22)

set(CMAKE_EXE_LINKER_FLAGS "-static")
set(CMAKE_CXX_STANDARD 14)

add_executable(GEPRExample22 main.cpp)