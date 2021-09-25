cmake_minimum_required(VERSION 3.16)

project(fp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/../dist")

add_executable(fp main.cpp)

install(
    TARGETS fp
    DESTINATION "bin"
)
