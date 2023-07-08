add_executable(Tokenize
    main.cpp
)

target_compile_features(Tokenize PRIVATE cxx_std_20)

target_link_libraries(Tokenize PRIVATE
    External::Cppjieba
)
