cmake_minimum_required(VERSION 3.16)
project(SmartPtr)
set(CMAKE_CXX_STANDARD 20)

add_executable(SmartPtr src/main.cpp)
target_include_directories(SmartPtr PRIVATE include)