cmake_minimum_required(VERSION 3.16)

project(mcpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/../dist")

add_subdirectory(libs/bigint)
add_subdirectory(libs/mui)
add_subdirectory(libs/reactive)
add_subdirectory(libs/events)

add_executable(mcpp
    src/main.cpp
)

target_link_libraries(mcpp
    PRIVATE
        bigint
        mevents
        reactive
        mui
)

install(
    TARGETS mcpp
    DESTINATION "bin"
)

# Tests ...
add_subdirectory(tests/reactive_test)

enable_testing()

add_test(NAME reactive_test COMMAND reactive_test)
