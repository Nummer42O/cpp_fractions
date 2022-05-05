#include "fraction.hpp"

#include <numeric> //lcm, gcd
#include <cmath>
#include <exception>
#include <cstring>
#include <memory>

#define SQRT_TOLERANCE 0.00001
#define  EXP_TOLERANCE 0.0001

namespace frac {
    //private
    Fraction::Fraction(double numerator, double denominator) {
        size_t factor = getDenominator(numerator) * getDenominator(denominator);
        this->numerator   = numerator   * factor;
        this->denominator = denominator * factor;

        truncate();
    }
    Fraction::Fraction(size_t numerator, size_t denominator, bool is_negative, char): numerator(numerator), denominator(denominator), is_negative(is_negative) {}

    size_t Fraction::getDenominator(double value) {
        std::string string_value = std::to_string(value);
        return std::pow(10, string_value.size() - string_value.find('.', 0ul) - 1);
    }
    void Fraction::truncate() {
        size_t gcd = std::gcd(numerator, denominator);
        if (gcd == 1) {
            return;
        }
        
        numerator   /= gcd;
        denominator /= gcd;
    }
    int Fraction::getSign(bool is_negative) {
        return (2 * !is_negative) - 1;
    }

    const char* Fraction::make_what(std::string text) {
        size_t size = text.size();

        std::unique_ptr<char[]> tmp = std::make_unique<char[]>(size + 1);
        strcpy(tmp.get(), text.c_str());
        tmp[size] = '\0';

        const char *output = tmp.get();

        return output;
    }
    //------------------- division by zero exception -------------------
    const char* Fraction::division_by_zero::what() const throw () {
        return make_what("Dividing " + numerator + " by 0 is not allowed.");
    }
    Fraction::division_by_zero::division_by_zero(size_t numerator) {
        this->numerator = std::to_string(numerator);   
    }
    //------------------- square root of negative nr -------------------
    const char* Fraction::sqrt_of_negative::what() const throw () {
        return make_what("Taking the square root of " + frac + " results in imaginary fractions.");
    }
    Fraction::sqrt_of_negative::sqrt_of_negative(const Fraction &frac) {
        this->frac = frac.toString();
    }
    //------------------- illegal truncation ---------------------------
    const char* Fraction::illegal_truncation::what() const throw () {
        return make_what("Can not truncate " + frac + " by factor " + factor + ".");
    }
    Fraction::illegal_truncation::illegal_truncation(const Fraction &frac, size_t factor) {
        this->frac = frac.toString();
        this->factor = std::to_string(factor);
    }
    //------------------------------------------------------------------

    //public
    Fraction::Fraction() {
        numerator = 1;
        denominator = 1;
    }
    Fraction::Fraction(double value) {
        if (value == 0) {
            numerator   = 0;
            denominator = 1;

            return;
        } else if (value < 0) {
            is_negative = true;
            value = -value;
        }

        size_t expanded_denom = getDenominator(value);
        size_t expanded_num = value * expanded_denom;
        size_t gcd = std::gcd(expanded_denom, expanded_num);
        if (gcd == 1) {
            return;
        }
  
        numerator   = expanded_num   / gcd;
        denominator = expanded_denom / gcd;
    }
    Fraction::Fraction(size_t numerator, size_t denominator, bool negative): is_negative(negative) {
        if (denominator == 0) {
            throw division_by_zero(numerator);
        } else if (numerator == 0) {
            this->numerator   = 0;
            this->denominator = 0;

            return;
        }

        this->numerator   = numerator;
        this->denominator = denominator;

        truncate();
    }


    Fraction::Fraction(const Fraction &other) {
        this->numerator   = other.numerator;
        this->denominator = other.denominator;
        this->is_negative = other.is_negative;
    }
    Fraction &Fraction::operator=(const Fraction &other) {
        this->numerator   = other.numerator;
        this->denominator = other.denominator;
        this->is_negative = other.is_negative;

        return *this;
    }
    Fraction &Fraction::operator=(double value) {
        if (value == 0) {
            numerator   = 0;
            denominator = 1;

            return *this;
        } else if (value < 0) {
            is_negative = true;
            value = -value;
        }

        size_t expanded_denom = getDenominator(value);
        size_t expanded_num = value * expanded_denom;
        size_t gcd = std::gcd(expanded_denom, expanded_num);
        if (gcd != 1) {
            numerator   = expanded_num   / gcd;
            denominator = expanded_denom / gcd;
        }

        return *this;
    }


    Fraction::operator double () {
        return getSign(is_negative) * static_cast<double>(numerator) / denominator;
    }
    Fraction::operator long () {
        return (numerator / denominator) * getSign(is_negative);
    }
    Fraction::operator size_t () {
        return numerator / denominator;
    }


    std::ostream &operator<<(std::ostream &stream, const Fraction &frac) {
        stream << frac.toString();

        return stream;
    }
    std::string Fraction::toString() {
        return static_cast<const Fraction &>(*this).toString();
    }
    std::string Fraction::toString() const {
        std::string output = std::to_string(numerator) + '/' + std::to_string(denominator);
        if (is_negative) {
            return '-' + output;
        } else {
            return output;
        }
    }


