cmake_minimum_required(VERSION 3.20)

project(HttpServer VERSION 0.1.0 LANGUAGES CXX)

set(Boost_ROOT "${CX_WORKSPACE_ROOT}/toolchains/boost_1_83_0")
find_package(Boost 1.83.0 REQUIRED)

add_executable(HttpServer main.cpp)

target_link_libraries(HttpServer PRIVATE 
	Boost::boost
)
