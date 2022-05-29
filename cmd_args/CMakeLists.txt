cmake_minimum_required(VERSION 3.20)

project(cmd_args LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(cmd_args
    src/main.cpp
)
