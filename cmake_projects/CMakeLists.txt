cmake_minimum_required(VERSION 3.20)

project(CMakeProjects LANGUAGES CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(CMakeProjects
    src/main.cpp
)

add_custom_target(rcc
    COMMAND ${CMAKE_COMMAND} -E echo_append "Hello, world!"
)
