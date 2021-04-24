cmake_minimum_required(VERSION 3.15)

project(cpp_base)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/..")

add_executable(fold_expression
    fold_expression.cpp
)

install(
    TARGETS fold_expression
    DESTINATION "bin"
)
