add_library(mcpp INTERFACE
    diff.hpp
)

target_compile_features(mcpp INTERFACE cxx_std_20)
target_include_directories(mcpp INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
