#ifndef MATRIX_H
#define MATRIX_H

#include <array>
#include <iostream>

template <typename T, size_t M, size_t N> class Matrix;
typedef Matrix<int,   2, 2> Matrix2i;
typedef Matrix<int,   3, 3> Matrix3i;
typedef Matrix<int,   4, 4> Matrix4i;
typedef Matrix<float, 2, 2> Matrix2f;
typedef Matrix<float, 3, 3> Matrix3f;
typedef Matrix<float, 4, 4> Matrix4f;

template <typename T, size_t M, size_t N>
class Matrix {
private:
    std::array<T, M*N> entries_{};

public:
    // construct zero matrix by default
    constexpr Matrix() = default;
    // construct matrix from array literal
    constexpr Matrix(const std::array<const T, M*N> list) {
        for (int i = 0; i < M*N; ++i)
            entries_[i] = list[i];
    }

    size_t GetRowCount() const { return M; }
    size_t GetColCount() const { return N; }

    // use operator() as the subscript operator
    T& operator()(size_t row, size_t col)             { return entries_[row*M + col]; }
    const T& operator()(size_t row, size_t col) const { return entries_[row*M + col]; }

    // // scalar addition
    // friend constexpr Matrix operator+(const Matrix& m, const T& s) {
    //     for (T &e : entries_)
    //         e += s;
    // }

    // friend constexpr Matrix operator+(const T& s, const Matrix& m) {
    //     for (T &e : entries_)
    //         e += s;
    // }

    // // scalar subtraction
    // friend Matrix<T, M, N> operator-(const Matrix& m, const T& s);
    // friend Matrix<T, M, N> operator-(const T& s, const Matrix& m);
    // // scalar multiplication
    // friend Matrix<T, M, N> operator*(const Matrix& m, const T& s);
    // friend Matrix<T, M, N> operator*(const T& s, const Matrix& m);

    // // matrix addition
    // friend Matrix<T, M, N> operator+(const Matrix& m1, const Matrix& m2);
    // // matrix subtraction
    // friend Matrix<T, M, N> operator-(const Matrix& m1, const Matrix& m2);
    // // matrix multiplication
    // template <int O>
    // friend Matrix<T, M, O> operator*(const Matrix& m1, const Matrix& m2);

    // // negation
    // Matrix<T, M, N> operator-() const;

    // // comparison
    // friend bool operator==(const Matrix& m1, const Matrix& m2);
    // friend bool operator!=(const Matrix& m1, const Matrix& m2);

    // operator <<
    friend std::ostream& operator<<(std::ostream& os, const Matrix& m) {
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++)
                os << m(i, j) << ' ';
            os << '\n';
        }

        return os;
    }
};

#endif