cmake_minimum_required(VERSION 3.20)

project(CleanApp LANGUAGES CXX)

find_package(AnyLib 0.0.1 REQUIRED)
find_package(Qt6 COMPONENTS Core REQUIRED)

add_executable(CleanApp
    src/main.cpp
)

set_target_properties(CleanApp PROPERTIES 
    DEBUG_POSTFIX d
)

target_link_libraries(CleanApp 
    PRIVATE AnyLib::AnyLib
    Qt6::Core
)
