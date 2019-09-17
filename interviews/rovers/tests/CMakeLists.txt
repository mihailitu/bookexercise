cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} -g -W -Wall -Wextra -pedantic -Wno-unknown-pragmas -fPIC -fno-strict-aliasing -I../")

project(rovers_ut)
add_executable(${PROJECT_NAME} "main.cpp" "rover_ut.cpp" "../rover.cpp")

target_link_libraries(${PROJECT_NAME} -lgtest -lpthread)

