cmake_minimum_required(VERSION 3.16)

project(bigint)

add_library(bigint
    bigint.hpp bigint.cpp
)

target_include_directories(bigint
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
