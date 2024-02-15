cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 14)
add_compile_options(-g -Wall -Werror)

project(rental_service)

add_executable(rental_service rental_service.cpp)