    size_t Fraction::getNumerator() {
        return numerator;
    }
    size_t Fraction::getNumerator() const {
        return numerator;
    }
    size_t Fraction::getDenominator() {
        return denominator;
    }
    size_t Fraction::getDenominator() const {
        return denominator;
    }


    Fraction Fraction::operator++() {
        if (is_negative) {
            if (numerator < denominator) {
                numerator = denominator - numerator;
                is_negative = false;
            } else {
                numerator -= denominator;
            }
        } else {
            numerator += denominator;
        }

        truncate();

        return *this;
    }
    Fraction Fraction::operator++(int) {
        Fraction that = *this;

        if (is_negative) {
            if (numerator < denominator) {
                numerator = denominator - numerator;
                is_negative = false;
            } else {
                numerator -= denominator;
            }
        } else {
            numerator += denominator;
        }

        truncate();

        return that;
    }

    Fraction Fraction::operator+(const Fraction &other) {
        return const_cast<Fraction &&>(static_cast<const Fraction &>(*this).operator+(other));
    }
    const Fraction Fraction::operator+(const Fraction &other) const {
        size_t common_denom = std::lcm(denominator, other.denominator);
        size_t left_num  = numerator       * common_denom / denominator,
               right_num = other.numerator * common_denom / other.denominator;

        if (is_negative == other.is_negative) {
            return Fraction(left_num + right_num, common_denom, is_negative);
        } else if (left_num < right_num) {
            return Fraction(right_num - left_num, common_denom, other.is_negative);
        } else {
            return Fraction(left_num - right_num, common_denom, is_negative);
        }
    }
    Fraction Fraction::operator+(double other) {
        return const_cast<Fraction &&>(static_cast<const Fraction &>(*this).operator+(other));
    }
    const Fraction Fraction::operator+(double other) const {
        bool other_is_negative = false;
        if (other < 0) {
            other_is_negative = true;
            other = -other;
        }

        size_t other_denom = getDenominator(other);
        size_t other_num = other * other_denom;

        size_t common_denom = std::lcm(denominator, other_denom);
        size_t left_num  = numerator * common_denom / denominator,
               right_num = other_num * common_denom / other_denom;

        if (is_negative == other_is_negative) {
            return Fraction(left_num + right_num, common_denom, is_negative);
        } else if (left_num < right_num) {
            return Fraction(right_num - left_num, common_denom, other_is_negative);
        } else {
            return Fraction(left_num - right_num, common_denom, is_negative);
        }
    }
    double operator+(double left, const Fraction &right) {
        if (right.is_negative) {
            left -= static_cast<double>(right.numerator) / right.denominator;
        } else {
            left += static_cast<double>(right.numerator) / right.denominator;
        }

        return left;
    }

    Fraction &Fraction::operator+=(const Fraction &other) {
        size_t common_denom = std::lcm(denominator, other.denominator);
        size_t left_num  = numerator       * common_denom / denominator,
               right_num = other.numerator * common_denom / other.denominator;

        denominator = common_denom;

        if (is_negative == other.is_negative) {
            numerator   = left_num + right_num;
        } else if (left_num < right_num) {
            numerator   = right_num - left_num;
            is_negative = other.is_negative;
        } else {
            numerator   = left_num - right_num;
        }

        truncate();

        return *this;
    }
    Fraction &Fraction::operator+=(double other) {
        bool other_is_negative = false;
        if (other < 0) {
            other_is_negative = true;
            other = -other;
        }

        size_t other_denom = getDenominator(other);
        size_t other_num = other * other_denom;

        size_t common_denom = std::lcm(denominator, other_denom);
        size_t left_num  = numerator * common_denom / denominator,
               right_num = other_num * common_denom / other_denom;

        denominator = common_denom;

        if (is_negative == other_is_negative) {
            numerator   = left_num + right_num;
        } else if (left_num < right_num) {
            numerator   = right_num - left_num;
            is_negative = other_is_negative;
        } else {
            numerator   = left_num - right_num;
        }

        truncate();

        return *this;
    }


    Fraction Fraction::operator--() {
        if (!is_negative) {
            if (numerator < denominator) {
                numerator = denominator - numerator;
                is_negative = true;
            } else {
                numerator -= denominator;
            }
        } else {
            numerator += denominator;
        }

        truncate();

        return *this;
    }
    Fraction Fraction::operator--(int) {
        Fraction that = *this;

        if (!is_negative) {
            if (numerator < denominator) {
                numerator = denominator - numerator;
                is_negative = true;
            } else {
                numerator -= denominator;
            }
        } else {
            numerator += denominator;
        }

        truncate();

        return that;
    }

