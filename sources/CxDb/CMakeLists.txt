add_library(CxDb STATIC
    database.hpp
    database.cpp
    sqlquery.hpp
    sqlquery.cpp
    fts5_chinese_tokenizer.hpp
    fts5_chinese_tokenizer.cpp
)
add_library(Cx::Db ALIAS CxDb)

target_compile_features(CxDb PRIVATE cxx_std_17)
target_include_directories(CxDb PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(CxDb 
    PRIVATE
        External::Sqlite3
)
