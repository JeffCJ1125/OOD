cmake_minimum_required(VERSION 3.10)
project(energy_calculator)
set(CMAKE_CXX_STANDARD 14)
add_compile_options(-g -Wall -Werror)

add_executable(energy_calculator energy_calculator.cpp)

