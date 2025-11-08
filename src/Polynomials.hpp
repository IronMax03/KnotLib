#pragma once
#include <vector>
#include <concepts>
#include <cstdint>
#include <utility>
#include <armadillo>

struct term
{
    double coefficient;
    int_fast16_t degree;
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
    Polynomial(int_fast16_t smallest_deg, int_fast16_t bigest_deg);
    Polynomial(std::vector<double> coefficient, int_fast16_t smallest_deg, int_fast16_t bigest_deg);

    inline bool operator==(const Polynomial &n);
    Polynomial operator+(const Polynomial &n);
    Polynomial operator-(const Polynomial &n);
    Polynomial operator*(const Polynomial &n);

    void setFromStr(std::string polynom);

    inline int_fast16_t getTerm(size_t i) const;
    int_fast16_t getSmallestTerm() const;
    std::string toString() const;

private:
    std::vector<double> _coefficients;
    int_fast16_t _termDegreeLowerBound, _termDegreeUpperBound;

    inline constexpr static size_t calcCoeffSize(int_fast16_t smallest_deg, int_fast16_t bigest_deg);
};
