cmake_minimum_required(VERSION 3.8)
project(dp)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_SH CMAKE_SH-NOTFOUND)
# 设置运行目录为当前目录，否则会在 子目录内，导致读取和输出需要设置相对路径
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_definitions(-DLOCAL)
#add_definitions(-std=c++98)
set(SOURCE_FILES lis_recursive.cpp)
add_executable(dp ${SOURCE_FILES})
