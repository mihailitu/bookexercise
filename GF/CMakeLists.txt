cmake_minimum_required(VERSION 2.8)

project(gfclient)

set(CMAKE_CXX_FLAGS_DEBUG "-std=c++11 ${CMAKE_CXX_FLAGS} -g -W -Wall -Wextra -pedantic -Wno-unknown-pragmas -fPIC -fno-strict-aliasing -Iinclude/")
aux_source_directory(. SRC_LIST)
FILE(GLOB_RECURSE INC_ALL "include/*.h")
add_executable(${PROJECT_NAME} main.cpp ${SRC_LIST} ${INC_ALL})

target_link_libraries(${PROJECT_NAME} -lpthread -lzmq -lz)
