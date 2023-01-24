#ifndef MATRIX_H
#define MATRIX_H

#include <array>
#include <iostream>

constexpr double EPSILON = 0.00001;     // allowed error for floating point comparison

template <typename T, size_t M, size_t N> class Matrix;
template <size_t M, size_t N> class MatrixFloat;

// typedefs for common matrices
typedef Matrix<int, 2, 2> Matrix2i;
typedef Matrix<int, 3, 3> Matrix3i;
typedef Matrix<int, 4, 4> Matrix4i;
typedef MatrixFloat<2, 2> Matrix2f;
typedef MatrixFloat<3, 3> Matrix3f;
typedef MatrixFloat<4, 4> Matrix4f;

template <typename T, size_t M, size_t N>
class Matrix {
protected:
    std::array<T, M*N> entries_{};

public:
    // construct zero matrix by default
    constexpr Matrix() = default;
    // construct matrix from array literal
    constexpr Matrix(const std::array<T, M*N> list) {
        for (int i = 0; i < M*N; ++i)
            entries_[i] = list[i];
    }

    size_t GetRowCount() const { return M; }
    size_t GetColCount() const { return N; }

    // use operator() as the subscript operator
    T& operator()(size_t row, size_t col)             { return entries_[row*M + col]; }
    const T& operator()(size_t row, size_t col) const { return entries_[row*M + col]; }

    // scalar addition
    friend constexpr Matrix operator+(const Matrix& m, const T& s) {
        std::array new_entries = m.entries_;
        for (T &e : new_entries)
            e += s;
        return Matrix(new_entries);
    }

    friend constexpr Matrix operator+(const T& s, const Matrix& m) {
        return m + s;
    }

    // scalar subtraction
    friend constexpr Matrix<T, M, N> operator-(const Matrix& m, const T& s) {
        std::array new_entries = m.entries_;
        for (T &e : new_entries)
            e -= s;
        return Matrix(new_entries);
    }

    friend constexpr Matrix<T, M, N> operator-(const T& s, const Matrix& m) {
        std::array new_entries = m.entries_;
        for (T &e : new_entries)
            e = s - e;
        return Matrix(new_entries);
    }
    // scalar multiplication
    friend constexpr Matrix<T, M, N> operator*(const Matrix& m, const T& s) {
        std::array new_entries = m.entries_;
        for (T &e : new_entries)
            e *= s;
        return Matrix(new_entries);
    }

    friend constexpr Matrix<T, M, N> operator*(const T& s, const Matrix& m) {
        return m * s;
    }

    // // matrix addition
    // friend Matrix<T, M, N> operator+(const Matrix& m1, const Matrix& m2);
    // // matrix subtraction
    // friend Matrix<T, M, N> operator-(const Matrix& m1, const Matrix& m2);
    // // matrix multiplication
    // template <int O>
    // friend Matrix<T, M, O> operator*(const Matrix<T, M, N>& m1, const Matrix<T, N, O>& m2);

    // negation
    Matrix<T, M, N> operator-() const {
        return *this * -1;
    }

    // comparison
    friend constexpr bool operator==(const Matrix<T, M, N>& m1, const Matrix<T, M, N>& m2) {
        for (int i = 0; i < M*N; ++i)
            if (m1.entries_[i] != m2.entries_[i])
                return false;
        return true;
    }

    friend constexpr bool operator!=(const Matrix<T, M, N>& m1, const Matrix<T, M, N>& m2) {
        for (int i = 0; i < M*N; ++i)
            if (m1.entries_[i] != m2.entries_[i])
                return true;
        return false;
    }

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

// Pseudo partial template specialization for floats
template <size_t M, size_t N>
class MatrixFloat : public Matrix<float, M, N> {
public:
    constexpr MatrixFloat()
        : Matrix<float, M, N>()
    {}

    constexpr MatrixFloat(const std::array<float, M*N> list)
        : Matrix<float, M, N>(list)
    {}

    friend constexpr bool operator==(const MatrixFloat& m1, const MatrixFloat& m2) {
        for (int i = 0; i < M*N; ++i)
            if (abs(m1.entries_[i] - m2.entries_[i]) > EPSILON)
                return false;
        return true;
    }

    friend constexpr bool operator!=(const MatrixFloat& m1, const MatrixFloat& m2) {
        for (int i = 0; i < M*N; ++i)
            if (abs(m1.entries_[i] - m2.entries_[i]) > EPSILON)
                return true;
        return false;
    }
};

// Pseudo partial template specialization for doubles



#endif