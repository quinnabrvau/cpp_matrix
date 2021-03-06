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


#define _MAT_RUN_TEST_NUM_TYPE(func)       \
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

#define ___MAT_RUN_TEST(func,type1,type2)       \
do {                                    \
void_func func ## _ ## type1 ## _ ## type2      \
= func < type1, type2 >;                       \
RUN_TEST( (func ## _ ## type1 ## _ ## type2) ); \
} while(false)

#define __MAT_RUN_TEST(func, type1)            \
do {                                       \
___MAT_RUN_TEST( func,type1,char );            \
___MAT_RUN_TEST( func,type1,unchar__A );       \
___MAT_RUN_TEST( func,type1,unshort__A );      \
___MAT_RUN_TEST( func,type1,short );           \
___MAT_RUN_TEST( func,type1,int );             \
___MAT_RUN_TEST( func,type1,unint__A );        \
___MAT_RUN_TEST( func,type1,long );            \
___MAT_RUN_TEST( func,type1,unlong__A );       \
___MAT_RUN_TEST( func,type1,longlong__A );     \
___MAT_RUN_TEST( func,type1,float );           \
___MAT_RUN_TEST( func,type1,double );          \
___MAT_RUN_TEST( func,type1,longdouble__A );   \
} while(false)

#define _MAT_RUN_TEST(func)      \
do {                                 \
__MAT_RUN_TEST( func, char );            \
__MAT_RUN_TEST( func, unchar__A );       \
__MAT_RUN_TEST( func, short );           \
__MAT_RUN_TEST( func, unshort__A );      \
__MAT_RUN_TEST( func, int );             \
__MAT_RUN_TEST( func, unint__A );        \
__MAT_RUN_TEST( func, long );            \
__MAT_RUN_TEST( func, unlong__A );       \
__MAT_RUN_TEST( func, longlong__A );     \
__MAT_RUN_TEST( func, float );           \
__MAT_RUN_TEST( func, double );          \
__MAT_RUN_TEST( func, longdouble__A );   \
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

template <class T>
void test__iter_size(void) {
    for (int i = 1; i < 20; i++) {
        for(int j = 1; j < i; j++) {
            Matrix<T> A = Matrix_Ones<T>(Shape(i,j));
            do {
                auto it = A.begin();
                int index = 0;
                while (it != A.end()) {
                    it++; index++;
                }
                TEST_ASSERT_EQUAL(A.size(), index);
            }while(0);
            do {
                auto it = A.end();
                int index = 0;
                while (it != A.begin()) {
                    it--; index++;
                }
                TEST_ASSERT_EQUAL(A.size(), index);
            }while(0);
        }
    }
}

template <class T>
void test__iter(void) {
    for (int i = 1; i < 20; i++) {
        for(int j = 1; j < i; j++) {
            Matrix<T> A = Matrix_Ones<T>(Shape(i,j));
            Matrix<T> B(A.begin(),A.end());
            TEST_ASSERT(A==B);
            for (auto it = B.begin(); it != B.end(); it++) {
                (*it) += 1;
            }
            Matrix<T> C = A+1;
            TEST_ASSERT( C==B );
            TEST_ASSERT( C==2 );
        }
    }
}
void test__Matrix(void) {
    _MAT_RUN_TEST_NUM_TYPE(test__gen_matrix);
    _MAT_RUN_TEST(test__multiply_tk);
    _MAT_RUN_TEST(test__add_tk);
    _MAT_RUN_TEST_NUM_TYPE(test__iter_size);
    _MAT_RUN_TEST_NUM_TYPE(test__iter);
}
    


#endif//TESTING
