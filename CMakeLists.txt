cmake_minimum_required(VERSION 3.14)
project(BA-Project2)

set(CMAKE_CXX_STANDARD 14)

add_executable(testing testing.cpp songDatabase.cpp)
add_executable(main main.cpp songDatabase.cpp)