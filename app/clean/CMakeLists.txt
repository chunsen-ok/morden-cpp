add_executable(capp main.cpp)
target_compile_features(capp PUBLIC cxx_std_17)
target_link_libraries(capp 
    PUBLIC spdlog::spdlog
)
