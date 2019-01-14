//
//  Matrix.cpp
//  GAME_TEST_LIB
//
//  Created by Quinn Abrahams-Vaughn on 1/11/19.
//

#include "Matrix.hpp"
#ifdef TESTING
#include "unity.h"
#include <iostream>

using namespace matrix;
    
#define _NUM_T_RUN_TEST(func)           \
do {                                \
RUN_TEST( func <int> );             \
RUN_TEST( func <short> );           \
RUN_TEST( func <long> );            \
RUN_TEST( func <unsigned int> );    \
RUN_TEST( func <unsigned short> );  \
RUN_TEST( func <unsigned long> );   \
RUN_TEST( func <char> );            \
RUN_TEST( func <float> );           \
RUN_TEST( func <double> );          \
RUN_TEST( func <long double> );     \
} while(false)

typedef void (*void_func) (void);

typedef unsigned char unchar__A;
typedef unsigned short unshort__A ;
typedef unsigned int unint__A;
typedef unsigned long unlong__A;
typedef long long longlong__A;
typedef long double longdouble__A;

#define ___RUN_TEST(func,type1,type2)       \
do {                                    \
void_func func ## _ ## type1 ## _ ## type2      \
= func < type1, type2 >;                       \
RUN_TEST( (func ## _ ## type1 ## _ ## type2) ); \
} while(false)

#define RUN_TEST_S(func, type1)            \
do {                                       \
___RUN_TEST( func,type1,char );            \
___RUN_TEST( func,type1,unchar__A );       \
___RUN_TEST( func,type1,unshort__A );      \
___RUN_TEST( func,type1,short );           \
___RUN_TEST( func,type1,int );             \
___RUN_TEST( func,type1,unint__A );        \
___RUN_TEST( func,type1,long );            \
___RUN_TEST( func,type1,unlong__A );       \
___RUN_TEST( func,type1,longlong__A );     \
___RUN_TEST( func,type1,float );           \
___RUN_TEST( func,type1,double );          \
___RUN_TEST( func,type1,longdouble__A );   \
} while(false)

#define _NUM_T_K_RUN_TEST(func)      \
do {                                 \
RUN_TEST_S( func, char );            \
RUN_TEST_S( func, unchar__A );       \
RUN_TEST_S( func, short );           \
RUN_TEST_S( func, unshort__A );      \
RUN_TEST_S( func, int );             \
RUN_TEST_S( func, unint__A );        \
RUN_TEST_S( func, long );            \
RUN_TEST_S( func, unlong__A );       \
RUN_TEST_S( func, longlong__A );     \
RUN_TEST_S( func, float );           \
RUN_TEST_S( func, double );          \
RUN_TEST_S( func, longdouble__A );   \
} while(false)


template <class T>
void test__gen_matrix(void) {
    Shape s;
    for (int i = 1; i < 20; i++) {
        for(int j = 1; j < i; j++) {
            Matrix<T> A(i,j);
            s = A.shape();
            TEST_ASSERT_TRUE(s.first==i && s.second==j);
            TEST_ASSERT_TRUE(A==0);
            TEST_ASSERT_FALSE(A==1);
            TEST_ASSERT_TRUE(A==A);
            
            Matrix<T> B = Matrix_Zeros<T>(i,j);
            s = B.shape();
            TEST_ASSERT_TRUE(s.first==i && s.second==j);
            TEST_ASSERT_TRUE(B==0);
            TEST_ASSERT_FALSE(B==1);
            TEST_ASSERT_TRUE(A==B && B==A);
            
            B = Matrix_Zeros<T>(j,i);
            s = B.shape();
            TEST_ASSERT_TRUE(s.first==j && s.second==i);
            TEST_ASSERT_TRUE(B==0);
            TEST_ASSERT_FALSE(B==1);
            TEST_ASSERT_FALSE(A==B);
            TEST_ASSERT_FALSE(B==A);
            
            Matrix<T> C = Matrix_Ones<T>(i,j);
            s = C.shape();
            TEST_ASSERT_TRUE(s.first==i && s.second==j);
            TEST_ASSERT_FALSE(C==0);
            TEST_ASSERT_TRUE(C==1);
            TEST_ASSERT_FALSE(A==C);
            TEST_ASSERT_FALSE(A==B);
        }
    }
}

template <class T, class K>
void test__multiply_tk(void) {
    Shape s, a, b;
    for (int i = 1; i < 20; i++) {
        for(int j = 1; j < i; j++) {
            for (int k = 1; k < j; k++) {
                Matrix<T> A = Matrix_Ones<T>(Shape(i,j));
                Matrix<K> B = Matrix_Ones<K>(Shape(j,k));
                a = A.shape(); b = B.shape();
                TEST_ASSERT_TRUE(A.can_multiply(B));
                Matrix<T> C = A*B;
                s = C.shape();
                TEST_ASSERT_EQUAL(i, s.first);
                TEST_ASSERT_EQUAL(k, s.second);
                TEST_ASSERT_TRUE(C == j);
                
                A = Matrix_Zeros<T>(i,j);
                C = A*B;
                s = C.shape();
                TEST_ASSERT_EQUAL(i, s.first);
                TEST_ASSERT_EQUAL(k, s.second);
                TEST_ASSERT_TRUE(C==0);
                
                B = Matrix_Ones<K>(k,j);
                TEST_ASSERT_FALSE(A.can_multiply(B));
                A = Matrix_Ones<T>(Shape(i,j));
                C = A*2;
                TEST_ASSERT(C==2);
                TEST_ASSERT(B==1);
                
                C*=2;
                TEST_ASSERT(C==4);
            }
        }
    }
}

template <class T, class K>
void test__add_tk(void) {
    Shape s, a, b;
    for (int i = 1; i < 20; i++) {
        for(int j = 1; j < i; j++) {
            Matrix<T> A = Matrix_Ones<T>(Shape(i,j));
            Matrix<K> B = Matrix_Ones<K>(Shape(i,j));
            a = A.shape(); b = B.shape();
            TEST_ASSERT_TRUE(A.can_add(B));
            Matrix<T> C = A+B;
            s = C.shape();
            TEST_ASSERT(s == A.shape());
            TEST_ASSERT_TRUE(C == 2);
            TEST_ASSERT_TRUE(C != 1);
            TEST_ASSERT_TRUE(C != 0);
            
            A = Matrix_Zeros<T>(i,j);
            C = A+B;
            s = C.shape();
            TEST_ASSERT(s == A.shape());
            TEST_ASSERT_TRUE(C == 1);
            TEST_ASSERT_TRUE(C != 2);
            TEST_ASSERT_TRUE(C != 0);
            
            B = Matrix_Zeros<K>(j,i);
            TEST_ASSERT_FALSE(A.can_add(B));
            
            C = A+1;
            TEST_ASSERT(A==0);
            TEST_ASSERT(C==1);
            
            C+=1;
            TEST_ASSERT(C==2);
            
            C-=1;
            TEST_ASSERT(C==1);
            
            C = C-1;
            TEST_ASSERT(C==0);
        }
    }
}
    
void test__Matrix(void) {
    _NUM_T_RUN_TEST(test__gen_matrix);
    _NUM_T_K_RUN_TEST(test__multiply_tk);
    _NUM_T_K_RUN_TEST(test__add_tk);
}
    


#endif//TESTING
