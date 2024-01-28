cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 14)
add_compile_options(-g -Wall -Werror)

project(library_book_management)

add_executable(library_book_management library_book_management.cpp)