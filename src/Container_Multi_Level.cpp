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
void test__iter_copy1(void) {
    for (int i = 1; i < 20; i++) {
        for(int j = 1; j < i; j++) {
            Container_Multi_Level<cont1 ,cont2, T>  A(i,j);
            Container_Multi_Level<cont1, cont2, T>  B(A.begin(),A.end());
            
            auto ait = A.begin();
            auto bit = B.begin();
            while (ait != A.end() && bit != B.end()) {
                TEST_ASSERT_EQUAL(*ait++, *bit++);
            }
            TEST_ASSERT(ait==A.end());
            TEST_ASSERT(bit==B.end());
            
            
            while (ait != A.begin() && bit != B.begin()) {
                ait--;bit--;
                TEST_ASSERT_EQUAL(*ait, *bit);
            }
            TEST_ASSERT(ait==A.begin());
            TEST_ASSERT(bit==B.begin());
            
            
            while (ait != A.end() && bit != B.end()) {
                TEST_ASSERT_EQUAL(*ait, *bit);
                ++ait; ++bit;
            }
            TEST_ASSERT(ait==A.end());
            TEST_ASSERT(bit==B.end());
            
            
            while (ait != A.begin() && bit != B.begin()) {
                TEST_ASSERT_EQUAL(*(--ait), *(--bit));
            }
            TEST_ASSERT(ait==A.begin());
            TEST_ASSERT(bit==B.begin());
        }
    }
}

template <class cont1, class cont2, class T>
void test__iter_copy2(void) {
    for (int i = 1; i < 20; i++) {
        for(int j = 1; j < i; j++) {
            Container_Multi_Level<cont1 ,cont2, T>  A(i,j);
            Container_Multi_Level<cont1, cont2, T>  B(A);
            
            auto ait = A.begin();
            auto bit = B.begin();
            while (ait != A.end() && bit != B.end()) {
                TEST_ASSERT_EQUAL(*ait++, *bit++);
            }
            TEST_ASSERT(ait==A.end());
            TEST_ASSERT(bit==B.end());
            
            
            while (ait != A.begin() && bit != B.begin()) {
                ait--;bit--;
                TEST_ASSERT_EQUAL(*ait, *bit);
            }
            TEST_ASSERT(ait==A.begin());
            TEST_ASSERT(bit==B.begin());
            
            
            while (ait != A.end() && bit != B.end()) {
                TEST_ASSERT_EQUAL(*ait, *bit);
                ++ait; ++bit;
            }
            TEST_ASSERT(ait==A.end());
            TEST_ASSERT(bit==B.end());
            
            
            while (ait != A.begin() && bit != B.begin()) {
                TEST_ASSERT_EQUAL(*(--ait), *(--bit));
            }
            TEST_ASSERT(ait==A.begin());
            TEST_ASSERT(bit==B.begin());
        }
    }
}

template <class cont1, class cont2, class T>
void test__iter_inc(void) {
    for (int i = 1; i < 20; i++) {
        for(int j = 1; j < i; j++) {
            Container_Multi_Level<cont1 ,cont2, T>  A(i,j);
            auto ait = A.begin();
            auto bit = A.begin();
            auto cit = A.cbegin();
            while (ait != A.end() && bit != A.end() && cit != A.cend()) {
                T foo = *ait;
                *ait++ += 1;
                TEST_ASSERT_EQUAL(*bit, foo+1);
                TEST_ASSERT_EQUAL(*cit, foo+1);
                TEST_ASSERT_EQUAL(*++bit, *bit);
                TEST_ASSERT_EQUAL(*++cit, *cit);
            }
            TEST_ASSERT(ait==A.end());
            TEST_ASSERT(bit==A.end());
            TEST_ASSERT(cit==A.cend());
        }
    }
}

template <class cont1, class cont2, class T>
void test__iter_dec(void) {
    for (int i = 1; i < 20; i++) {
        for(int j = 1; j < i; j++) {
            Container_Multi_Level<cont1 ,cont2, T>  A(i,j);
            auto ait = A.end();
            auto bit = A.end();
            auto cit = A.cend();
            ait--; bit--; cit--;
            while (ait != A.begin() && bit != A.begin() && cit != A.cbegin()) {
                T foo = *ait;
                *ait-- += 1;
                TEST_ASSERT_EQUAL(*bit, foo+1);
                TEST_ASSERT_EQUAL(*cit, foo+1);
                TEST_ASSERT_EQUAL(*--bit, *bit);
                TEST_ASSERT_EQUAL(*--cit, *cit);
            }
            TEST_ASSERT(ait==A.begin());
            TEST_ASSERT(bit==A.begin());
            TEST_ASSERT(cit==A.cbegin());
        }
    }
}

template <class cont1, class cont2, class T>
void test__iter_ptr(void) {
    for (int i = 1; i < 20; i++) {
        for(int j = 1; j < i; j++) {
            Container_Multi_Level<cont1 ,cont2, T>  A(i,j);
            auto ait = A.begin();
            auto cit = A.cbegin();
            while (ait != A.end() && cit != A.cend()) {
                const T foo = *ait;
                TEST_ASSERT_EQUAL(&(*ait), ait.operator->());
                const T phi = *cit;
                TEST_ASSERT_EQUAL(&(*cit), cit.operator->());
                TEST_ASSERT_EQUAL(foo, phi);
                ait++;cit++;
            }
        }
    }
}

void test__CML(void) {
    CML_RUN_TEST(test__iter_copy1);
    CML_RUN_TEST(test__iter_copy2);
    CML_RUN_TEST(test__iter_inc);
    CML_RUN_TEST(test__iter_dec);
    CML_RUN_TEST(test__iter_ptr);
}
#endif//TESTING
