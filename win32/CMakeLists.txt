cmake_minimum_required(VERSION 3.16)

project(win32 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(win32 
    src/main.cpp
    src/window_state.hpp
    src/window_state.cpp
)

set_target_properties(win32 PROPERTIES 
    WIN32_EXECUTABLE TRUE
)

target_compile_definitions(win32
    PRIVATE UNICODE _UNICODE
)

target_link_libraries(win32 PRIVATE Dwmapi)
