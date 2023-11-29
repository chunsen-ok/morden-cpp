cmake_minimum_required(VERSION 3.20)

find_package(Boost 1.79.0 REQUIRED COMPONENTS thread)

add_executable(TcpServer main.cpp)

target_link_libraries(TcpServer PRIVATE 
	Boost::boost
	Boost::thread
)
