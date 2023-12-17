cmake_minimum_required(VERSION 3.10)
project(OOD)                   # project name
add_compile_options(-g -Wall -Werror) #do not allow any warning

set(CMAKE_CXX_STANDARD 14)            # C++14

add_executable(hotelbookingsys hotelbookingsys.cpp)  # set the executable file name

