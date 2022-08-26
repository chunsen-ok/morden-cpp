cmake_minimum_required(VERSION 3.20)

project(Calculator LANGUAGES CXX)

# set(CMAKE_C_STANDARD 11)
# set(CMAKE_C_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(calc STATIC 
    src/calc.cpp 
    include/calc/lib.hpp
)
target_include_directories(calc PUBLIC include)
target_compile_features(calc PUBLIC cxx_std_17)

add_executable(calculator
    app/main.cpp
)
target_link_libraries(calculator PUBLIC calc)

# 变量
set(MY_VARIABLE "value")

# 列表
set(MY_LIST0 "a b c")
set(MY_LIST1 "a;b;c")
