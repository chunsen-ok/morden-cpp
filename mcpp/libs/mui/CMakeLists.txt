cmake_minimum_required(VERSION 3.16)

project(mui)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/..")

include(ExternalProject)
include(FetchContent)

# downloads at build time
# ExternalProject_Add(glfw
#     GIT_REPOSITORY "https://gitee.com/blusque/glfw.git"
#     GIT_TAG        "3.3.4"
# )

# FetchContent
FetchContent_Declare(
    glfw
    GIT_REPOSITORY "https://gitee.com/blusque/glfw.git"
    GIT_TAG        "3.3.4"
)
FetchContent_MakeAvailable(glfw)

add_library(mui
    glad/glad.c
    glad/glad.h
    glad/KHR/khrplatform.h
    point.hpp
    size.hpp
    # size.cpp
    size_policy.hpp
    # size_policy.cpp
    property.hpp
    property.cpp
    object.hpp
    object.cpp
    widget.hpp
    widget.cpp
    application.hpp
    application.cpp
)

target_include_directories(mui
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(mui PRIVATE glfw)