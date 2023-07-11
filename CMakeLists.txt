cmake_minimum_required(VERSION 3.20)

project(ModernCpp VERSION 0.1.0 LANGUAGES C CXX)

set(MCPP_ENABLE_TOKENIZER OFF CACHE BOOL "Enable cppjieba")

add_subdirectory(extern)
add_subdirectory(sources)
add_subdirectory(tests)
