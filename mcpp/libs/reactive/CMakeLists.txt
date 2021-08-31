cmake_minimum_required(VERSION 3.15)

project(reactive)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/..")

add_library(reactive
    reactive.hpp
    observable.hpp
    event.hpp
    event_pool.hpp
    event_pool.cpp
    private/event_pool_p.hpp
    private/event_pool_p.cpp
)

target_include_directories(reactive
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
