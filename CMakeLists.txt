cmake_minimum_required(VERSION 3.20)

project(ModernCpp)

add_subdirectory(extern/spdlog)

add_subdirectory(src)

add_subdirectory(app/clean)
add_subdirectory(app/fp) # functional programming
add_subdirectory(app/fs) # file, filesystem
