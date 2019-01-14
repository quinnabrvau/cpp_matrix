//
//  Matrix.hpp
//  TEST
//
//  Created by Quinn Abrahams-Vaughn on 1/10/19.
//

#ifndef Matrix_h
#define Matrix_h

#include <vector>
#include <iterator>
#include <utility>

typedef std::pair<int,int> Shape;
typedef Shape Position;

template<class T>
class Matrix {
    std::vector<std::vector<T>> matrix;
    void init_matrix(int cols = 1, int rows = 1) {
        matrix.clear();
        for (int c = 0; c<cols; c++) {
            matrix.push_back(std::vector<T>(rows));
        }
    };
public:
    Matrix (std::vector<std::vector<T>>* p_matrix) : matrix(p_matrix-begin(),p_matrix->end) {}
    Matrix(Shape s) {
        init_matrix(s.first, s.second);
    }
    Matrix(int cols = 1, int rows = 1) {
        init_matrix(cols,rows);
    };
    Matrix copy(void) {
        Shape s = shape();
        Matrix A(s);
        for (int i = 0; i<s.first; i++) {
            A.matrix[i] = std::vector<T>(matrix[i].begin(), matrix[i].end());
        }
        return A;
    }
    
    int size(void) const {
        int s = matrix.size();
        if (s==0) return 0;
        return s * matrix[0].size();
    }
    Shape shape(void) const{
        int s = matrix.size();
        if (s>0)
            return std::pair<int,int>(s,matrix[0].size());
        else
            return std::pair<int,int>(0,0);
    }
    
    T& operator[](Position index) {return matrix[index.first][index.second];};
    std::vector<T>& operator[](int col) { return matrix[col]; };
    T& operator()(int col, int row) {return matrix[col][row];};


    template<class K>
    Shape output_shape(Matrix<K>& A) {
        Shape s = this->shape();
        Shape sa = A.shape();
        return Shape(s.first, sa.second);
    }
    template<class K>
    bool can_multiply(Matrix<K>& A) {
        Shape s = this->shape();
        Shape sa = A.shape();
        return s.second==sa.first;
    }
private:
    template<class K, class L>
    void static_multiply(Matrix<T>& A, Matrix<K>& B, Matrix<L>& out) {
        Shape sa = A.shape();
        Shape sb = B.shape();
        Shape sout = out.shape();
        ASSERT(sout == A.output_shape(B)); // check output shape
        ASSERT(sa.second == sb.first); // check middle dimensions
        //TODO multiply
        for (int i = 0; i < sa.first; i++) {
            for (int j = 0; j < sb.second; j++) {
                L* l = &out[i][j];
                *l = 0;
                for (int k = 0; k<sa.second; k++) {
                    *l += A(i,k)*B(k,j);
                }
            }
        }
    }
public:
    template<class K>
    Matrix operator*(Matrix<K>& A) {
        ASSERT(can_multiply(A));
        Matrix B(output_shape(A));
        static_multiply(*this,A,B);
        return B;
    }
    template<class K>
    Matrix operator*(K f) {
        Matrix A = *this;
        A *= f;
        return A;
    }
    template<class K>
    void operator*=(K f) {
        for (auto rit = matrix.begin(); rit != matrix.end(); rit++) {
            for (auto cit = (*rit).begin(); cit != (*rit).end(); cit++) {
                *cit *= f;
            }
        }
    }
    template<class K>
    bool can_add(Matrix<K>& A) {
        return shape() == A.shape();
    }
    template<class K>
    void static_add(Matrix<K>& A, Matrix& B) {
        Shape s = this->shape();
        Shape sb = B.shape();
        ASSERT(can_add(A))
        ASSERT(sb == s);
        for (int c = 0; c < s.first; c++ ) {
            for (int r = 0; r < s.second; r++) {
                B(c,r) = matrix[c][r] + A(c,r);
            }
        }
    }
    template<class K>
    Matrix operator+(Matrix<K>& A) {
        ASSERT(can_add(A));
        Matrix B(shape());
        static_add(A, B);
        return B;
    }
    template<class K>
    void operator+=(Matrix<K>& A) {
        static_add(A, this);
    }
    template<class K>
    Matrix operator+(K f) {
        Matrix A = *this;
        for (auto rit = A.matrix.begin(); rit != A.matrix.end(); rit++) {
            for (auto cit = (*rit).begin(); cit != (*rit).end(); cit++) {
                *cit += f;
            }
        }
        return A;
    }
    template<class K>
    void operator+=(K f) {
        for (auto rit = matrix.begin(); rit != matrix.end(); rit++) {
            for (auto cit = (*rit).begin(); cit != (*rit).end(); cit++) {
                *cit += f;
            }
        }
    }
    
