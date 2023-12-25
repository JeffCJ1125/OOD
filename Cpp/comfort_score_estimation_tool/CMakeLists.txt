cmake_minimum_required(VERSION 3.10)
project(comfort_estimation_tool)
add_compile_options(-g -Wall -Werror)

set(CMAKE_CXX_STANDARD 14)
add_executable(comfort_estimation_tool comfort_estimation_tool.cpp)
