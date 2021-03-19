cmake_minimum_required(VERSION 3.0)

project(hrank)

set(CMAKE_CXX_FLAGS "-std=c++17 ${CMAKE_CXX_FLAGS} -g -W -Wall -Wextra -pedantic -Wno-unknown-pragmas -fPIC -fno-strict-aliasing -I../")

link_directories(${PROJECT_NAME} util/ ../ ../gtest/ ../gtest/internal ../gtest/internal/custom)

aux_source_directory(. SRC_LIST)
aux_source_directory(src SRC_LIST)
aux_source_directory(src/util SRC_LIST)
aux_source_directory(tests/01 SRC_LIST)

add_executable(${PROJECT_NAME} ${SRC_LIST} ${INC_ALL})

target_link_libraries(${PROJECT_NAME} -lgtest -lpthread)

target_include_directories(${PROJECT_NAME} PUBLIC include/)
target_include_directories(${PROJECT_NAME} PUBLIC src/)
target_include_directories(${PROJECT_NAME} PUBLIC exercises/01)
target_include_directories(${PROJECT_NAME} PUBLIC ../)
target_include_directories(${PROJECT_NAME} PUBLIC ../gtest)
target_include_directories(${PROJECT_NAME} PUBLIC ../gtest/internal)
target_include_directories(${PROJECT_NAME} PUBLIC ../gtest/internal/custom)

