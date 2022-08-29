cmake_minimum_required(VERSION 3.14)

project(crypto LANGUAGES CXX C)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(OPENSSL_ROOT_DIR "D:\\OpenSSL-Win64")

include(FindOpenSSL)
find_package(OpenSSL)

add_executable(crypto
  main.cpp
)

target_link_libraries(crypto
    PRIVATE OpenSSL::SSL
    PRIVATE OpenSSL::Crypto
    PRIVATE OpenSSL::applink
)
