add_executable(cpp20
    main.cpp
)

target_compile_features(cpp20 PRIVATE cxx_std_20)

target_link_libraries(cpp20 PRIVATE 
    mcpp
)