    Fraction Fraction::operator-() {
        return const_cast<Fraction &&>(static_cast<const Fraction &>(*this).operator-());
    }
    const Fraction Fraction::operator-() const {
        Fraction output(*this);
        output.is_negative = !is_negative;

        return output;
    }
    Fraction Fraction::operator-(const Fraction &other) {
        return const_cast<Fraction &&>(static_cast<const Fraction &>(*this).operator-(other));
    }
    const Fraction Fraction::operator-(const Fraction &other) const {
        size_t common_denom = std::lcm(denominator, other.denominator);
        size_t left_num  = numerator       * common_denom / denominator,
               right_num = other.numerator * common_denom / other.denominator;

        if (is_negative != other.is_negative) {
            return Fraction(left_num - right_num, common_denom, is_negative);
        } else if (left_num < right_num) {
            return Fraction(right_num - left_num, common_denom, !is_negative);
        } else {
            return Fraction(left_num - right_num, common_denom, is_negative);
        }
    }
    Fraction Fraction::operator-(double other) {
        return const_cast<Fraction &&>(static_cast<const Fraction &>(*this).operator-(other));
    }
    const Fraction Fraction::operator-(double other) const {
        bool other_is_negative = false;
        if (other < 0) {
            other_is_negative = true;
            other = -other;
        }

        size_t other_denom = getDenominator(other);
        size_t other_num = other * other_denom;

        size_t common_denom = std::lcm(denominator, other_denom);
        size_t left_num  = numerator * common_denom / denominator,
               right_num = other_num * common_denom / other_denom;

        if (is_negative != other_is_negative) {
            return Fraction(left_num - right_num, common_denom, is_negative);
        } else if (left_num < right_num) {
            return Fraction(right_num - left_num, common_denom, !is_negative);
        } else {
            return Fraction(left_num - right_num, common_denom, is_negative);
        }
    }
    double operator-(double left, const Fraction &right) {
        if (right.is_negative) {
            left += static_cast<double>(right.numerator) / right.denominator;
        } else {
            left -= static_cast<double>(right.numerator) / right.denominator;
        }

        return left;
    }

    Fraction &Fraction::operator-=(const Fraction &other) {
        size_t common_denom = std::lcm(denominator, other.denominator);
        size_t left_num  = numerator       * common_denom / denominator,
               right_num = other.numerator * common_denom / other.denominator;

        denominator = common_denom;

        if (is_negative != other.is_negative) {
            numerator   = left_num - right_num;
        } else if (left_num < right_num) {
            numerator   = right_num - left_num;
            is_negative = !is_negative;
        } else {
            numerator   = left_num - right_num;
        }

        truncate();

        return *this;
    }
    Fraction &Fraction::operator-=(double other) {
        bool other_is_negative = false;
        if (other < 0) {
            other_is_negative = true;
            other = -other;
        }

        size_t other_denom = getDenominator(other);
        size_t other_num = other * other_denom;

        size_t common_denom = std::lcm(denominator, other_denom);
        size_t left_num  = numerator * common_denom / denominator,
               right_num = other_num * common_denom / other_denom;

        denominator = common_denom;

        if (is_negative != other_is_negative) {
            numerator   = left_num - right_num;
        } else if (left_num < right_num) {
            numerator   = right_num - left_num;
            is_negative = !is_negative;
        } else {
            numerator   = left_num - right_num;
        }

        truncate();

        return *this;
    }


    Fraction Fraction::operator*(const Fraction &other) {
        return const_cast<Fraction &&>(static_cast<const Fraction &>(*this).operator*(other));
    }
    const Fraction Fraction::operator*(const Fraction &other) const {
        return Fraction(numerator * other.numerator, denominator * other.denominator, !(is_negative == other.is_negative));
    }
    Fraction Fraction::operator*(double other) {
        return const_cast<Fraction &&>(static_cast<const Fraction &>(*this).operator*(other));
    }
    const Fraction Fraction::operator*(double other) const {
        bool other_is_negative = false;
        if (other < 0) {
            other_is_negative = true;
            other = -other;
        }

        size_t expanded_denom = getDenominator(other);
        size_t expanded_num = other * expanded_denom;
        size_t gcd = std::gcd(expanded_denom, expanded_num);
        
        return Fraction(expanded_num * numerator / gcd, expanded_denom * denominator / gcd, !(is_negative == other_is_negative));
    }
    double operator*(double left, const Fraction &right) {
        if (right.is_negative) {
            left *= -right.numerator;
        } else {
            left *= right.numerator;
        }

        left /= right.denominator;

        return left;
    }

    Fraction &Fraction::operator*=(const Fraction &other) {
        numerator   *= other.numerator;
        denominator *= other.denominator;
        is_negative  = !(is_negative == other.is_negative);

        truncate();

        return *this;
    }
    Fraction &Fraction::operator*=(double other) {
        bool other_is_negative = false;
        if (other < 0) {
            other_is_negative = true;
            other = -other;
        }

        size_t expanded_denom = getDenominator(other);
        size_t expanded_num = other * expanded_denom;
        size_t gcd = std::gcd(expanded_denom, expanded_num);
        
        numerator   *= expanded_num;
        denominator *= expanded_denom;
        is_negative  = !(is_negative == other_is_negative);

        truncate();

        return *this;
    }


