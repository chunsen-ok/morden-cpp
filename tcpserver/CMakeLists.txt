cmake_minimum_required(VERSION 3.20)

project(tcpserver VERSION 0.1.0 LANGUAGES CXX)

set(Boost_ROOT "${CX_WORKSPACE_ROOT}/toolchains/boost_1_83_0")
find_package(Boost 1.83.0 REQUIRED)

add_executable(TcpServer main.cpp)

target_compile_features(TcpServer PRIVATE cxx_std_20)

target_link_libraries(TcpServer PRIVATE 
	Boost::boost
)
