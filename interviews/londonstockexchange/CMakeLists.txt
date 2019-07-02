cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "-std=c++17 ${CMAKE_CXX_FLAGS} -g -W -Wall -Wextra -pedantic -Wno-unknown-pragmas -fPIC -fno-strict-aliasing")
project(londonstockexchange)
add_executable(${PROJECT_NAME} "main.cpp")
