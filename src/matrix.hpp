#ifndef MATRIX_H
#define MATRIX_H

#include <array>
#include <iostream>

template <typename T, size_t M, size_t N>
class Matrix {
private:
    std::array<T, M*N> entries;

public:
    size_t GetRowCount() const;
    size_t GetColCount() const;

    // use operator() as the subscript operator
    T& operator()(size_t row, size_t col);
    const T& operator()(size_t row, size_t col) const;

    // scalar addition
    friend Matrix<T, M, N> operator+(const Matrix<T, M, N>& m, const T& s);
    friend Matrix<T, M, N> operator+(const T& s, const Matrix<T, M, N>& m);
    // scalar subtraction
    friend Matrix<T, M, N> operator-(const Matrix<T, M, N>& m, const T& s);
    friend Matrix<T, M, N> operator-(const T& s, const Matrix<T, M, N>& m);
    // scalar multiplication
    friend Matrix<T, M, N> operator*(const Matrix<T, M, N>& m, const T& s);
    friend Matrix<T, M, N> operator*(const T& s, const Matrix<T, M, N>& m);

    // matrix addition
    friend Matrix<T, M, N> operator+(const Matrix<T, M, N>& m1, const Matrix<T, M, N>& m2);
    // matrix subtraction
    friend Matrix<T, M, N> operator-(const Matrix<T, M, N>& m1, const Matrix<T, M, N>& m2);
    // matrix multiplication
    template <int O>
    friend Matrix<T, M, O> operator*(const Matrix<T, M, N>& m1, const Matrix<T, N, O>& m2);

    // negation
    Matrix<T, M, N> operator-() const;

    // operator <<
    friend std::ostream& operator<<(std::ostream& os, const Matrix<T,m,n>& m);
};

#endif