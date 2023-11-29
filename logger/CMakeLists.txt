add_executable(logger main.cpp)
target_compile_features(logger PUBLIC cxx_std_17)
target_link_libraries(logger 
    PUBLIC spdlog::spdlog
)