    Matrix operator-(void) {
        Matrix A = *this;
        for (auto rit = A.matrix.begin(); rit != A.matrix.end(); rit++) {
            for (auto cit = (*rit).begin(); cit != (*rit).end(); cit++) {
                *cit = -(*cit);
            }
        }
        return A;
    }
    template<class K>
    Matrix operator-(K f) {
        return *this+(-f);
    }
    template<class K>
    void operator-=(K f) {
        *this += (-f);
    }
    
    
// Boolean Checks
    template<class K>
    bool operator==(Matrix<K>& A) {
        Shape s = shape(); Shape sa = A.shape();
        if (s.first != sa.first || s.second != sa.second) return false;
        for (int i = 0; i < s.first; i++) {
            for (int j = 0; j < s.second; j++) {
                if (matrix[i][j] != A(i,j)) return false;
            }
        }
        return true;
    }
    template<class K>
    bool operator==(K k) {
        for (auto rit = matrix.begin(); rit != matrix.end(); rit++) {
            for (auto cit = (*rit).begin(); cit != (*rit).end(); cit++) {
                if (*cit != k) return false;
            }
        }
        return true;
    }

    template<class K>
    bool operator!=(Matrix<K>& A) {
        return !(*this == A);
    }

    template<class K>
    bool operator!=(K k) {
        return !(*this == k);
    }
    
    template<class K>
    bool operator<(K k) {
        for (auto rit = matrix.begin(); rit != matrix.end(); rit++) {
            for (auto cit = (*rit).begin(); cit != (*rit).end(); cit++) {
                if (*cit >= k) return false;
            }
        }
        return true;
    }
    
    template<class K>
    bool operator<=(K k) {
        for (auto rit = matrix.begin(); rit != matrix.end(); rit++) {
            for (auto cit = (*rit).begin(); cit != (*rit).end(); cit++) {
                if (*cit > k) return false;
            }
        }
        return true;
    }
    
    template<class K>
    bool operator>(K k) {
        for (auto rit = matrix.begin(); rit != matrix.end(); rit++) {
            for (auto cit = (*rit).begin(); cit != (*rit).end(); cit++) {
                if (*cit <= k) return false;
            }
        }
        return true;
    }
    
    template<class K>
    bool operator>=(K k) {
        for (auto rit = matrix.begin(); rit != matrix.end(); rit++) {
            for (auto cit = (*rit).begin(); cit != (*rit).end(); cit++) {
                if (*cit < k) return false;
            }
        }
        return true;
    }

    typedef typename std::vector<std::vector<T>>::iterator c_iterator; //column iterator
    typedef typename std::vector<T>::iterator r_iterator;              //row iterator
    typedef typename std::vector<std::vector<T>>::const_iterator c_iterator_const; //column iterator const
    typedef typename std::vector<T>::const_iterator r_iterator_const;              //row iterator const

