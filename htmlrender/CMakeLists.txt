cmake_minimum_required(VERSION 3.20)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(litehtml REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(HtmlRenderer
	main.cpp 
	mainwindow.h 
	mainwindow.cpp
	htmlwidget.h
	htmlwidget.cpp
	master_css.inc
)

set_target_properties(HtmlRenderer PROPERTIES 
	WIN32_EXECUTABLE TRUE
)

target_link_libraries(HtmlRenderer PRIVATE 
	litehtml
	Qt6::Widgets
)
