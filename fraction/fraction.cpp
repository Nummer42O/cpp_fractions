#include "fraction.hpp"

#include <numeric> //lcm, gcd
#include <cmath>

namespace frac {
    size_t Fraction::getDenominator(double value) {
        return std::floor(std::log10(value)) + 1;
    }

    Fraction::Fraction() {
        numerator = 1;
        denominator = 1;
    }
    Fraction::Fraction(double value) {
        if (value < 0) {
            is_negative = true;
            value = -value;
        }

        size_t expanded_denominator = getDenominator(value);
        size_t expanded_numerator = value * expanded_denominator;
        size_t gcd = std::gcd(expanded_denominator, expanded_numerator);
  
        numerator   = expanded_numerator   / gcd;
        denominator = expanded_denominator / gcd;
    }
    Fraction::Fraction(size_t numerator, size_t denominator, bool negative): is_negative(negative) {
        size_t gcd = std::gcd(denominator, numerator);
        
        this->numerator   = numerator   / gcd;
        this->denominator = denominator / gcd;
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
    }
    Fraction &Fraction::operator=(double value) {
        if (value < 0) {
            is_negative = true;
            value = -value;
        }

        size_t expanded_denominator = getDenominator(value);
        size_t expanded_numerator = value * expanded_denominator;
        size_t gcd = std::gcd(expanded_denominator, expanded_numerator);
  
        numerator   = expanded_numerator   / gcd;
        denominator = expanded_denominator / gcd;
    }


    Fraction::operator double () {
        return (2 * static_cast<int>(!is_negative) - 1) * static_cast<double>(numerator) / denominator;
    }
    Fraction::operator long () {
        return (2 * static_cast<int>(!is_negative) - 1) * numerator / denominator;
    }
    Fraction::operator size_t () {
        return numerator / denominator;
    }


    std::ostream &operator<<(std::ostream &stream, const Fraction &frac) {
        if (frac.is_negative) {
            stream << '-';
        }

        stream << frac.numerator << '/' << frac.denominator;

        return stream;
    }


    Fraction Fraction::operator++() {
        
    }
    Fraction Fraction::operator++(int) {
        
    }

    Fraction Fraction::operator+(const Fraction &other) {
        
    }
    const Fraction Fraction::operator+(const Fraction &other) const {
        
    }
    Fraction Fraction::operator+(double other) {
        
    }
    const Fraction Fraction::operator+(double other) const {
        
    }
    double operator+(double left, const Fraction &right) {
        
    }

    Fraction &Fraction::operator+=(const Fraction &other) {
        
    }
    Fraction &Fraction::operator+=(double other) {
        
    }


    Fraction Fraction::operator--() {
        
    }
    Fraction Fraction::operator--(int) {
        
    }

    Fraction Fraction::operator-() {
        
    }
    Fraction Fraction::operator-(const Fraction &other) {
        
    }
    const Fraction Fraction::operator-(const Fraction &other) const {
        
    }
    Fraction Fraction::operator-(double other) {
        
    }
    const Fraction Fraction::operator-(double other) const {
        
    }
    double operator-(double left, const Fraction &right) {
        
    }

    Fraction &Fraction::operator-=(const Fraction &other) {
        
    }
    Fraction &Fraction::operator-=(double other) {
        
    }


    Fraction Fraction::operator*(const Fraction &other) {
        
    }
    const Fraction Fraction::operator-(const Fraction &other) const {
        
    }
    Fraction Fraction::operator*(double other) {
        
    }
    const Fraction Fraction::operator*(double other) const {
        
    }
    double operator*(double left, const Fraction &right) {
        
    }

    Fraction &Fraction::operator*=(const Fraction &other) {
        
    }
    Fraction &Fraction::operator*=(double other) {
        
    }


    Fraction Fraction::operator/(const Fraction &other) {
        
    }
    const Fraction Fraction::operator/(const Fraction &other) const {
        
    }
    Fraction Fraction::operator/(double other) {
        
    }
    const Fraction Fraction::operator/(double other) const {
        
    }
    double operator/(double left, const Fraction &right) {
        
    }

