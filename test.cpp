#include "fraction/fraction.hpp"

#include <cstdlib>
#include <iostream>

int main(int argc, char* argv[]) {
    //Constructors
    frac::Fraction f1(0.5),         //from double
                   f2(5ul, 4ul, false), //from num, denom, sign
                   f3(5ul, 4ul, true),  //from num, denom, sign
                   f4;              //default constructor (1/1)
    std::cout << f1 << '\n'
              << f2 << '\n'
              << f3 << '\n'
              << f4 << '\n';

    std::cout << "double of 1/2: " << static_cast<double>(f1) << '\n'
              << "long of 1/2: " << static_cast<long>(f1) << '\n'
              << "size_t of 1/2: " << static_cast<size_t>(f1) << '\n';

    std::cout << "numerator of f3: " << f3.getNumerator() << '\n'
              << "denominator of f3: " << f3.getDenominator() << '\n';

    { //Addition
        frac::Fraction frac = f1,
                       frac_iadd_f = f1,
                       frac_iadd_d = f1;

        frac_iadd_f += f1;
        frac_iadd_d += .5;

        std::cout << "temporary: frac = 1/2\n"
                  << "frac++ (pre, output, post): " << frac << ", " << frac++ << ", " << frac << '\n'
                  << "++frac (pre, output, post): " << frac << ", " << ++frac << ", " << frac << '\n'
                  << "frac + 1/2 = " << frac + f2 << '\n'
                  << "frac + 0.5 = " << frac + .5 << '\n'
                  << "0.5 + frac = " << .5 + frac << '\n'
                  << "frac += 1/2: " << frac_iadd_f << '\n'
                  << "frac += 0.5: " << frac_iadd_d << '\n';
    }

    { //Subtraction
        frac::Fraction frac = f1,
                       frac_isub_f = f1,
                       frac_isub_d = f1;

        frac_isub_f -= f1;
        frac_isub_d -= .5;

        std::cout << "temporary: frac = 1/2\n"
                  << "frac-- (pre, output, post): " << frac << ", " << frac-- << ", " << frac << '\n'
                  << "--frac (pre, output, post): " << frac << ", " << --frac << ", " << frac << '\n'
                  << "frac - 1/2 = " << frac - f2 << '\n'
                  << "frac - 0.5 = " << frac - .5 << '\n'
                  << "0.5 - frac = " << .5 - frac << '\n'
                  << "frac -= 1/2: " << frac_isub_f << '\n'
                  << "frac -= 0.5: " << frac_isub_d << '\n';
    }

    { //Multiplication
        frac::Fraction frac = f1,
                       frac_imul_f = f1,
                       frac_imul_d = f1;

        frac_imul_f *= f1;
        frac_imul_d *= .5;

        std::cout << "temporary: frac = 1/2\n"
                  << "frac * 1/2 = " << frac * f2 << '\n'
                  << "frac * 0.5 = " << frac * .5 << '\n'
                  << "0.5 * frac = " << .5 * frac << '\n'
                  << "frac *= 1/2: " << frac_imul_f << '\n'
                  << "frac *= 0.5: " << frac_imul_d << '\n';
    }

    { //Division
        frac::Fraction frac = f1,
                       frac_idiv_f = f1,
                       frac_idiv_d = f1;

        frac_idiv_f /= f1;
        frac_idiv_d /= .5;

        std::cout << "temporary: frac = 1/2\n"
                  << "frac / 1/2 = " << frac / f2 << '\n'
                  << "frac / 0.5 = " << frac / .5 << '\n'
                  << "0.5 / frac = " << .5 / frac << '\n'
                  << "frac /= 1/2: " << frac_idiv_f << '\n'
                  << "frac /= 0.5: " << frac_idiv_d << '\n';
    }

    { //Modulo
        frac::Fraction frac = f1,
                       frac_imod_f = f1,
                       frac_imod_d = f1;

        frac_imod_f %= f1;
        frac_imod_d %= .5;

        std::cout << "temporary: frac = 1/2\n"
                  << "frac % 1/2 = " << frac % f2 << '\n'
                  << "frac % 0.5 = " << frac % .5 << '\n'
                  << "frac %= 1/2: " << frac_imod_f << '\n'
                  << "frac %= 0.5: " << frac_imod_d << '\n';
    }

    //Comparisons
    std::cout << "-5/4 < 1/2: " << (f3 < f1) << '\n'
              << "-5/4 < 0.5: " << (f3 < .5) << '\n'
              << "0.5 < -5/4: " << (.5 < f3) << '\n'

              << "-5/4 > 1/2: " << (f3 > f1) << '\n'
              << "-5/4 > 0.5: " << (f3 > .5) << '\n'
              << "0.5 > -5/4: " << (.5 > f3) << '\n'

              << "-5/4 <= 1/2: " << (f3 <= f1) << '\n'
              << "-5/4 <= 0.5: " << (f3 <= .5) << '\n'
              << "0.5 <= -5/4: " << (.5 <= f3) << '\n'

              << "-5/4 >= 1/2: " << (f3 >= f1) << '\n'
              << "-5/4 >= 0.5: " << (f3 >= .5) << '\n'
              << "0.5 >= -5/4: " << (.5 >= f3) << '\n'

              << "-5/4 == 1/2: " << (f3 == f1) << '\n'
              << "-5/4 == 0.5: " << (f3 == .5) << '\n'
              << "0.5 == -5/4: " << (.5 == f3) << '\n'

              << "-5/4 != 1/2: " << (f3 != f1) << '\n'
              << "-5/4 != 0.5: " << (f3 != .5) << '\n'
              << "0.5 != -5/4: " << (.5 != f3) << '\n';

    { //Math methods
        std::cout << "(Output format: friend, method\n"
                  << "pow(1/2, 2) = " << frac::pow(f1, 2) << ", " << frac::Fraction(f1).pow(2) << '\n'
                  << "sqrt(1/2)   = " << frac::sqrt(f1) << ", " << frac::Fraction(f1).sqrt() << '\n'
                  << "exp(1/2)    = " << frac::exp(f1) << ", " << frac::Fraction(f1).exp() << '\n'
                  << "exp2(1/2)   = " << frac::exp2(f1) << ", " << frac::Fraction(f1).exp2() << '\n'
                  << "log(1/2)    = " << frac::log(f1) << ", " << frac::Fraction(f1).log() << '\n'
                  << "log10(1/2)  = " << frac::log10(f1) << ", " << frac::Fraction(f1).log10() << '\n'
                  << "log2(1/2)   = " << frac::log2(f1) << ", " << frac::Fraction(f1).log2() << '\n'
                  << "abs(1/2)    = " << frac::abs(f1) << ", " << frac::Fraction(f1).abs() << '\n'
                  << "ceil(1/2)   = " << frac::ceil(f1) << ", " << frac::Fraction(f1).ceil() << '\n'
                  << "floor(1/2)  = " << frac::floor(f1) << ", " << frac::Fraction(f1).floor() << '\n'
                  << "round(1/2)  = " << frac::round(f1) << ", " << frac::Fraction(f1).round() << '\n';
    }

    { //Manipulation methods
        frac::Fraction temp = f1;

        std::cout << "invert(1/2)      = " << frac::invert(f1) << ", " << frac::Fraction(f1).invert() << '\n'
                  << "expand(1/2, 2)   = " << frac::expand(f1, 2) << ", " << temp.expand(2) << '\n'
                  << "truncate(2/4, 2) = " << frac::truncate(temp, 2) << ", " << temp.truncate(2) << '\n';
    }

    return 0;
}