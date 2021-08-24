cmake_minimum_required(VERSION 3.16)

project(mcpp)

add_subdirectory(libs/bigint)

add_executable(mcpp src/main.cpp)
