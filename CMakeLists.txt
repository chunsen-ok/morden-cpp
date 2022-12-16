cmake_minimum_required(VERSION 3.20)

project(ModernCpp)

add_subdirectory(extern/spdlog)
add_subdirectory(extern/sqlite3)

add_subdirectory(src)

#add_subdirectory(app/clean)
add_subdirectory(app/fp)
add_subdirectory(app/fs)
#add_subdirectory(app/WebServer)
#add_subdirectory(app/db)
