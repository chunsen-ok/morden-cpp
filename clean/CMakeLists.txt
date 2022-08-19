cmake_minimum_required(VERSION 3.20)

project(CleanApp LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(CleanApp
    src/main.cpp
    src/chat.hpp
)

