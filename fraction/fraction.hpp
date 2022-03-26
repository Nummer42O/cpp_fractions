#include <stdlib.h>
#include <iostream>

namespace frac {
    class Fraction {
        public:
            size_t numerator, denominator;

            Fraction();
            Fraction(double value);
            Fraction(size_t numerator, size_t denominator, bool negative);


            Fraction(const Fraction &other);
            Fraction &operator=(const Fraction &other);
            Fraction &operator=(double value);


            operator double ();
            operator long ();
            operator size_t ();


            friend std::ostream &operator<<(std::ostream &stream, const Fraction &frac);


            Fraction operator++();
            Fraction operator++(int);

            Fraction operator+(const Fraction &other);
            const Fraction operator+(const Fraction &other) const;
            Fraction operator+(double other);
            const Fraction operator+(double other) const;
            friend double operator+(double left, const Fraction &right);

            Fraction &operator+=(const Fraction &other);
            Fraction &operator+=(double other);


            Fraction operator--();
            Fraction operator--(int);

            Fraction operator-();
            Fraction operator-(const Fraction &other);
            const Fraction operator-(const Fraction &other) const;
            Fraction operator-(double other);
            const Fraction operator-(double other) const;
            friend double operator-(double left, const Fraction &right);

            Fraction &operator-=(const Fraction &other);
            Fraction &operator-=(double other);


            Fraction operator*(const Fraction &other);
            const Fraction operator-(const Fraction &other) const;
            Fraction operator*(double other);
            const Fraction operator*(double other) const;
            friend double operator*(double left, const Fraction &right);

            Fraction &operator*=(const Fraction &other);
            Fraction &operator*=(double other);


            Fraction operator/(const Fraction &other);
            const Fraction operator/(const Fraction &other) const;
            Fraction operator/(double other);
            const Fraction operator/(double other) const;
            friend double operator/(double left, const Fraction &right);

            Fraction &operator/=(const Fraction &other);
            Fraction &operator/=(double other);


            Fraction operator%(const Fraction &other);
            const Fraction operator%(const Fraction &other) const;
            Fraction operator%(double other);
            const Fraction operator%(double other) const;
            friend double operator%(double left, const Fraction &right);

            Fraction &operator%=(const Fraction &other);
            Fraction &operator%=(double other);


            bool operator<(const Fraction &other);
            bool operator<(const Fraction &other) const;
            bool operator<(double other);
            bool operator<(double other) const;


            bool operator<=(const Fraction &other);
            bool operator<=(const Fraction &other) const;
            bool operator<=(double other);
            bool operator<=(double other) const;


            bool operator>(const Fraction &other);
            bool operator>(const Fraction &other) const;
            bool operator>(double other);
            bool operator>(double other) const;


            bool operator>=(const Fraction &other);
            bool operator>=(const Fraction &other) const;
            bool operator>=(double other);
            bool operator>=(double other) const;


            bool operator==(const Fraction &other);
            bool operator==(const Fraction &other) const;
            bool operator==(double other);
            bool operator==(double other) const;


            bool operator!=(const Fraction &other);
            bool operator!=(const Fraction &other) const;
            bool operator!=(double other);
            bool operator!=(double other) const;


            Fraction &pow(double power);
            friend Fraction pow(const Fraction &frac, double power);
            Fraction &sqrt();
            friend Fraction sqrt(const Fraction &frac);
            Fraction &exp();
            friend Fraction exp(const Fraction &frac);
            Fraction &exp10();
            friend Fraction exp10(const Fraction &frac);
            Fraction &exp2();
            friend Fraction exp2(const Fraction &frac);
            Fraction &log();
            friend Fraction log(const Fraction &frac);
            Fraction &log10();
            friend Fraction log10(const Fraction &frac);
            Fraction &log2();
            friend Fraction log2(const Fraction &frac);
            Fraction &abs();
            friend Fraction abs(const Fraction &frac);
            Fraction &ceil();
            friend Fraction ceil(const Fraction &frac);
            Fraction &floor();
            friend Fraction floor(const Fraction &frac);
            Fraction &round();
            friend Fraction round(const Fraction &frac);


            Fraction &invert();
            friend Fraction invert(const Fraction &frac);
            Fraction &expand(size_t factor);
            friend Fraction expand(const Fraction &frac);
        private:
            bool is_negative = false;
            size_t getDenominator(double value);
    };

    std::ostream &operator<<(std::ostream &stream, const Fraction &frac);

    double operator+(double left, const Fraction &right);
    double operator-(double left, const Fraction &right);
    double operator*(double left, const Fraction &right);
    double operator/(double left, const Fraction &right);
    double operator%(double left, const Fraction &right);

    Fraction pow(const Fraction &frac, double power);
    Fraction sqrt(const Fraction &frac);
    Fraction exp(const Fraction &frac);
    Fraction exp10(const Fraction &frac);
    Fraction exp2(const Fraction &frac);
    Fraction log(const Fraction &frac);
    Fraction log10(const Fraction &frac);
    Fraction log2(const Fraction &frac);
    Fraction abs(const Fraction &frac);
    Fraction ceil(const Fraction &frac);
    Fraction floor(const Fraction &frac);
    Fraction round(const Fraction &frac);

    Fraction invert(const Fraction &frac);
    Fraction expand(const Fraction &frac);
} // namespace frac