    Fraction Fraction::operator/(const Fraction &other) {
        return const_cast<Fraction &&>(static_cast<const Fraction &>(*this).operator/(other));
    }
    const Fraction Fraction::operator/(const Fraction &other) const {
        return Fraction(numerator * other.denominator, denominator * other.numerator, !(is_negative == other.is_negative));
    }
    Fraction Fraction::operator/(double other) {
        return const_cast<Fraction &&>(static_cast<const Fraction &>(*this).operator/(other));
    }
    const Fraction Fraction::operator/(double other) const {
        bool other_is_negative = false;
        if (other < 0) {
            other_is_negative = true;
            other = -other;
        }

        size_t expanded_denom = getDenominator(other);
        size_t expanded_num = other * expanded_denom;
        size_t gcd = std::gcd(expanded_denom, expanded_num);
        
        return Fraction(expanded_denom * numerator / gcd, expanded_num * denominator / gcd, !(is_negative == other_is_negative));
    }
    double operator/(double left, const Fraction &right) {
        if (right.is_negative) {
            left *= -right.denominator;
        } else {
            left *= right.denominator;
        }

        left /= right.numerator;

        return left;
    }

    Fraction &Fraction::operator/=(const Fraction &other) {
        numerator   *= other.denominator;
        denominator *= other.numerator;
        is_negative  = !(is_negative == other.is_negative);

        truncate();

        return *this;
    }
    Fraction &Fraction::operator/=(double other) {
        bool other_is_negative = false;
        if (other < 0) {
            other_is_negative = true;
            other = -other;
        }

        size_t expanded_denom = getDenominator(other);
        size_t expanded_num = other * expanded_denom;
        size_t gcd = std::gcd(expanded_denom, expanded_num);
        
        numerator   *= expanded_denom;
        denominator *= expanded_num;
        is_negative  = !(is_negative == other_is_negative);

        truncate();

        return *this;
    }


    //-----------------------------------------------------------------------------------------------//
    // Note: modulo operations for floatingpoint types or fractions in general are usually obsolete. //
    //       In the number space IR there is no rest r != 0 when dividing.                           //
    //       For the sake of this implementation it is assumed that the quotient q of the division   //
    //       needs to be a whole number. This is NOT a general rule!                                 //
    //       There is no guarantee for correctness. Use under your own responsability.               //
    //                                                                                               //
    // e.g.: (9/10) % (1/5) = (1/10)                                                                 //
    //                                                                                               //
    //         a =  q *   b +   r                                                                    //
    //        .9 =  4 *  .2 +  .1                                                                    //
    //       -.9 = -4 *  .2 + -.1                                                                    //
    //        .9 = -4 * -.2 +  .1                                                                    //
    //       -.9 =  4 * -.2 + -.1                                                                    //
    //-----------------------------------------------------------------------------------------------//

    Fraction Fraction::operator%(const Fraction &other) {
        return const_cast<Fraction &&>(static_cast<const Fraction &>(*this).operator%(other));
    }
    const Fraction Fraction::operator%(const Fraction &other) const {
        size_t common_denom = std::lcm(denominator, other.denominator);
        size_t left_num  = numerator       * common_denom / denominator,
               right_num = other.numerator * common_denom / other.denominator;

        return Fraction(left_num % right_num, common_denom, is_negative);
    }
    Fraction Fraction::operator%(double other) {
        return const_cast<Fraction &&>(static_cast<const Fraction &>(*this).operator%(other));
    }
    const Fraction Fraction::operator%(double other) const {
        if (other < 0) {
            other = -other;
        }

        size_t other_denom = Fraction::getDenominator(other);
        size_t other_num = other * other_denom;
        size_t gcd = std::gcd(other_denom, other_num);

        other_num   /= gcd;
        other_denom /= gcd;

        size_t common_denom = std::lcm(denominator, other_denom);
        size_t left_num  = numerator * common_denom / denominator,
               right_num = other_num * common_denom / other_denom;

        return Fraction(left_num % right_num, common_denom, is_negative);
    }

    Fraction &Fraction::operator%=(const Fraction &other) {
        size_t common_denom = std::lcm(denominator, other.denominator);
        size_t left_num  = numerator       * common_denom / denominator,
               right_num = other.numerator * common_denom / other.denominator;

        numerator   = left_num % right_num;
        denominator = common_denom;

        return *this;
    }
    Fraction &Fraction::operator%=(double other) {
        if (other < 0) {
            other = -other;
        }

        size_t other_denom = Fraction::getDenominator(other);
        size_t other_num = other * other_denom;
        size_t gcd = std::gcd(other_denom, other_num);

        other_num   /= gcd;
        other_denom /= gcd;

        size_t common_denom = std::lcm(denominator, other_denom);
        size_t left_num  = numerator * common_denom / denominator,
               right_num = other_num * common_denom / other_denom;

        numerator   = left_num % right_num;
        denominator = common_denom;

        return *this;
    }


