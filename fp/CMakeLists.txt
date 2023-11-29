add_executable(fp main.cpp)
target_compile_features(fp PUBLIC cxx_std_17)
target_link_libraries(fp PUBLIC mcpp)
