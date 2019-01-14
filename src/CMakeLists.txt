project( MATRIX_LIB )
cmake_minimum_required (VERSION 3.4)

file(GLOB_RECURSE headers "../include/*.hpp")

set( MATRIX_SOURCES
    ./Matrix.cpp
    ../include/Matrix.hpp
)

include_directories(
    ../include
)

add_library(MATRIX_TEST_LIB
    ../unity/src/unity.c
    ${MATRIX_SOURCES}
)
target_include_directories(MATRIX_TEST_LIB
    PRIVATE ../unity/src
)
target_compile_definitions(MATRIX_TEST_LIB
    PRIVATE TESTING
)

add_library(MATRIX_LIB
    ${MATRIX_SOURCES}
)