    bool Fraction::operator<(const Fraction &other) {
        return static_cast<const Fraction &>(*this).operator<(other);
    }
    bool Fraction::operator<(const Fraction &other) const {
        if (is_negative == other.is_negative) {
            size_t common_denom = std::lcm(denominator, other.denominator);
            size_t left_num  = numerator       * common_denom / denominator,
                right_num = other.numerator * common_denom / other.denominator;
            
            return (left_num < right_num) ^ is_negative;
        } else {
            return is_negative;
        }
    }
    bool Fraction::operator<(double other) {
        return static_cast<const Fraction &>(*this).operator<(other);
    }
    bool Fraction::operator<(double other) const {
        bool other_is_negative = false;
        if (other < 0) {
            other_is_negative = true;
            other = -other;
        }

        if (is_negative == other_is_negative) {
            size_t other_denom = Fraction::getDenominator(other);
            size_t other_num = other * other_denom;
            size_t gcd = std::gcd(other_denom, other_num);

            other_num   /= gcd;
            other_denom /= gcd;

            size_t common_denom = std::lcm(denominator, other_denom);
            size_t left_num  = numerator * common_denom / denominator,
                   right_num = other_num * common_denom / other_denom;
            
            return (left_num < right_num) ^ is_negative;
        } else {
            return is_negative;
        }
    }
    bool operator<(double left, const Fraction &right) {
        bool left_is_negative = false;
        if (left < 0) {
            left_is_negative = true;
            left = -left;
        }

        if (right.is_negative == left_is_negative) {
            size_t other_denom = Fraction::getDenominator(left);
            size_t other_num = left * other_denom;
            size_t gcd = std::gcd(other_denom, other_num);

            other_num   /= gcd;
            other_denom /= gcd;

            size_t common_denom = std::lcm(right.denominator, other_denom);
            size_t left_num  = other_num * common_denom / other_denom,
                   right_num = right.numerator * common_denom / right.denominator;
            
            return (left_num < right_num) ^ left_is_negative;
        } else {
            return left_is_negative;
        }
    }


    bool Fraction::operator<=(const Fraction &other) {
        return static_cast<const Fraction &>(*this).operator<=(other);
    }
    bool Fraction::operator<=(const Fraction &other) const {
        if (is_negative == other.is_negative) {
            size_t common_denom = std::lcm(denominator, other.denominator);
            size_t left_num  = numerator       * common_denom / denominator,
                   right_num = other.numerator * common_denom / other.denominator;
            
            return (left_num <= right_num) ^ is_negative;
        } else {
            return is_negative || (other.numerator == numerator && numerator == 0);
        }
    }
    bool Fraction::operator<=(double other) {
        return static_cast<const Fraction &>(*this).operator<=(other);
    }
    bool Fraction::operator<=(double other) const {
        bool other_is_negative = false;
        if (other < 0) {
            other_is_negative = true;
            other = -other;
        }

        if (is_negative == other_is_negative) {
            size_t other_denom = Fraction::getDenominator(other);
            size_t other_num = other * other_denom;
            size_t gcd = std::gcd(other_denom, other_num);

            other_num   /= gcd;
            other_denom /= gcd;

            size_t common_denom = std::lcm(denominator, other_denom);
            size_t left_num  = numerator * common_denom / denominator,
                   right_num = other_num * common_denom / other_denom;
            
            return (left_num <= right_num) ^ is_negative;
        } else {
            return is_negative || (other == numerator && numerator == 0);
        }
    }
    bool operator<=(double left, const Fraction &right) {
        bool left_is_negative = false;
        if (left < 0) {
            left_is_negative = true;
            left = -left;
        }

        if (right.is_negative == left_is_negative) {
            size_t other_denom = Fraction::getDenominator(left);
            size_t other_num = left * other_denom;
            size_t gcd = std::gcd(other_denom, other_num);

            other_num   /= gcd;
            other_denom /= gcd;

            size_t common_denom = std::lcm(right.denominator, other_denom);
            size_t left_num  = other_num * common_denom / other_denom,
                   right_num = right.numerator * common_denom / right.denominator;
            
            return (left_num <= right_num) ^ left_is_negative;
        } else {
            return left_is_negative || (left == right.numerator && right.numerator == 0);
        }
    }


    bool Fraction::operator>(const Fraction &other) {
        return static_cast<const Fraction &>(*this).operator>(other);
    }
    bool Fraction::operator>(const Fraction &other) const {
        if (is_negative == other.is_negative) {
            size_t common_denom = std::lcm(denominator, other.denominator);
            size_t left_num  = numerator       * common_denom / denominator,
                right_num = other.numerator * common_denom / other.denominator;
            
            return (left_num > right_num) ^ is_negative;
        } else {
            return !is_negative;
        }
    }
    bool Fraction::operator>(double other) {
        return static_cast<const Fraction &>(*this).operator>(other);
    }
    bool Fraction::operator>(double other) const {
        bool other_is_negative = false;
        if (other < 0) {
            other_is_negative = true;
            other = -other;
        }

        if (is_negative == other_is_negative) {
            size_t other_denom = Fraction::getDenominator(other);
            size_t other_num = other * other_denom;
            size_t gcd = std::gcd(other_denom, other_num);

            other_num   /= gcd;
            other_denom /= gcd;

            size_t common_denom = std::lcm(denominator, other_denom);
            size_t left_num  = numerator * common_denom / denominator,
                   right_num = other_num * common_denom / other_denom;
            
            return (left_num > right_num) ^ is_negative;
        } else {
            return !is_negative;
        }
    }
    bool operator>(double left, const Fraction &right) {
        bool left_is_negative = false;
        if (left < 0) {
            left_is_negative = true;
            left = -left;
        }

        if (right.is_negative == left_is_negative) {
            size_t other_denom = Fraction::getDenominator(left);
            size_t other_num = left * other_denom;
            size_t gcd = std::gcd(other_denom, other_num);

            other_num   /= gcd;
            other_denom /= gcd;

            size_t common_denom = std::lcm(right.denominator, other_denom);
            size_t left_num  = other_num * common_denom / other_denom,
                   right_num = right.numerator * common_denom / right.denominator;
            
            return (left_num > right_num) ^ left_is_negative;
        } else {
            return !left_is_negative;
        }
    }


