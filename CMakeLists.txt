cmake_minimum_required(VERSION 3.14)

project(p1_project C)

set(CMAKE_C_STANDARD 11)


add_subdirectory(Main)

enable_testing()
add_subdirectory(Test)