    Fraction &Fraction::operator/=(const Fraction &other) {
        
    }
    Fraction &Fraction::operator/=(double other) {
        
    }


    Fraction Fraction::operator%(const Fraction &other) {
        
    }
    const Fraction Fraction::operator%(const Fraction &other) const {
        
    }
    Fraction Fraction::operator%(double other) {
        
    }
    const Fraction Fraction::operator%(double other) const {
        
    }
    double operator%(double left, const Fraction &right) {
        
    }

    Fraction &Fraction::operator%=(const Fraction &other) {
        
    }
    Fraction &Fraction::operator%=(double other) {
        
    }


    bool Fraction::operator<(const Fraction &other) {
        
    }
    bool Fraction::operator<(const Fraction &other) const {
        
    }
    bool Fraction::operator<(double other) {
        
    }
    bool Fraction::operator<(double other) const {
        
    }


    bool Fraction::operator<=(const Fraction &other) {
        
    }
    bool Fraction::operator<=(const Fraction &other) const {
        
    }
    bool Fraction::operator<=(double other) {
        
    }
    bool Fraction::operator<=(double other) const {
        
    }


    bool Fraction::operator>(const Fraction &other) {
        
    }
    bool Fraction::operator>(const Fraction &other) const {
        
    }
    bool Fraction::operator>(double other) {
        
    }
    bool Fraction::operator>(double other) const {
        
    }


    bool Fraction::operator>=(const Fraction &other) {
        
    }
    bool Fraction::operator>=(const Fraction &other) const {
        
    }
    bool Fraction::operator>=(double other) {
        
    }
    bool Fraction::operator>=(double other) const {
        
    }


    bool Fraction::operator==(const Fraction &other) {
        
    }
    bool Fraction::operator==(const Fraction &other) const {
        
    }
    bool Fraction::operator==(double other) {
        
    }
    bool Fraction::operator==(double other) const {
        
    }


    bool Fraction::operator!=(const Fraction &other) {
        
    }
    bool Fraction::operator!=(const Fraction &other) const {
        
    }
    bool Fraction::operator!=(double other) {
        
    }
    bool Fraction::operator!=(double other) const {
        
    }


    Fraction &Fraction::pow(double power) {
        
    }
    Fraction pow(const Fraction &frac, double power) {
        
    }
    Fraction &Fraction::sqrt() {
        
    }
    Fraction sqrt(const Fraction &frac) {
        
    }
    Fraction &Fraction::exp() {
        
    }
    Fraction exp(const Fraction &frac) {
        
    }
    Fraction &Fraction::exp10() {
        
    }
    Fraction exp10(const Fraction &frac) {
        
    }
    Fraction &Fraction::exp2() {
        
    }
    Fraction exp2(const Fraction &frac) {
        
    }
    Fraction &Fraction::log() {
        
    }
    Fraction log(const Fraction &frac) {
        
    }
    Fraction &Fraction::log10() {
        
    }
    Fraction log10(const Fraction &frac) {
        
    }
    Fraction &Fraction::log2() {
        
    }
    Fraction log2(const Fraction &frac) {
        
    }
    Fraction &Fraction::abs() {
        
    }
    Fraction abs(const Fraction &frac) {
        
    }
    Fraction &Fraction::ceil() {
        
    }
    Fraction ceil(const Fraction &frac) {
        
    }
    Fraction &Fraction::floor() {
        
    }
    Fraction floor(const Fraction &frac) {
        
    }
    Fraction &Fraction::round() {
        
    }
    Fraction round(const Fraction &frac) {
        
    }


    Fraction &Fraction::invert() {
        
    }
    Fraction invert(const Fraction &frac) {
        
    }
    Fraction &Fraction::expand(size_t factor) {
        
    }
    Fraction expand(const Fraction &frac) {
        
    }
} // namespace frac