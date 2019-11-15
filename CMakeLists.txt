cmake_minimum_required(VERSION 3.0)

project(sn C)

add_executable(sn app/main.c)

target_include_directories(sn PRIVATE include)
target_compile_options(sn PRIVATE -Wall -O2)


set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
