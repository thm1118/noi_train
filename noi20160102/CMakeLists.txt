cmake_minimum_required(VERSION 3.8)
project(noi20160102)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_SH CMAKE_SH-NOTFOUND)
# 设置运行目录为当前目录，否则会在 子目录内，导致读取和输出需要设置相对路径
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCE_FILES main.cpp)
add_executable(noi20160102 ${SOURCE_FILES})