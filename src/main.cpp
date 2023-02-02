#include <iostream>

#include "matrix.hpp"

int main() {
    Matrix2i a({1, 2, 3, 4});
    Matrix2i b({3, 4, 5, 6});

    auto add = a + 2;

    std::cout << (a + 2 == b) << '\n';
}