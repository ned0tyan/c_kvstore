cmake_minimum_required(VERSION 3.10)
project(c_kvstore C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(c_kvstore src/main.cpp)