    bool Fraction::operator>=(const Fraction &other) {
        return static_cast<const Fraction &>(*this).operator>=(other);
    }
    bool Fraction::operator>=(const Fraction &other) const {
        if (is_negative == other.is_negative) {
            size_t common_denom = std::lcm(denominator, other.denominator);
            size_t left_num  = numerator       * common_denom / denominator,
                right_num = other.numerator * common_denom / other.denominator;
            
            return (left_num >= right_num) ^ is_negative;
        } else {
            return !is_negative || (other.numerator == numerator && numerator == 0);
        }
    }
    bool Fraction::operator>=(double other) {
        return static_cast<const Fraction &>(*this).operator>=(other);
    }
    bool Fraction::operator>=(double other) const {
        bool other_is_negative = false;
        if (other < 0) {
            other_is_negative = true;
            other = -other;
        }

        if (is_negative == other_is_negative) {
            size_t other_denom = Fraction::getDenominator(other);
            size_t other_num = other * other_denom;
            size_t gcd = std::gcd(other_denom, other_num);

            other_num   /= gcd;
            other_denom /= gcd;

            size_t common_denom = std::lcm(denominator, other_denom);
            size_t left_num  = numerator * common_denom / denominator,
                   right_num = other_num * common_denom / other_denom;
            
            return (left_num >= right_num) ^ is_negative;
        } else {
            return !is_negative || (other == numerator && numerator == 0);
        }
    }
    bool operator>=(double left, const Fraction &right) {
        bool left_is_negative = false;
        if (left < 0) {
            left_is_negative = true;
            left = -left;
        }

        if (right.is_negative == left_is_negative) {
            size_t other_denom = Fraction::getDenominator(left);
            size_t other_num = left * other_denom;
            size_t gcd = std::gcd(other_denom, other_num);

            other_num   /= gcd;
            other_denom /= gcd;

            size_t common_denom = std::lcm(right.denominator, other_denom);
            size_t left_num  = other_num * common_denom / other_denom,
                   right_num = right.numerator * common_denom / right.denominator;
            
            return (left_num >= right_num) ^ left_is_negative;
        } else {
            return !left_is_negative || (left == right.numerator && right.numerator == 0);
        }
    }


    bool Fraction::operator==(const Fraction &other) {
        return static_cast<const Fraction &>(*this).operator==(other);
    }
    bool Fraction::operator==(const Fraction &other) const {
        if (is_negative == other.is_negative) {
            size_t common_denom = std::lcm(denominator, other.denominator);
            size_t left_num  = numerator       * common_denom / denominator,
                   right_num = other.numerator * common_denom / other.denominator;
            
            return left_num == right_num;
        } else {
            return false;
        }
    }
    bool Fraction::operator==(double other) {
        return static_cast<const Fraction &>(*this).operator==(other);
    }
    bool Fraction::operator==(double other) const {
        bool other_is_negative = false;
        if (other < 0) {
            other_is_negative = true;
            other = -other;
        }

        if (is_negative == other_is_negative) {
            size_t other_denom = Fraction::getDenominator(other);
            size_t other_num = other * other_denom;
            size_t gcd = std::gcd(other_denom, other_num);

            other_num   /= gcd;
            other_denom /= gcd;

            size_t common_denom = std::lcm(denominator, other_denom);
            size_t left_num  = numerator * common_denom / denominator,
                   right_num = other_num * common_denom / other_denom;
            
            return left_num == right_num;
        } else {
            return false;
        }
    }
    bool operator==(double left, const Fraction &right) {
        bool left_is_negative = false;
        if (left < 0) {
            left_is_negative = true;
            left = -left;
        }

        if (right.is_negative == left_is_negative) {
            size_t other_denom = Fraction::getDenominator(left);
            size_t other_num = left * other_denom;
            size_t gcd = std::gcd(other_denom, other_num);

            other_num   /= gcd;
            other_denom /= gcd;

            size_t common_denom = std::lcm(right.denominator, other_denom);
            size_t left_num  = other_num * common_denom / other_denom,
                   right_num = right.numerator * common_denom / right.denominator;
            
            return left_num == right_num;
        } else {
            return false;
        }
    }


