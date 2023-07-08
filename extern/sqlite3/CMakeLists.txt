include(ExternalProject)

ExternalProject_Add(
    sqlite3
    URL "https://sqlite.org/2023/sqlite-amalgamation-3420000.zip"
    URL_HASH "SHA3_256=436747dc8090d015b9869b96f5837f745e852d2ce73fd77410ed76ee51107a1f" # SHA3-256
    DOWNLOAD_EXTRACT_TIMESTAMP ON

    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    TEST_COMMAND ""
)

ExternalProject_Get_Property(
    sqlite3
    SOURCE_DIR
)

add_library(ExternalSqlite3 STATIC
    ${SOURCE_DIR}/sqlite3.h
    ${SOURCE_DIR}/sqlite3ext.h
    ${SOURCE_DIR}/sqlite3.c
)
add_library(External::Sqlite3 ALIAS ExternalSqlite3)

target_include_directories(ExternalSqlite3 PUBLIC ${SOURCE_DIR})
target_compile_features(ExternalSqlite3 PRIVATE cxx_std_17)
target_compile_definitions(ExternalSqlite3
    PRIVATE
        SQLITE_ENABLE_FTS5
        SQLITE_ENABLE_JSON1
)
