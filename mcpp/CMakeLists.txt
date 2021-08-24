cmake_minimum_required(VERSION 3.16)

project(mcpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/..")

add_subdirectory(libs/bigint)
add_executable(mcpp src/main.cpp)
target_link_libraries(mcpp bigint)

install(
    TARGETS mcpp
    DESTINATION "bin"
)