    bool Fraction::operator!=(const Fraction &other) {
        return static_cast<const Fraction &>(*this).operator!=(other);
    }
    bool Fraction::operator!=(const Fraction &other) const {
        if (is_negative == other.is_negative) {
            size_t common_denom = std::lcm(denominator, other.denominator);
            size_t left_num  = numerator       * common_denom / denominator,
                   right_num = other.numerator * common_denom / other.denominator;
            
            return left_num != right_num;
        } else {
            return true;
        }
    }
    bool Fraction::operator!=(double other) {
        return static_cast<const Fraction &>(*this).operator!=(other);
    }
    bool Fraction::operator!=(double other) const {
        bool other_is_negative = false;
        if (other < 0) {
            other_is_negative = true;
            other = -other;
        }

        if (is_negative == other_is_negative) {
            size_t other_denom = Fraction::getDenominator(other);
            size_t other_num = other * other_denom;
            size_t gcd = std::gcd(other_denom, other_num);

            other_num   /= gcd;
            other_denom /= gcd;

            size_t common_denom = std::lcm(denominator, other_denom);
            size_t left_num  = numerator * common_denom / denominator,
                   right_num = other_num * common_denom / other_denom;
            
            return left_num != right_num;
        } else {
            return true;
        }
    }
    bool operator!=(double left, const Fraction &right) {
        bool left_is_negative = false;
        if (left < 0) {
            left_is_negative = true;
            left = -left;
        }

        if (right.is_negative == left_is_negative) {
            size_t other_denom = Fraction::getDenominator(left);
            size_t other_num = left * other_denom;
            size_t gcd = std::gcd(other_denom, other_num);

            other_num   /= gcd;
            other_denom /= gcd;

            size_t common_denom = std::lcm(right.denominator, other_denom);
            size_t left_num  = other_num * common_denom / other_denom,
                   right_num = right.numerator * common_denom / right.denominator;
            
            return left_num != right_num;
        } else {
            return true;
        }
    }


