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

#include "Container_Multi_Level.hpp"

#ifdef TESTING
#include "unity.h"
#define ASSERT(...) TEST_ASSERT(__VA_ARGS__)
#else
#include <cassert>
#define ASSERT(...) assert(__VA_ARGS__)
#endif

namespace matrix {

typedef std::pair<int,int> Shape;
typedef Shape Position;
    
template<class T>
class Matrix {
    typedef std::vector<T> row_type;
    typedef Container_Multi_Level<std::vector<row_type>,row_type,T> tMatrix;
    
    tMatrix matrix;
    void init_matrix(int cols = 1, int rows = 1) {
        matrix.clear();
        for (int c = 0; c<cols; c++) {
            matrix.push_back(std::vector<T>(rows));
        }
    };
public:
    Matrix (std::vector<std::vector<T>>* p_matrix) : matrix(p_matrix->begin(),p_matrix->end) {}
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
        for (auto it = matrix.begin(); it != matrix.end(); it++) {
            *it *= f;
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
        for (auto it = A.matrix.begin(); it != A.matrix.end(); it++) {
            *it += f;
        }
        return A;
    }
    template<class K>
    void operator+=(K f) {
        for (auto it = matrix.begin(); it != matrix.end(); it++) {
            *it += f;
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
        for (auto it = matrix.begin(); it != matrix.end(); it++) {
            if (*it != k) return false;
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
    
    
    typedef typename tMatrix::iterator iterator;
    typedef typename tMatrix::const_iterator const_iterator;
    
    // Iterator Creator
    iterator begin(void) {
        return matrix.begin();
    }
    iterator end(void) {
        return matrix.end();
    }
    const_iterator begin(void) const {
        return matrix.cbegin();
    }
    const_iterator end(void) const {
        return matrix.cend();
    }
    const_iterator cbegin(void) const {
        return matrix.cbegin();
    }
    const_iterator cend(void) const {
        return matrix.cend();
    }
    
// Iterator Init
    Matrix (iterator be, iterator end):matrix(be,end) { }
    Matrix (tMatrix* p_matrix) : matrix(p_matrix->begin(),p_matrix->end) {}
    
// Transition Functions
    void leaky_relu(float alpha = 0.0) {
        for (auto cit = matrix.begin(); cit != matrix.end(); cit++) {
            for (auto rit = (*cit).begin(); rit < (*cit).end(); rit++) {
                if (*rit < 0) {
                    *rit *= alpha;
                }
            }
        }
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

};

void test__Matrix(void);



#endif /* Matrix_h */
