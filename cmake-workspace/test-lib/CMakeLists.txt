cmake_minimum_required(VERSION 3.20)

project(test-lib)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(test
    src/main.cpp
)

file(GENERATE OUTPUT gen_expr.txt CONTENT "$<TARGET_FILE:test>")
