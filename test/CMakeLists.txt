project( TEST )

cmake_minimum_required (VERSION 3.4)

file(GLOB_RECURSE UNITY_SOURCES "../unity/src/*")

include_directories (
    ../include
    ../unity/src
)
add_executable (_Matrix_Test 
    array_test.cpp
    ${UNITY_SOURCES}
)
target_link_libraries(_Matrix_Test
    MATRIX_TEST_LIB
)
add_test (NAME Matrix_Test COMMAND _Matrix_Test)
