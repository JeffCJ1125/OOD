cmake_minimum_required(VERSION 3.10)
project(BookstoreInventory)
add_compile_options(-g -Wall -Werror)
set(CMAKE_CXX_STANDARD 14)

add_executable(bookstore_inventory bookstore_inventory.cpp)