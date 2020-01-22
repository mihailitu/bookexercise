cmake_minimum_required(VERSION 3.0)

project(segwick)

set(CMAKE_CXX_FLAGS_DEBUG "-std=c++17 ${CMAKE_CXX_FLAGS} -g -W -Wall -Wextra -pedantic -Wno-unknown-pragmas -fPIC -fno-strict-aliasing -I../")
#set(CMAKE_CXX_FLAGS_RELEASE "-std=c++17 ${CMAKE_CXX_FLAGS} -O3 -W -Wall -Wextra -pedantic -Wno-unknown-pragmas -fPIC -fno-strict-aliasing -I../")

link_directories(${PROJECT_NAME} util/ ../ ../gtest/ ../gtest/internal ../gtest/internal/custom)

aux_source_directory(src SRC_LIST)
aux_source_directory(src/util SRC_LIST)
aux_source_directory(src/Chapter_1_2 SRC_LIST)
aux_source_directory(src/Chapter_1_3 SRC_LIST)
aux_source_directory(src/Chapter_1_4 SRC_LIST)
aux_source_directory(src/Chapter_1_5 SRC_LIST)
aux_source_directory(src/Chapter_2_1 SRC_LIST)
aux_source_directory(src/Chapter_2_2 SRC_LIST)
aux_source_directory(src/Chapter_2_3 SRC_LIST)
aux_source_directory(src/Chapter_2_4 SRC_LIST)
aux_source_directory(src/Chapter_3_1 SRC_LIST)
aux_source_directory(src/Chapter_3_2 SRC_LIST)
aux_source_directory(src/Chapter_3_3 SRC_LIST)
aux_source_directory(src/Chapter_5_1 SRC_LIST)

FILE(GLOB_RECURSE INC_ALL "src/Chapter_1_5/*.h")

add_executable(${PROJECT_NAME} main.cpp ${SRC_LIST} ${INC_ALL})

target_link_libraries(${PROJECT_NAME} -lgtest -lpthread)

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_include_directories(${PROJECT_NAME} PUBLIC src/Chapter_5_1)
target_include_directories(${PROJECT_NAME} PUBLIC ../)
target_include_directories(${PROJECT_NAME} PUBLIC ../gtest)
target_include_directories(${PROJECT_NAME} PUBLIC ../gtest/internal)
target_include_directories(${PROJECT_NAME} PUBLIC ../gtest/internal/custom)

# Instead, from bin dir, use ../data.sh, not to download all files for ever cmake
#FILE(DOWNLOAD https://algs4.cs.princeton.edu/15uf/tinyUF.txt
#    ${CMAKE_BINARY_DIR}/data/tinyUF.txt
#    SHOW_PROGRESS)

#FILE(DOWNLOAD https://algs4.cs.princeton.edu/15uf/mediumUF.txt
#    ${CMAKE_BINARY_DIR}/data/mediumUF.txt
#    SHOW_PROGRESS)

#FILE(DOWNLOAD https://algs4.cs.princeton.edu/15uf/largeUF.txt
#    ${CMAKE_BINARY_DIR}/data/largeUF.txt
#    SHOW_PROGRESS)

#FILE(DOWNLOAD https://algs4.cs.princeton.edu/14analysis/1Kints.txt
#    ${CMAKE_BINARY_DIR}/data/1Kints.txt
#    SHOW_PROGRESS)

#FILE(DOWNLOAD https://algs4.cs.princeton.edu/14analysis/2Kints.txt
#    ${CMAKE_BINARY_DIR}/data/2Kints.txt
#    SHOW_PROGRESS)

#FILE(DOWNLOAD https://algs4.cs.princeton.edu/14analysis/4Kints.txt
#    ${CMAKE_BINARY_DIR}/data/4Kints.txt
#    SHOW_PROGRESS)

#FILE(DOWNLOAD https://algs4.cs.princeton.edu/14analysis/8Kints.txt
#    ${CMAKE_BINARY_DIR}/data/8Kints.txt
#    SHOW_PROGRESS)

#FILE(DOWNLOAD https://algs4.cs.princeton.edu/14analysis/16Kints.txt
#    ${CMAKE_BINARY_DIR}/data/16Kints.txt
#    SHOW_PROGRESS)

#FILE(DOWNLOAD https://algs4.cs.princeton.edu/14analysis/32Kints.txt
#    ${CMAKE_BINARY_DIR}/data/32Kints.txt
#    SHOW_PROGRESS)

#FILE(DOWNLOAD https://algs4.cs.princeton.edu/14analysis/1Mints.txt
#    ${CMAKE_BINARY_DIR}/data/1Mints.txt
#    SHOW_PROGRESS)
