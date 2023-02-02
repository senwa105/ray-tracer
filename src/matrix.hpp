#ifndef MATRIX_H
#define MATRIX_H

#include <array>
#include <iostream>
#include <cmath>
#include <concepts>

constexpr float EPSILON = 0.00001;     // allowed error for floating point comparison

template <typename T, size_t M, size_t N> 
requires std::integral<T> || std::floating_point<T>
class Matrix;

template <typename T, size_t M, size_t N> 
requires std::integral<T>
class MatrixIntegral;

template <typename T, size_t M, size_t N>
requires std::floating_point<T>
class MatrixFloating;

// typedefs for common matrices
typedef Matrix<int, 2, 2> Matrix2i;
typedef Matrix<int, 3, 3> Matrix3i;
typedef Matrix<int, 4, 4> Matrix4i;
typedef Matrix<int, 2, 1> Vector2i;
typedef Matrix<int, 3, 1> Vector3i;
typedef Matrix<int, 4, 1> Vector4i;
typedef Matrix<float, 2, 2> Matrix2f;
typedef Matrix<float, 3, 3> Matrix3f;
typedef Matrix<float, 4, 4> Matrix4f;
typedef Matrix<float, 2, 1> Vector2f;
typedef Matrix<float, 3, 1> Vector3f;
typedef Matrix<float, 4, 1> Vector4f;

template <typename T, size_t M, size_t N>
requires std::integral<T> || std::floating_point<T>
class Matrix {
protected:
    std::array<T, M*N> entries_{};

public:
    // construct zero matrix by default
    constexpr Matrix() = default;

    // construct matrix from array literal
    constexpr Matrix(const std::array<T, M*N> list) {
        for (size_t i = 0; i < M*N; ++i)
            entries_[i] = list[i];
    }

    // construct identity matrix
    static constexpr Matrix Identity() {
        static_assert(M == N, "Identity matrix can only be constructed for square matrices");

        std::array<T, M*N> entries{};
        for (size_t i = 0; i < N; ++i)
            entries[i*N + i] = 1;
        return Matrix(entries);
    }

    size_t GetRowCount() const { return M; }
    size_t GetColCount() const { return N; }

    // use operator() as the subscript operator
    T& operator()(size_t row, size_t col)             { return entries_[row*N + col]; }
    const T& operator()(size_t row, size_t col) const { return entries_[row*N + col]; }

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

    // matrix addition
    friend Matrix<T, M, N> operator+(const Matrix& m1, const Matrix& m2) {
        std::array new_entries = m1.entries_;
        for (int i = 0; i < M*N; ++i)
            new_entries[i] += m2.entries_[i];
        return new_entries;
    }

    // matrix subtraction
    friend Matrix<T, M, N> operator-(const Matrix& m1, const Matrix& m2) {
        std::array new_entries = m1.entries_;
        for (int i = 0; i < M*N; ++i)
            new_entries[i] -= m2.entries_[i];
        return new_entries;
    }

    // matrix multiplication
    template <size_t O>
    friend Matrix<T, M, O> operator*(const Matrix<T, M, N>& m1, const Matrix<T, N, O>& m2) {
        Matrix<T, M, O> output;
        for (size_t row = 0; row < M; ++row) {
            for (size_t col = 0; col < O; ++col) {
                for (size_t i = 0; i < N; ++i) {
                    auto mm = m1(row, i);
                    auto nn = m2(i, col);
                    output(row, col) += m1(row, i) * m2(i, col);
                }
            }
        }

        return output;
    }

    // negation
    Matrix<T, M, N> operator-() const {
        return *this * -1;
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

    // comparison
    friend constexpr bool operator==<T, M, N>(const Matrix& m1, const Matrix& m2);
    friend constexpr bool operator!=<T, M, N>(const Matrix& m1, const Matrix& m2);

    // Vector Functions

    T& X() {
        static_assert(M >= 1 && N == 1, "Must be a vector in at least 1 dimension");
        return entries_[0];
    }

    const T& X() const {
        static_assert(M >= 1 && N == 1, "Must be a vector in at least 1 dimension");
        return entries_[0];
    }

    T& Y() {
        static_assert(M >= 2 && N == 1, "Must be a vector in at least 2 dimensions");
        return entries_[1];
    }

    const T& Y() const {
        static_assert(M >= 2 && N == 1, "Must be a vector in at least 2 dimensions");
        return entries_[1];
    }

    T& Z() {
        static_assert(M >= 3 && N == 1, "Must be a vector in at least 3 dimensions");
        return entries_[2];
    }

    const T& Z() const {
        static_assert(M >= 3 && N == 1, "Must be a vector in at least 3 dimensions");
        return entries_[2];
    }

    T& W() {
        static_assert(M >= 4 && N == 1, "Must be a vector in at least 4 dimension");
        return entries_[3];
    }

    const T& W() const {
        static_assert(M >= 4 && N == 1, "Must be a vector in at least 4 dimension");
        return entries_[3];
    }

    const T Norm() const {
        static_assert(N == 1, "Norm is only defined for vectors; number of cols must be one");

        T sum = 0;
        for (T e : entries_)
            sum += e * e;
        return sqrt(sum);
    }

    friend constexpr Matrix<T, M, 1> Normalize(Matrix& v) {
        static_assert(N == 1, "Normalize is only defined for vectors; number of cols must be one");

        T norm = v.Norm();
        std::array new_entries = v.entries_;
        for (T& e : new_entries)
            e /= norm;
        
        return Matrix(new_entries);
    } 

    friend constexpr T Dot(const Matrix& v1, const Matrix& v2) {
        static_assert(N == 1, "Dot is only defined for vectors; number of cols must be one");

        T dot = 0;
        for (int i = 0; i < M; ++i)
            dot += v1.entries_[i] * v2.entries_[i];
        return dot;
    }

    friend constexpr Matrix<T, 3, 1> Cross(const Matrix& v1, const Matrix& v2) {
        static_assert(N == 1, "Cross is only defined for vectors; number of cols must be one");
        static_assert(M == 3, "Cross is only defined for 3-dimensional vectors");

        return Matrix({v1.Y() * v2.Z() - v1.Z() * v2.Y(), 
                       v1.Z() * v2.X() - v1.X() * v2.Z(), 
                       v1.X() * v2.Y() - v1.Y() * v2.X()});
    }
};

template <std::integral T, size_t M, size_t N>
constexpr bool operator==(const Matrix<T, M, N>& m1, const Matrix<T, M, N>& m2) {
    for (int i = 0; i < M*N; ++i)
        if (m1.entries_[i] != m2.entries_[i])
            return false;
    return true;
}

template <std::integral T, size_t M, size_t N>
constexpr bool operator!=(const Matrix<T, M, N>& m1, const Matrix<T, M, N>& m2) {
    for (int i = 0; i < M*N; ++i)
        if (m1.entries_[i] != m2.entries_[i])
            return true;
    return false;
}

template <std::floating_point T, size_t M, size_t N>
constexpr bool operator==(const Matrix<T, M, N>& m1, const Matrix<T, M, N>& m2) {
        for (size_t i = 0; i < M*N; ++i)
            if (std::abs(m1.entries_[i] - m2.entries_[i]) > EPSILON)
                return false;
        return true;
}

template <std::floating_point T, size_t M, size_t N>
constexpr bool operator!=(const Matrix<T, M, N>& m1, const Matrix<T, M, N>& m2) {
        for (size_t i = 0; i < M*N; ++i)
            if (std::abs(m1.entries_[i] - m2.entries_[i]) > EPSILON)
                return true;
        return false;
}

#endif