#pragma once

#include "exception.hpp"
#include <vector>
#include <cstdint>
#include <utility>
//#include <algorithm>
#include <string>

struct Term
{
    double coefficient;
    int_fast16_t degree;


    inline void operator*=(const double scalar) { coefficient *= scalar; }

    inline void operator/=(const double scalar);
};

/**
 * @brief Represents a single-variable polynomial with an inclusive degree range.
 *
 * The polynomial tracks a lower and upper degree bound and stores coefficients
 * for every integer exponent in that closed interval.
 */
class Polynomial
{
public:
    Polynomial();
    Polynomial(const Polynomial &n) = default;
    Polynomial(int_fast16_t smallest_deg, int_fast16_t biggest_deg);
    Polynomial(std::vector<Term> coefficient, int_fast16_t smallest_deg, int_fast16_t biggest_deg);

    // Polynomial operations
    bool operator==(const Polynomial &n) const;
    bool operator!=(const Polynomial &n) const;

    Polynomial operator+(const Polynomial &n) const;
    Polynomial operator-(const Polynomial &n) const;
    Polynomial operator*(const Polynomial &n) const;
    Polynomial operator/(const Polynomial &n) const;

    void operator+=(const Polynomial &n);
    void operator-=(const Polynomial &n);
    void operator*=(const Polynomial &n);
    void operator/=(const Polynomial &n);

    // scalar operations
    bool operator==(const double scalar) const;
    bool operator!=(const double scalar) const;

    Polynomial operator+(const double scalar) const;
    Polynomial operator-(const double scalar) const;
    Polynomial operator*(const double scalar) const;
    Polynomial operator/(const double scalar) const;

    void operator+=(const double scalar);
    void operator-=(const double scalar);
    void operator*=(const double scalar);
    void operator/=(const double scalar);

    // read only
    Term getTerm(size_t i) const;
    int_fast16_t getDegree() const;
    std::string toString() const;
    bool isMonomial() const;
    bool isZero() const;

    size_t findExponent(int_fast16_t exponent) const;

private:
    std::vector<Term> _Terms;
    int_fast16_t _trailingTermDegree, _leadingTermDegree;

    static size_t calcVectorSize(int_fast16_t smallest_deg, int_fast16_t biggest_deg);
    static size_t binarySearch(const std::vector<Term> &lst, size_t low, size_t hight, const int_fast16_t value);
};
