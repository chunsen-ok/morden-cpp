cmake_minimum_required(VERSION 3.20)

project(cpp20 VERSION 0.1.0 LANGUAGES CXX)

add_executable(cpp20 
    src/main.cpp
)
target_compile_features(cpp20 PRIVATE cxx_std_20)
