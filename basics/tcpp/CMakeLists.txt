cmake_minimum_required(VERSION 3.20)

project(tcpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(Boost_NO_BOOST_CMAKE ON)
set(BOOST_ROOT "F:/repo/boost_1_79_0")
find_package(Boost 1.79.0)

add_executable(tcpp 
    src/main.cpp
)

target_link_libraries(tcpp Boost::boost)