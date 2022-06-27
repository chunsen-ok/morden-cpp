cmake_minimum_required(VERSION 3.20)

project(CleanApp LANGUAGES CXX)

add_executable(CleanApp
    src/main.cpp
)

set_target_properties(CleanApp PROPERTIES 
    DEBUG_POSTFIX d
)
