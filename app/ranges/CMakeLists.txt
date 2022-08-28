cmake_minimum_required(VERSION 3.20)

find_package(Boost 1.79.0 REQUIRED COMPONENTS thread)

add_executable(Ranges main.cpp)

target_link_libraries(Ranges PRIVATE 
	Boost::boost
)
