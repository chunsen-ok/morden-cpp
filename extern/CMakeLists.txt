add_subdirectory(sqlite3)

if(${MCPP_ENABLE_TOKENIZER})
    add_subdirectory(cppjieba)
endif()