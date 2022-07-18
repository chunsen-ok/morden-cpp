cmake_minimum_required(VERSION 3.20)

find_package(Boost 1.79.0 REQUIRED)

add_executable(WebServer 
	main.cpp 
	webserver_global.hpp
	tcplistener.hpp 
	session.hpp 
	session.cpp
 )

target_link_libraries(WebServer PRIVATE 
	Boost::boost
)
