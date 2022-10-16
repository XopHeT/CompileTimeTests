cmake_minimum_required(VERSION 3.00)
project(CompileTimeTest)

set(CMAKE_CXX_STANDARD 23)

add_executable(CompileTimeTest main.cpp 
        MathExpectations.cpp MathExpectations.hpp)
