cmake_minimum_required(VERSION 3.16)

project(reactive_test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/..")

add_executable(reactive_test
    main.cpp
)
target_link_libraries(reactive_test PRIVATE reactive)
