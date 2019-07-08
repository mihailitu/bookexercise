cmake_minimum_required(VERSION 3.0)

project(segwick)

set(CMAKE_CXX_FLAGS "-std=c++17 ${CMAKE_CXX_FLAGS} -g -W -Wall -Wextra -pedantic -Wno-unknown-pragmas -fPIC -fno-strict-aliasing -I../")

link_directories(${PROJECT_NAME} ../ ../gtest/ ../gtest/internal ../gtest/internal/custom)

aux_source_directory(src SRC_LIST)

#FILE(GLOB_RECURSE INC_ALL "../gtest/*.h")

add_executable(${PROJECT_NAME} main.cpp ${SRC_LIST} ${INC_ALL})

target_link_libraries(${PROJECT_NAME} -lgtest -lpthread)

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_include_directories(${PROJECT_NAME} PUBLIC ../)
target_include_directories(${PROJECT_NAME} PUBLIC ../gtest)
target_include_directories(${PROJECT_NAME} PUBLIC ../gtest/internal)
target_include_directories(${PROJECT_NAME} PUBLIC ../gtest/internal/custom)

