add_executable(cman main.cpp)

target_compile_features(cman PRIVATE cxx_std_20)
target_include_directories(cman PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
