cmake_minimum_required(VERSION 3.0)

project(prjtemplate)

set(CMAKE_CXX_FLAGS "-std=c++17 ${CMAKE_CXX_FLAGS} -g -W -Wall -Wextra -pedantic -Wno-unknown-pragmas -fPIC -fno-strict-aliasing")

aux_source_directory(src SRC_LIST)
add_executable(${PROJECT_NAME} main.cpp ${SRC_LIST} ${INC_ALL})

target_include_directories(${PROJECT_NAME} PUBLIC include/)
