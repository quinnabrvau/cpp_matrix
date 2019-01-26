project( TEST )

cmake_minimum_required (VERSION 3.4)

file(GLOB_RECURSE UNITY_SOURCES "../unity/src/*")

include_directories (
    ../include
    ../unity/src
)
add_executable (Matrix_Test_
    array_test.cpp
    ${UNITY_SOURCES}
)
target_link_libraries(Matrix_Test_
    MATRIX_TEST_LIB
)
add_test (NAME Matrix_Test COMMAND Matrix_Test_)
