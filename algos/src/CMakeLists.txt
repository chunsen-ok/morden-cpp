cmake_minimum_required(VERSION 3.20)

project(algos LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/../build/${CMAKE_BUILD_TYPE}")

add_library(algos INTERFACE 
    sort.hpp
)

install(FILES
    sort.hpp
    DESTINATION "include/algos"
)
