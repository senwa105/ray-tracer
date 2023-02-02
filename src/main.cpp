#include <iostream>

#include "matrix.hpp"

int main() {
    Matrix2f a({1.00001f, 2, 3, 4});
    Matrix2f b({3, 4, 5, 6});

    auto add = a + 2;

    std::cout << (a + 2 == b) << '\n';
}