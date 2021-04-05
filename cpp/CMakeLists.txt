cmake_minimum_required(VERSION 3.15)

project(cpp_base)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/..")

add_executable(cpp_base
    main.cpp
)

install(
    TARGETS cpp_base
    DESTINATION "bin"
)
