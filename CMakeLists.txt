cmake_minimum_required(VERSION 3.10)
project(Calculator_Parsing)

set(CMAKE_CXX_STANDARD 17)

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/build)

set(FLEX_DIR ${CMAKE_SOURCE_DIR}/flex/src)
set(BUILD_DIR ${CMAKE_SOURCE_DIR}/build)
find_package(FLEX)

FLEX_TARGET(MyScanner ${FLEX_DIR}/flex.l ${BUILD_DIR}/lex_lib.hpp)

include_directories(${BUILD_DIR} ${FLEX_DIR})

add_executable(parsing ${FLEX_DIR}/main.cpp ${FLEX_DIR}/lex_funct.cpp ${FLEX_MyScanner_OUTPUTS})

set(SHIFT_REDUCE_DIR ${CMAKE_SOURCE_DIR}/shift-reduce)

add_executable(lexer ${SHIFT_REDUCE_DIR}/main.cpp)
