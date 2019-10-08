cmake_minimum_required(VERSION 3.0)

project(segwick)

set(CMAKE_CXX_FLAGS_DEBUG "-std=c++17 ${CMAKE_CXX_FLAGS} -g -W -Wall -Wextra -pedantic -Wno-unknown-pragmas -fPIC -fno-strict-aliasing -I../")
#set(CMAKE_CXX_FLAGS_RELEASE "-std=c++17 ${CMAKE_CXX_FLAGS} -O3 -W -Wall -Wextra -pedantic -Wno-unknown-pragmas -fPIC -fno-strict-aliasing -I../")

link_directories(${PROJECT_NAME} ../ ../gtest/ ../gtest/internal ../gtest/internal/custom)

aux_source_directory(src SRC_LIST)
aux_source_directory(src/Chapter_1_2 SRC_LIST)
aux_source_directory(src/Chapter_1_3 SRC_LIST)
aux_source_directory(src/Chapter_1_5 SRC_LIST)

FILE(GLOB_RECURSE INC_ALL "src/Chapter_1_5/*.h")

FILE(DOWNLOAD https://algs4.cs.princeton.edu/15uf/tinyUF.txt
    ${CMAKE_BINARY_DIR}/data/tinyUF.txt
    SHOW_PROGRESS)

FILE(DOWNLOAD https://algs4.cs.princeton.edu/15uf/mediumUF.txt
    ${CMAKE_BINARY_DIR}/data/mediumUF.txt
    SHOW_PROGRESS)

FILE(DOWNLOAD https://algs4.cs.princeton.edu/15uf/largeUF.txt
    ${CMAKE_BINARY_DIR}/data/largeUF.txt
    SHOW_PROGRESS)

add_executable(${PROJECT_NAME} main.cpp ${SRC_LIST} ${INC_ALL})

target_link_libraries(${PROJECT_NAME} -lgtest -lpthread)

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_include_directories(${PROJECT_NAME} PUBLIC ../)
target_include_directories(${PROJECT_NAME} PUBLIC ../gtest)
target_include_directories(${PROJECT_NAME} PUBLIC ../gtest/internal)
target_include_directories(${PROJECT_NAME} PUBLIC ../gtest/internal/custom)

