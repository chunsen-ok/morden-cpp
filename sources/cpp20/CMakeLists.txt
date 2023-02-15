add_executable(cpp20
    main.cpp
)

target_compile_features(cpp20 PRIVATE cxx_std_20)
