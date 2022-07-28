cmake_minimum_required(VERSION 3.20)

project(Play LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# find_package(Boost 1.79.0 REQUIRED COMPONENTS thread)

# add_subdirectory(src/tcpclient)
# add_subdirectory(src/tcpserver)
# add_subdirectory(src/httpserver)
# add_subdirectory(src/htmlrender)
# add_subdirectory(src/ranges)
add_subdirectory(src/WebServer)