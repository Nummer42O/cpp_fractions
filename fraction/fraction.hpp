#include <stdlib.h>
#include <iostream>
#include <string>

namespace frac {
    class Fraction {
        public:
            Fraction();
            Fraction(double value);
            Fraction(size_t numerator, size_t denominator, bool negative);


            Fraction(const Fraction &other);
            Fraction &operator=(const Fraction &other);
            Fraction &operator=(double value);


            explicit operator double ();
            explicit operator long ();
            explicit operator size_t ();


            friend std::ostream &operator<<(std::ostream &stream, const Fraction &frac);
            std::string toString();
            std::string toString() const;


            size_t getNumerator();
            size_t getNumerator() const;
            size_t getDenominator();
            size_t getDenominator() const;


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
            const Fraction operator-() const;
            Fraction operator-(const Fraction &other);
            const Fraction operator-(const Fraction &other) const;
            Fraction operator-(double other);
            const Fraction operator-(double other) const;
            friend double operator-(double left, const Fraction &right);

            Fraction &operator-=(const Fraction &other);
            Fraction &operator-=(double other);


            Fraction operator*(const Fraction &other);
            const Fraction operator*(const Fraction &other) const;
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

            Fraction &operator%=(const Fraction &other);
            Fraction &operator%=(double other);


            bool operator<(const Fraction &other);
            bool operator<(const Fraction &other) const;
            bool operator<(double other);
            bool operator<(double other) const;
            friend bool operator<(double left, const Fraction &right);


            bool operator<=(const Fraction &other);
            bool operator<=(const Fraction &other) const;
            bool operator<=(double other);
            bool operator<=(double other) const;
            friend bool operator<=(double left, const Fraction &right);


            bool operator>(const Fraction &other);
            bool operator>(const Fraction &other) const;
            bool operator>(double other);
            bool operator>(double other) const;
            friend bool operator>(double left, const Fraction &right);


            bool operator>=(const Fraction &other);
            bool operator>=(const Fraction &other) const;
            bool operator>=(double other);
            bool operator>=(double other) const;
            friend bool operator>=(double left, const Fraction &right);


            bool operator==(const Fraction &other);
            bool operator==(const Fraction &other) const;
            bool operator==(double other);
            bool operator==(double other) const;
            friend bool operator==(double left, const Fraction &right);


            bool operator!=(const Fraction &other);
            bool operator!=(const Fraction &other) const;
            bool operator!=(double other);
            bool operator!=(double other) const;
            friend bool operator!=(double left, const Fraction &right);


            Fraction &pow(double power);
            friend Fraction pow(const Fraction &frac, double power);
            Fraction &sqrt();
            friend Fraction sqrt(const Fraction &frac);
            Fraction &exp();
            friend Fraction exp(const Fraction &frac);
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
            friend Fraction expand(const Fraction &frac, size_t factor);
            Fraction &truncate(size_t factor);
            friend Fraction truncate(const Fraction &frac, size_t factor);
        private:
            size_t numerator, denominator;
            bool is_negative = false;

            Fraction(double numerator, double denominator); //expecteds fraction to always be positive
            Fraction(size_t numerator, size_t denominator, bool is_negative, char); //like default constructor but doesn't truncate - char for differenciation

            static size_t getDenominator(double value);
            void truncate();
            static int getSign(bool is_negative);


            static const char* make_what(std::string text);
            struct division_by_zero: public std::exception {
                const char* what() const throw ();

                division_by_zero(size_t numerator);

                std::string numerator;
            };
            struct sqrt_of_negative: public std::exception {
                const char* what() const throw ();

                sqrt_of_negative(const Fraction &frac);

                std::string frac;
            };
            struct log_of_negative: public std::exception {
                const char* what() const throw ();

                log_of_negative(const Fraction &frac);

                std::string frac;
            };
            struct illegal_truncation: public std::exception {
                const char* what() const throw ();

                illegal_truncation(const Fraction &frac, size_t factor);

                std::string frac, factor;
            };
    };

    std::ostream &operator<<(std::ostream &stream, const Fraction &frac);

    double operator+(double left, const Fraction &right);
    double operator-(double left, const Fraction &right);
    double operator*(double left, const Fraction &right);
    double operator/(double left, const Fraction &right);

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
    Fraction expand(const Fraction &frac, size_t factor);
    Fraction truncate(const Fraction &frac, size_t factor);
} // namespace frac