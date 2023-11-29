add_executable(tui main.cpp)

target_compile_features(tui PRIVATE cxx_std_20)
target_include_directories(tui PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
