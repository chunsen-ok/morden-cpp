#! /bin/bash

CMAKE_APP="D:/Qtz/Tools/CMake_64/bin/cmake.exe"


function build {
    $CMAKE_APP -S "$1" -B "build/$1" -G "MinGW Makefiles"
    $CMAKE_APP --build "build/$1"
    $CMAKE_APP --install "build/$1"
}

function run {
    "./bin/$1.exe"
}

function new {
    mkidr $1
    cp project.template $1/CMakeLists.txt
    cp main.template $1/mainc.pp
}

if [ "$1" == "--build" ];  then
    build $2
elif [ "$1" == "--new" ]; then
    if [ -n "$2" ]; then
        new $2
    fi
elif [ "$1" == "--run" ]; then
    run $2
elif [ "$1" == "--build-run" ]; then
    build $2
    run $2
fi
