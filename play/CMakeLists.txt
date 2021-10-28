cmake_minimum_required(VERSION 3.16)

project(play LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/../dist")

add_executable(play
    main.cpp
    helper.hpp
    sort_by_multi_fields.hpp
    reverse_iterator.hpp
)

install(
    TARGETS play
    DESTINATION "bin"
)
