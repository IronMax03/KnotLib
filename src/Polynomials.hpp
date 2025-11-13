#pragma once

#include "exception.hpp"
#include <iostream>
#include <vector>
#include <cstdint>
#include <utility>
#include <string>

struct Term
{
    double coefficient;
    int_fast16_t degree;

    inline void copy(const Term &n)
    {
      coefficient = n.coefficient;
      degree = n.degree;
    }

    inline void operator*=(const double scalar) { coefficient *= scalar; }

    inline void operator/=(const double scalar) 
    {
        if(scalar == 0)
            throw PolynomialArithmeticException("/", "zero division exception.");
        coefficient /= scalar;
    }


    inline void operator+=(const Term &n)
    {
      if(degree == n.degree)
        coefficient += n.coefficient;
      else
        throw PolynomialArithmeticException("+=", "2 terms of different degree cant be added.");

    }


    inline void operator-=(const Term &n)
    {
      if(degree == n.degree)
        coefficient -= n.coefficient;
      else
        throw PolynomialArithmeticException("-", "2 terms of different degree cant be added.");
    }

  
    inline bool operator==(const Term &n) const { return coefficient == n.coefficient && degree == n.degree; }

    inline Term operator+(const Term &n) const
    {
      Term t(*this);
      t += n;
      return t;
    }

    inline Term operator-(const Term &n) const
    {
      Term t(*this);
      t -= n;
      return t;
    }
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
    // atribute 
    std::vector<Term> Terms;

    // constructor
    Polynomial();
    Polynomial(const Polynomial &n) = default;
    Polynomial(int_fast16_t smallest_deg, int_fast16_t biggest_deg);
    Polynomial(std::vector<Term> coefficient, int_fast16_t smallest_deg, int_fast16_t biggest_deg);

    // Polynomial operators
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

    // scalar operators
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

    // other polynomial operation
    void simplify();
    void densify();
    void densify(const int_fast16_t startDegree, const int_fast16_t endDegree);

    // read only
    Term getTerm(size_t i) const;
    int_fast16_t getLeadingDegree() const;
    int_fast16_t getTrailingDegree() const;
    std::string toString() const;
    bool isMonomial() const;
    bool isZero() const;

    size_t findExponent(int_fast16_t exponent) const;

private:
    int_fast16_t _trailingTermDegree, _leadingTermDegree;

    void isInOrder(size_t i) const;

    static size_t calcVectorSize(int_fast16_t smallest_deg, int_fast16_t biggest_deg);
    static size_t binarySearch(const std::vector<Term> &lst, size_t low, size_t hight, const int_fast16_t value);
};
