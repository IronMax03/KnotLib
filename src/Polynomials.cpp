#include "Polynomials.hpp"
#include "exception.hpp"
#include <algorithm>
#include <string>

 Polynomial::Polynomial() 
 :_coefficients(std::vector<double>{0}), _termDegreeLowerBound(0), _termDegreeUpperBound(0){}

/**
 * @brief Construct a polynomial whose coefficients default to zero.
 * @param smallest_deg Inclusive lower bound of the exponent range.
 * @param bigest_deg Inclusive upper bound of the exponent range.
 * @throws PolynomBoundException if smallest_deg is greater than bigest_deg.
 */
Polynomial::Polynomial(int_fast16_t smallest_deg, int_fast16_t bigest_deg)
    : _termDegreeLowerBound(smallest_deg), _termDegreeUpperBound(bigest_deg), _coefficients(std::vector<double>(calcCoeffSize(smallest_deg, bigest_deg))) {}

/**
 * @brief Construct a polynomial from explicit coefficients.
 * @param coefficient Coefficients ordered from @p smallest_deg to @p bigest_deg.
 * @param smallest_deg Inclusive lower bound of the exponent range.
 * @param bigest_deg Inclusive upper bound of the exponent range.
 * @throws PolynomBoundException if smallest_deg is greater than bigest_deg.
 */
Polynomial::Polynomial(std::vector<double> coefficient, int_fast16_t smallest_deg, int_fast16_t bigest_deg)
    : _coefficients(coefficient), _termDegreeLowerBound(smallest_deg), _termDegreeUpperBound(bigest_deg)
{
    if (smallest_deg > bigest_deg)
        throw PolynomBoundException("smallest_deg must be smaller or equal then bigest_deg");
}

bool Polynomial::operator==(const Polynomial &n)
{
    return this->_coefficients == n._coefficients;
}

// ! not tested
Polynomial Polynomial::operator+(const Polynomial &n)
{
    const Polynomial &lowerPoly = (this->_termDegreeLowerBound < n._termDegreeLowerBound) ? *this : n;
    const Polynomial &upperPoly = (this->_termDegreeLowerBound < n._termDegreeLowerBound) ? n : *this;

    int_fast16_t smallest_deg = std::min(this->_termDegreeLowerBound, n._termDegreeLowerBound);
    int_fast16_t bigest_deg = std::max(this->_termDegreeUpperBound, n._termDegreeUpperBound);

    std::vector<double> newVector(calcCoeffSize(smallest_deg, bigest_deg));

    double var1, var2;

    for (size_t i = 0; i < newVector.size(); i++)
    {
        var1 = 0;
        var2 = 0;

        if (i <= lowerPoly._termDegreeUpperBound)
            var1 = lowerPoly.getTerm(i);
        else if (i >= upperPoly._termDegreeLowerBound)
            var2 = upperPoly.getTerm(i);

        newVector[i] = var1 + var2;
    }

    return Polynomial(std::move(newVector), std::move(smallest_deg), std::move(bigest_deg));
}

/**
 * @brief Returns a string representation of the polynomial.
 * @return String containing coefficients and matching exponents.
 */
std::string Polynomial::toString() const
{
    // ensures _coefficient is not empty
    if (_coefficients.empty())
        return "... + 0x^-1 + 0x^0 + 0x^1 + ...";

    std::string output = std::to_string(_coefficients.at(0)) + "x^" + std::to_string(_termDegreeLowerBound);
    for (size_t i = 1; i < _coefficients.size(); ++i)
    {
        output += " + " + std::to_string(_coefficients.at(i)) + "x^" + std::to_string(i + _termDegreeLowerBound);

        if (i + _termDegreeLowerBound == 0)
            i++;
    }

    return output;
}

/**
 * @brief Redefine the actual polynomial from a string representation.
 * @param polynomStr String to parse into coefficients.
 * @return Copy of the polynomial after redefinition.
 */
void Polynomial::setFromStr(std::string polynomStr) // ! Only works with integer coefficients.
{
    bool isSmallCoeffDef = false;
    _coefficients.clear();

    for (size_t i = 0; i < polynomStr.length(); i++)
    {
        if (polynomStr[i] == ' ' || polynomStr[i] == '+')
            continue;
        else if (polynomStr[i] == 'x')
            _coefficients.push_back(std::stod(std::to_string(polynomStr[i - 1])));
        else if(polynomStr[i] ==  '^' && !isSmallCoeffDef)
        {
            isSmallCoeffDef = true;
            _termDegreeLowerBound = std::stod(std::to_string(polynomStr[i + 1]));
        }
    }

    _termDegreeUpperBound = _termDegreeLowerBound < 0 ? (_coefficients.size() + 1 - _termDegreeLowerBound) : (_coefficients.size() - _termDegreeLowerBound) ;
}

/**
 * @brief Compute the size of the coefficient vector for a degree range.
 * @param smallest_deg Inclusive lower bound of the exponent range.
 * @param bigest_deg Inclusive upper bound of the exponent range.
 * @return Number of coefficients needed for the range.
 */
inline constexpr size_t Polynomial::calcCoeffSize(int_fast16_t smallest_deg, int_fast16_t bigest_deg)
{
    size_t size = bigest_deg - smallest_deg;

    if (smallest_deg > bigest_deg)
        throw PolynomBoundException("smallest_deg must be smaller or equal then bigest_deg.");
    else if (smallest_deg <= 0 || bigest_deg <= 0)
        size++;

    return size;
}

inline int_fast16_t Polynomial::getTerm(size_t i) const { return _coefficients.at(i); }

int_fast16_t Polynomial::getSmallestTerm() const { return _termDegreeLowerBound; }