    Fraction &Fraction::pow(double power) { //TODO: make real implementation
        double num   = std::pow(numerator, power),
               denom = std::pow(denominator, power);
        
        size_t factor = getDenominator(num) * getDenominator(denom);
        numerator   = num   * factor;
        denominator = denom * factor;

        truncate();

        bool numerator_neg   = numerator < 0,
             denominator_neg = denominator < 0;
        is_negative = (numerator_neg && !denominator_neg) || (!numerator_neg && denominator_neg);

        return *this;
    }
    Fraction pow(const Fraction &frac, double power) { //TODO: make real implementation
        return Fraction(std::pow(frac.numerator, power) / std::pow(frac.denominator, power));
    }
    Fraction &Fraction::sqrt() { //TODO: make real implementation
        if (is_negative) {
            throw sqrt_of_negative(*this);
        } else if (numerator == 0) {
            return *this;
        }

        /*
        Fraction high = *this,
                 low(0, 1, false),
                 guess = *this / 2.0;

        while (frac::abs(guess * guess - *this) / guess > SQRT_TOLERANCE) {
            if (guess * guess > *this) {
                high = guess;
            } else {
                low  = guess;
            }

            guess = (high + low) / 2.0;
        }

        numerator   = guess.numerator;
        denominator = guess.denominator;
        is_negative = guess.is_negative;
        */

        double num   = std::sqrt(numerator),
               denom = std::sqrt(denominator);
        
        size_t factor = getDenominator(num) * getDenominator(denom);
        numerator   = num   * factor;
        denominator = denom * factor;

        is_negative = false;

        truncate();

        return *this;
    }
    Fraction sqrt(const Fraction &frac) { //TODO: make real implementation
        if (frac.is_negative) {
            throw Fraction::sqrt_of_negative(frac);
        } else if (frac.numerator == 0) {
            return frac;
        }

        /*
        Fraction high = frac,
                 low(0, 1, false),
                 guess = frac / 2.0;

        while (frac::abs(guess * guess - frac) / guess > SQRT_TOLERANCE) {
            if (guess * guess > frac) {
                high = guess;
            } else {
                low  = guess;
            }

            guess = (high + low) / 2.0;
        }

        return guess;
        */
       
        return Fraction(std::sqrt(frac.numerator), std::sqrt(frac.denominator));
    }
    Fraction &Fraction::exp() { //TODO: make real implementation
        /*
        size_t i = 1;
        double denom = 1;
        Fraction result(1, 1, false),
                 x(1, 1, false),
                 previous;

        do {
            previous = result;

            x *= *this;
            denom *= i;

            result += x / denom;

            i += 1;
        } while (result - previous < EXP_TOLERANCE);

        numerator   = result.numerator;
        denominator = result.denominator;
        is_negative = result.is_negative;
        */
        
        double num   = std::exp(numerator),
               denom = std::exp(denominator);
        
        size_t factor = getDenominator(num) * getDenominator(denom);
        numerator   = num   * factor;
        denominator = denom * factor;

        is_negative = false;

        truncate();

        return *this;
    }
    Fraction exp(const Fraction &frac) { //TODO: make real implementation
        /*
        size_t i = 1;
        double denom = 1;
        Fraction result(1, 1, false),
                 x(1, 1, false),
                 previous;

        do {
            previous = result;

            x *= frac;
            denom *= i;

            result += x / denom;

            i += 1;
        } while (result - previous < EXP_TOLERANCE);
        */
        
        return Fraction(std::exp(static_cast<double>(frac.numerator) / frac.denominator));
    }
    Fraction &Fraction::exp2() { //TODO: make real implementation
        double num   = std::exp2(numerator),
               denom = std::exp2(denominator);
        
        size_t factor = getDenominator(num) * getDenominator(denom);
        numerator   = num   * factor;
        denominator = denom * factor;

        is_negative = false;

        truncate();

        return *this;
    }
    Fraction exp2(const Fraction &frac) { //TODO: make real implementation
        return Fraction(std::exp2(frac.numerator / frac.denominator));
    }
    Fraction &Fraction::log() { //TODO: make real implementation
        double num   = std::log(numerator),
               denom = std::log(denominator);
        
        size_t factor = getDenominator(num) * getDenominator(denom);
        numerator   = num   * factor;
        denominator = denom * factor;

        truncate();

        bool numerator_neg   = numerator < 0,
             denominator_neg = denominator < 0;
        is_negative = (numerator_neg && !denominator_neg) || (!numerator_neg && denominator_neg);

        return *this;
    }
    Fraction log(const Fraction &frac) { //TODO: make real implementation
        return Fraction(std::log(frac.numerator) - std::log(frac.denominator)); //log(a/b) = log(a) - log(b)
    }
    Fraction &Fraction::log10() { //TODO: make real implementation
        double num   = std::log10(numerator),
               denom = std::log10(denominator);
        
        size_t factor = getDenominator(num) * getDenominator(denom);
        numerator   = num   * factor;
        denominator = denom * factor;

        truncate();

        bool numerator_neg   = numerator < 0,
             denominator_neg = denominator < 0;
        is_negative = (numerator_neg && !denominator_neg) || (!numerator_neg && denominator_neg);

        return *this;
    }
    Fraction log10(const Fraction &frac) { //TODO: make real implementation
        return Fraction(std::log(frac.numerator) - std::log(frac.denominator));
    }
    Fraction &Fraction::log2() { //TODO: make real implementation
        double num   = std::log2(numerator),
               denom = std::log2(denominator);
        
        size_t factor = getDenominator(num) * getDenominator(denom);
        numerator   = num   * factor;
        denominator = denom * factor;

        truncate();

        bool numerator_neg   = numerator < 0,
             denominator_neg = denominator < 0;
        is_negative = (numerator_neg && !denominator_neg) || (!numerator_neg && denominator_neg);

        return *this;
    }
    Fraction log2(const Fraction &frac) { //TODO: make real implementation
        return Fraction(std::log2(frac.numerator) - std::log2(frac.denominator));
    }
    Fraction &Fraction::abs() {
        is_negative = false;

        return *this;
    }
    Fraction abs(const Fraction &frac) {
        return Fraction(frac.numerator, frac.denominator, false);
    }
    Fraction &Fraction::ceil() {
        numerator   = numerator / denominator + (numerator % denominator != 0);
        denominator = 1;

        return *this;
    }
    Fraction ceil(const Fraction &frac) {
        return (frac.numerator / frac.denominator + (frac.numerator % frac.denominator != 0), 1, frac.is_negative);
    }
    Fraction &Fraction::floor() {
        numerator   = numerator / denominator;
        denominator = 1;

        return *this;
    }
    Fraction floor(const Fraction &frac) {
        return Fraction(frac.numerator / frac.denominator, 1, frac.is_negative);
    }
    Fraction &Fraction::round() {
        size_t residue = numerator % denominator;
        numerator = numerator / denominator + (denominator - residue <= residue);
        denominator = 1;

        return *this;
    }
    Fraction round(const Fraction &frac) {
        size_t residue = frac.numerator % frac.denominator;
        
        return Fraction(frac.numerator / frac.denominator + (frac.denominator - residue <= residue), 1, frac.is_negative);
    }


    Fraction &Fraction::invert() {
        std::swap(numerator, denominator);

        return *this;
    }
    Fraction invert(const Fraction &frac) {
        return Fraction(frac.denominator, frac.numerator, frac.is_negative);
    }
    Fraction &Fraction::expand(size_t factor) {
        if (factor == 0) {
            throw division_by_zero(numerator);
        }

        numerator   *= factor;
        denominator *= factor;

        return *this;
    }
    Fraction expand(const Fraction &frac, size_t factor) {
        if (factor == 0) {
            throw Fraction::division_by_zero(frac.numerator);
        }

        return Fraction(frac.numerator * factor, frac.denominator * factor, frac.is_negative, '\0');
    }
    Fraction &Fraction::truncate(size_t factor) {
        if (factor == 0) {
            throw division_by_zero(numerator);
        } else if (numerator % factor != 0 || denominator % factor != 0) {
            throw illegal_truncation(*this, factor);
        }

        numerator   /= factor;
        denominator /= factor;

        return *this;
    }
    Fraction truncate(const Fraction &frac, size_t factor) {
        if (factor == 0) {
            throw Fraction::division_by_zero(frac.numerator);
        } else if (frac.numerator % factor != 0 || frac.denominator % factor != 0) {
            throw Fraction::illegal_truncation(frac, factor);
        }

        return Fraction(frac.numerator / factor, frac.denominator / factor, frac.is_negative, '\0');
    }
} // namespace frac