cmake_minimum_required(VERSION 3.15)

project(leetcode)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/..")

add_executable(leetcode
    main.cpp
    leetcode.hpp
)

install(TARGETS leetcode
    DESTINATION "bin"
)