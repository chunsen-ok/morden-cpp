#! /bin/bash

CMAKE_APP="D:/Qtz/Tools/CMake_64/bin/cmake.exe"

if [ "$1" == "--build" ];  then
    $CMAKE_APP -S "$2" -B "build/$2" -G "MinGW Makefiles"
    $CMAKE_APP --build "build/$2"
    $CMAKE_APP --install "build/$2"
elif [ "$1" == "--new" ]; then
    if [ -n "$2" ]; then
        mkdir $2
        cp project.template $2/CMakeLists.txt
    fi
elif [ "$1" == "--run" ]; then
    "bin/$2.exe"
fi
