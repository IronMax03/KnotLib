#pragma once
#include <vector>
#include <concepts>
#include <cstdint>
#include <utility>

/*
template <typename T>
concept arithmetic = std::integral<T> || std::floating_point<T>;
*/

// ! make template
class Polynomial
{
public:
    Polynomial() = default;
    Polynomial(const Polynomial &n) = default;
    Polynomial(std::vector<double> coefficient, int_fast16_t smallest_deg);

    Polynomial operator+(const Polynomial &n);
    Polynomial operator-(const Polynomial &n);
    Polynomial operator*(const Polynomial &n);

    void addTerm(int_fast16_t degree);

    // read only
    int_fast16_t getSmallestTerm() const;
    std::string toString() const;

private:
    std::vector<double> _coefficient;
    int_fast16_t _termDegreeLowerBound, _termDegreeUpperBound;

    inline std::vector<double> coeffSum(std::vector<double> coefficient, int_fast16_t termDegreeLowerBound, int_fast16_t termDegreeUpperBound, bool isNegative);
};