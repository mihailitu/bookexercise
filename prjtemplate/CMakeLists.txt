cmake_minimum_required(VERSION 2.8)

project(prjtemplate)

set(CMAKE_CXX_FLAGS "-std=c++17 ${CMAKE_CXX_FLAGS} -g -W -Wall -Wextra -pedantic -Wno-unknown-pragmas -fPIC -fno-strict-aliasing")
include_directories(include)
# target_include_directories(prjtemplate PUBLIC include/)
FILE(GLOB_RECURSE INC_ALL "include/*.h")
aux_source_directory(src SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST} ${INC_ALL})
