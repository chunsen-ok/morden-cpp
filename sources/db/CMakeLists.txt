add_executable(db
    main.cpp
)
target_compile_features(db PUBLIC cxx_std_17)
target_link_libraries(db 
    PUBLIC sqlite3
    PUBLIC mcpp
)

