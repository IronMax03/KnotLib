#pragma once

#include "exception.hpp"
#include <vector>
#include <cstdint>
#include <utility>
#include <string>

#ifndef EGREE_TYPE // DEGREE_TYPE must be a fixed sized integer.
  #define DEGREE_TYPE int_fast16_t
#else
  #define DEGREE_TYPE EGREE_TYPE

  static_assert(
    std::disjunction_v<
        std::is_same<DEGREE_TYPE, std::int8_t>,  std::is_same<DEGREE_TYPE, std::int16_t>,
        std::is_same<DEGREE_TYPE, std::int32_t>, std::is_same<DEGREE_TYPE, std::int64_t>,
        std::is_same<DEGREE_TYPE, std::int_fast8_t>,  std::is_same<DEGREE_TYPE, std::int_fast16_t>,
        std::is_same<DEGREE_TYPE, std::int_fast32_t>, std::is_same<DEGREE_TYPE, std::int_fast64_t>,
        std::is_same<DEGREE_TYPE, std::int_least8_t>, std::is_same<DEGREE_TYPE, std::int_least16_t>,
        std::is_same<DEGREE_TYPE, std::int_least32_t>, std::is_same<DEGREE_TYPE, std::int_least64_t>>,
    "DEGREE_TYPE must be an 8/16/32/64-bit fixed-width, least, or fast signed integer type");
#endif

struct Term
{
    double coefficient;
    DEGREE_TYPE degree;

    inline void operator*=(const double scalar) { coefficient *= scalar; }

    inline void operator/=(const double scalar) 
    {
        if(scalar == 0)
            throw kle::PolynomialArithmeticException("/", "zero division exception.");
        coefficient /= scalar;
    }


    inline void operator+=(const Term &n)
    {
      if(degree == n.degree)
        coefficient += n.coefficient;
      else
        throw kle::PolynomialArithmeticException("+=", "2 terms of different degree cant be added.");
    }


    inline void operator-=(const Term &n)
    {
      if(degree == n.degree)
        coefficient -= n.coefficient;
      else
        throw kle::PolynomialArithmeticException("-", "2 terms of different degree cant be added.");
    }

  
    inline bool operator==(const Term &n) const { return coefficient == n.coefficient && degree == n.degree; }

    inline Term operator+(const Term &n) const
    {
      Term t(*this);
      t += n;
      return std::move(t);
    }

    inline Term operator-(const Term &n) const
    {
      Term t(*this);
      t -= n;
      return std::move(t);
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
    Polynomial(std::vector<Term> coefficient);
    Polynomial(const Polynomial &n) = default;
    Polynomial(DEGREE_TYPE smallest_deg, DEGREE_TYPE biggest_deg);
    Polynomial(std::vector<Term> coefficient, DEGREE_TYPE smallest_deg, DEGREE_TYPE biggest_deg);

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
    void densify(const DEGREE_TYPE startDegree, const DEGREE_TYPE endDegree);

    // read only
    Term getTerm(size_t i) const;
    DEGREE_TYPE getLeadingDegree() const;
    DEGREE_TYPE getTrailingDegree() const;
    std::string toString() const;
    bool isMonomial() const;

    size_t findExponent(DEGREE_TYPE exponent) const;

private:
    DEGREE_TYPE _trailingTermDegree, _leadingTermDegree;

    void isInOrdered(size_t i) const;

    static size_t calcVectorSize(DEGREE_TYPE smallest_deg, DEGREE_TYPE biggest_deg);
    static size_t binarySearch(const std::vector<Term> &lst, size_t low, size_t hight, const DEGREE_TYPE value);
};
