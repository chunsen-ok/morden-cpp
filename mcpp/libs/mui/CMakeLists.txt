cmake_minimum_required(VERSION 3.16)

project(mui)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/..")

add_library(mui
    # point.hpp
    # size.hpp
    # size.cpp
    # size_policy.hpp
    # size_policy.cpp
    property.hpp
    # object.hpp
    # widget.hpp
    # widget.cpp
    # application.hpp
)

target_include_directories(mui
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
