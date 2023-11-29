cmake_minimum_required(VERSION 3.16)

project(win32_title_bar LANGUAGES CXX C)

add_executable(win32_title_bar main.cpp)

set_target_properties(win32_title_bar PROPERTIES 
    WIN32_EXECUTABLE TRUE
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_compile_definitions(win32_title_bar
    PRIVATE UNICODE _UNICODE
)

target_include_directories(win32_title_bar PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(win32_title_bar PRIVATE uxtheme)
