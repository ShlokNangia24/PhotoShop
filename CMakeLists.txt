cmake_minimum_required(VERSION 3.23)
project(Project_3)

set(CMAKE_CXX_STANDARD 20)

add_executable(image-processor main.cpp Header.cpp Header.h blenders.cpp blenders.h tester.cpp tester.h)
