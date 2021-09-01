cmake_minimum_required(VERSION 3.15)

project(dep LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/../dist")

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

add_executable(dep
    main.cpp
    glad/glad.c
    glad/glad.h
    glad/KHR/khrplatform.h
)
target_link_libraries(dep PRIVATE glfw)

install(
    TARGETS dep
    DESTINATION "bin"
)
