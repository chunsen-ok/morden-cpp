cmake_minimum_required(VERSION 3.16)

project(fp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/../dist")
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../algos/build/Debug")

find_package(algos)

add_executable(fp main.cpp)

target_link_libraries(fp 
    PRIVATE mcpp::algos
)

install(
    TARGETS fp
    DESTINATION "bin"
)
