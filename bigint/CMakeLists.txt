cmake_minimum_required(VERSION 3.15)

project(bigint LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/..")

add_executable(bigint
    main.cpp
    bigint.hpp
)

install(
    TARGETS bigint
    DESTINATION "bin"
)
