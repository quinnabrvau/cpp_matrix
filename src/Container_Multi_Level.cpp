//
//  Container_Multi_Level.cpp
//  Cpp_Matrix
//
//  Created by Quinn Abrahams-Vaughn on 1/26/19.
//

#include <stdio.h>
#ifdef TESTING
#include "unity.h"
#include "Container_Multi_Level.hpp"

#include <vector>
#include <list>

using namespace std;
using namespace matrix;

typedef void (*void_func) (void);

typedef unsigned char unchar__CML;
typedef unsigned short unshort__CML ;
typedef unsigned int unint__CML;
typedef unsigned long unlong__CML;
typedef long long longlong__CML;
typedef long double longdouble__CML;

#define ___CML_RUN_TEST(func,cont,num)       \
do {                                         \
void_func func ## _ ## cont ## _ ## num      \
= func < cont<cont<num>>, cont<num>, num >;  \
RUN_TEST( (func ## _ ## cont ## _ ## num) ); \
} while(false)

#define _CML_RUN_TEST(func,cont)                \
do {                                            \
___CML_RUN_TEST( func,cont,char );              \
___CML_RUN_TEST( func,cont,unchar__CML );       \
___CML_RUN_TEST( func,cont,unshort__CML );      \
___CML_RUN_TEST( func,cont,short );             \
___CML_RUN_TEST( func,cont,int );               \
___CML_RUN_TEST( func,cont,unint__CML );        \
___CML_RUN_TEST( func,cont,long );              \
___CML_RUN_TEST( func,cont,unlong__CML );       \
___CML_RUN_TEST( func,cont,longlong__CML );     \
___CML_RUN_TEST( func,cont,float );             \
___CML_RUN_TEST( func,cont,double );            \
___CML_RUN_TEST( func,cont,longdouble__CML );   \
} while(false)

#define CML_RUN_TEST(func)      \
do {                            \
_CML_RUN_TEST(func,vector);     \
_CML_RUN_TEST(func,list);       \
} while(false)


template <class cont1, class cont2, class T>
void test__iter(void) {
    for (int i = 1; i < 20; i++) {
        for(int j = 1; j < i; j++) {
            Container_Multi_Level<cont1 ,cont2, T>  A(i,j);
            Container_Multi_Level<cont1, cont2, T>  B(A.begin(),A.end());
            
            auto ait = A.begin();
            auto bit = B.begin();
            while (ait != A.end() && bit != B.end()) {
                TEST_ASSERT_EQUAL(*ait, *bit);
                ait++; bit++;
            }
            TEST_ASSERT(ait==A.end());
            TEST_ASSERT(bit==B.end());
        }
    }
}


void test__CML(void) {
    void_func func = test__iter<vector<vector<int>>,vector<int>,int>;

    CML_RUN_TEST(test__iter);
}
#endif//TESTING