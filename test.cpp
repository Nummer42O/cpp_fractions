#include "fraction/fraction.hpp"

#include <cstdlib>
#include <iostream>

int main(int argc, char* argv[]) {
    frac::Fraction f1 = 0.5,
                   f2(5, 4, false),
                   f3(5, 4, true);

    std::cout << f1 << '\n'
              << f2 << '\n'
              << f3 << std::endl;

    return 0;
}