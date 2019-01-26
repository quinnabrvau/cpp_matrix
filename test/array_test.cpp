//
//  genetic_test.cpp
//  GAME_TEST_LIB
//
//  Created by Quinn Abrahams-Vaughn on 1/11/19.
//

#include "Matrix.hpp"
#include "Container_Multi_Level.hpp"

using namespace matrix;

#include "unity.h"

int main(int argc, const char * argv[]) {
    UNITY_BEGIN();
    test__Matrix();
    test__CML();
    return UNITY_END();
}
