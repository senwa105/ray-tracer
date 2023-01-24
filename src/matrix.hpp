#ifndef MATRIX_H
#define MATRIX_H

#include <array>
#include <iostream>



template <typename T, size_t M, size_t N>
class Matrix {
private:
    std::array<T, M*N> entries_{};

public:
    // construct zero matrix by default
    Matrix() = default;
    // construct matrix from array
    Matrix(std::array<T, M*N>&& entries)
        : entries_(entries)
    {}

    size_t GetRowCount() const { return M; }
    size_t GetColCount() const { return N; }

    // use operator() as the subscript operator
    T& operator()(size_t row, size_t col);
    const T& operator()(size_t row, size_t col) const;

    // // scalar addition
    // friend Matrix<T, M, N> operator+<>(const Matrix<T, M, N>& m, const T& s);
    // friend Matrix<T, M, N> operator+<>(const T& s, const Matrix<T, M, N>& m);
    // // scalar subtraction
    // friend Matrix<T, M, N> operator-<>(const Matrix<T, M, N>& m, const T& s);
    // friend Matrix<T, M, N> operator-<>(const T& s, const Matrix<T, M, N>& m);
    // // scalar multiplication
    // friend Matrix<T, M, N> operator*<>(const Matrix<T, M, N>& m, const T& s);
    // friend Matrix<T, M, N> operator*<>(const T& s, const Matrix<T, M, N>& m);

    // // matrix addition
    // friend Matrix<T, M, N> operator+<>(const Matrix<T, M, N>& m1, const Matrix<T, M, N>& m2);
    // // matrix subtraction
    // friend Matrix<T, M, N> operator-<>(const Matrix<T, M, N>& m1, const Matrix<T, M, N>& m2);
    // // matrix multiplication
    // template <int O>
    // friend Matrix<T, M, O> operator*(const Matrix<T, M, N>& m1, const Matrix<T, N, O>& m2);

    // // negation
    // Matrix<T, M, N> operator-() const;

    // // comparison
    // friend bool operator==<>(const Matrix& m1, const Matrix& m2);
    // friend bool operator!=<>(const Matrix& m1, const Matrix& m2);

    // operator <<
    friend std::ostream& operator<<<>(std::ostream& os, const Matrix<T, M, N>& m);
};

template <typename T, size_t M, size_t N>
Matrix<T, M, N> operator+(const Matrix<T, M, N>& m, const T& s) {
    
}

template <typename T, size_t M, size_t N>
T& Matrix<T, M, N>::operator()(size_t row, size_t col) {
    return entries_[row*M + col];
}

template <typename T, size_t M, size_t N>
const T& Matrix<T, M, N>::operator()(size_t row, size_t col) const {
    return entries_[row*M + col];
}

template <typename T, size_t M, size_t N>
std::ostream& operator<<(std::ostream& os, const Matrix<T, M, N>& m) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++)
            os << m(i, j) << ' ';
        os << '\n';
    }

    return os;
}

#endif