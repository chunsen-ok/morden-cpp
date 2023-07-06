add_library(CxDb STATIC

)
add_library(Cx::Db ALIAS CxDb)

target_compile_features(CxDb PRIVATE cxx_std_20)
target_include_directories(CxDb PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(CxDb 
    PRIVATE
        External::Sqlite3
)
