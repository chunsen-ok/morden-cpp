cmake_minimum_required(VERSION 3.16)

project(play-win32 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/../dist")
set(CMAKE_CXX_FLAGS -municode)

add_executable(play-win32 main.cpp)

install(
    TARGETS play-win32
    DESTINATION "bin"
)
