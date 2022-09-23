cmake_minimum_required(VERSION 3.20)

project(extern_sqlite3 VERSION 3.39.2 LANGUAGES C)

add_library(sqlite3 STATIC
    src/sqlite3.c
)

target_include_directories(sqlite3 
    INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    INTERFACE $<INSTALL_INTERFACE:include>
)