    class iterator {
        c_iterator cit, end;
        r_iterator rit;
    public:
        iterator(c_iterator _c_it,r_iterator _r_it,c_iterator _end) :
            cit(_c_it), rit(_r_it), end(_end) {}
        bool operator==(iterator const * const it) const {
            if (this->cit != it->cit) return false;
            if (this->rit != it->rit) return false;
            return true;
        }
        void operator++(void) const {
            if ((++rit) == (*cit).end()) {
                cit++; 
                if (cit != end) {
                    rit = (*cit).begin();
                }
            }
        }
        void operator--(void) const {
            if (rit == (*cit).begin()) {
                cit--; 
                rit = (*cit).end();
                rit--;
            } else {
                rit--;
            }
        }

        T& operator*(void) {
            return (*rit);
        }

    }
    
    class const_iterator:public iterator {
        const T& operator*(void) const {
            return (*rit);
        }
    }
    
// Iterator Creator
    iterator begin(void) {
        return iterator(matrix.begin(),matrix[0].begin(),matrix.end());
    }
    iterator end(void) {
        return iterator(matrix.end(),matrix.back().end(),matrix.end());
    }
    const_iterator begin(void) const {
        return const_iterator(matrix.begin(),matrix[0].begin(),matrix.end());
    }
    const_iterator end(void) const {
        return const_iterator(matrix.end(),matrix.back().end(),matrix.end());
    }
    const_iterator cbegin(void) const {
        return const_iterator(matrix.cbegin(),matrix[0].cbegin(),matrix.cend());
    }
    const_iterator cend(void) const {
        return const_iterator(matrix.end(),matrix.back().end(),matrix.end());
    }
};


template <class T>
Matrix<T> Matrix_Zeros(Shape shape) {
    Matrix<T> A(shape);
    return A;
}
template <class T>
Matrix<T> Matrix_Zeros(int cols=1, int rows=1) {
    return Matrix_Zeros<T>(Shape(cols,rows));
}

template <class T>
Matrix<T> Matrix_Ones(Shape shape) {
    Matrix<T> A(shape);
    for (int i = 0; i < shape.first; i++) {
        for (int j = 0; j < shape.second; j++) {
            A(i,j) = 1;
        }
    }
    return A;
}
template <class T>
Matrix<T> Matrix_Ones(int cols=1, int rows=1) {
    return Matrix_Ones<T>(Shape(cols,rows));
}

void test__Matrix(void);

#ifdef TESTING
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

typedef unsigned int unint;
typedef unsigned short unshort;
typedef unsigned long unlong;
typedef long long longlong;
typedef long double longdouble;

#define ___RUN_TEST(func,type1,type2)       \
do {                                    \
void_func func ## _ ## type1 ## _ ## type2      \
= func < type1, type2 >;                       \
RUN_TEST( (func ## _ ## type1 ## _ ## type2) ); \
} while(false)

#define RUN_TEST_S(func, type1)                \
do {                                       \
___RUN_TEST( func,type1,int );             \
___RUN_TEST( func,type1,short );           \
___RUN_TEST( func,type1,long );            \
___RUN_TEST( func,type1,longlong );        \
___RUN_TEST( func,type1,unint );           \
___RUN_TEST( func,type1,unshort );         \
___RUN_TEST( func,type1,unlong );          \
___RUN_TEST( func,type1,char );            \
___RUN_TEST( func,type1,float );           \
___RUN_TEST( func,type1,double );          \
___RUN_TEST( func,type1,longdouble );      \
} while(false)

#define _NUM_T_K_RUN_TEST(func)          \
do {                                 \
RUN_TEST_S( func, int );             \
RUN_TEST_S( func, short );           \
RUN_TEST_S( func, long );            \
RUN_TEST_S( func, longlong );        \
RUN_TEST_S( func, unint );           \
RUN_TEST_S( func, unshort );         \
RUN_TEST_S( func, unlong );          \
RUN_TEST_S( func, char );            \
RUN_TEST_S( func, float );           \
RUN_TEST_S( func, double );          \
RUN_TEST_S( func, longdouble );      \
} while(false)

#endif//TESTING


#endif /* Matrix_h */
