cmake_minimum_required(VERSION 3.16)

project(mui LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/../dist")

add_executable(mui 
    main.cpp
    domain/data.hpp
    common/types.hpp
)

install(
    TARGETS mui
    DESTINATION "bin"
)
