#include "Polynomials.hpp"

Polynomial::Polynomial()
    : _Terms(std::vector<Term>{Term{0,0}}), _trailingTermDegree(0), _leadingTermDegree(0) {}

/**
 * @brief Construct a polynomial whose coefficients default to zero.
 * @param smallest_deg Inclusive lower bound of the exponent range.
 * @param bigest_deg Inclusive upper bound of the exponent range.
 * @throws PolynomialBoundException if smallest_deg is greater than bigest_deg.
 */
Polynomial::Polynomial(int_fast16_t smallest_deg, int_fast16_t biggest_deg)
    : _trailingTermDegree(smallest_deg), _leadingTermDegree(biggest_deg), _Terms(std::vector<Term>(calcVectorSize(smallest_deg, biggest_deg))) {}

/**
 * @brief Construct a polynomial from explicit coefficients.
 * @param coefficient Coefficients ordered from @p smallest_deg to @p bigest_deg.
 * @param smallest_deg Inclusive lower bound of the exponent range.
 * @param bigest_deg Inclusive upper bound of the exponent range.
 * @throws PolynomialBoundException if smallest_deg is greater than bigest_deg.
 */
Polynomial::Polynomial(std::vector<Term> coefficient, int_fast16_t smallest_deg, int_fast16_t bigest_deg)
    : _Terms(coefficient), _trailingTermDegree(smallest_deg), _leadingTermDegree(bigest_deg)
{
    if (smallest_deg > bigest_deg)
        throw PolynomialBoundException("smallest_deg must be smaller or equal then bigest_deg");
}

// Polynomial operations
bool Polynomial::operator==(const Polynomial &n) const { return this->_Terms == n._Terms; } 
bool Polynomial::operator!=(const Polynomial &n) const { return this->_Terms != n._Terms; }

/*
! todo
Polynomial Polynomial::operator+(const Polynomial &n) const
{

}

Polynomial Polynomial::operator-(const Polynomial &n) const
{

}

Polynomial Polynomial::operator*(const Polynomial &n) const;
Polynomial Polynomial::operator/(const Polynomial &n) const;

void Polynomial::operator+=(const Polynomial &n);
void Polynomial::operator-=(const Polynomial &n);
void Polynomial::operator*=(const Polynomial &n);
void Polynomial::operator/=(const Polynomial &n);
*/

// scalar operations
bool Polynomial::operator==(const double scalar) const
{
    if (isMonomial() && _Terms.at(0).degree == 0)
        return scalar == _Terms.at(0).coefficient;
    throw PolynomialArithmeticException("==", "The polynomial must be a monomial with exponant 0.");
}

bool Polynomial::operator!=(const double scalar) const 
{
    if (isMonomial() && _Terms.at(0).degree == 0)
        return scalar != _Terms.at(0).coefficient;
    throw PolynomialArithmeticException("!=", "The polynomial must be a monomial with exponant 0.");
}

Polynomial Polynomial::operator+(const double scalar) const 
{ 
    Polynomial temp(*this);
    temp += scalar;
    return std::move(temp);
}
 
Polynomial Polynomial::operator-(const double scalar) const 
{ 
    Polynomial temp(*this);
    temp -= scalar;
    return std::move(temp);
}

Polynomial Polynomial::operator*(const double scalar) const 
{ 
    Polynomial temp(*this);
    temp *= scalar;
    return std::move(temp);
}

Polynomial Polynomial::operator/(const double scalar) const 
{ 
    Polynomial temp(*this);
    temp /= scalar;
    return std::move(temp);
}

void Polynomial::operator+=(const double scalar) { _Terms[findExponent(0)].coefficient += scalar; }
void Polynomial::operator-=(const double scalar) { _Terms[findExponent(0)].coefficient -= scalar; }

void Polynomial::operator*=(const double scalar)
{
    for (size_t i = 0; i < _Terms.size(); i++)
    {
        _Terms[i] *= scalar;
    }
}

void Polynomial::operator/=(const double scalar)
{
    for (size_t i = 0; i < _Terms.size(); i++)
    {
        _Terms[i] /= scalar;
    }
}

Term Polynomial::getTerm(size_t i) const { return _Terms.at(i); }

int_fast16_t Polynomial::getDegree() const { return _leadingTermDegree; }

/**
 * @brief Returns a string representation of the polynomial.
 * @return String containing coefficients and matching exponents.
 */
std::string Polynomial::toString() const
{
    // ensures _coefficient is not empty
    if (_Terms.empty())
        return "... + 0x^-1 + 0x^0 + 0x^1 + ...";

    std::string output = std::to_string(_Terms.at(0).coefficient) + "x^" + std::to_string(_trailingTermDegree);
    for (size_t i = 1; i < _Terms.size(); ++i)
    {
        output += " + " + std::to_string(_Terms.at(i).coefficient) + "x^" + std::to_string(_Terms.at(i).degree);

        if (i + _trailingTermDegree == 0)
            i++;
    }

    return output;
}

bool Polynomial::isMonomial() const
{
  std::cout << _Terms.size() << std::endl;
  return _Terms.size() == 1;
}


/**
 * @brief Compute the size of the coefficient vector for a degree range.
 * @param smallest_deg Inclusive lower bound of the exponent range.
 * @param bigest_deg Inclusive upper bound of the exponent range.
 * @return Number of coefficients needed for the range.
 */
size_t Polynomial::calcVectorSize(int_fast16_t smallest_deg, int_fast16_t bigest_deg)
{
    size_t size = bigest_deg - smallest_deg;

    if (smallest_deg > bigest_deg)
        throw PolynomialBoundException("smallest_deg must be smaller or equal then bigest_deg.");
    else if (smallest_deg <= 0 || bigest_deg <= 0)
        size++;

    return size;
}

size_t Polynomial::binarySearch(const std::vector<Term> &lst, size_t low, size_t hight, const int_fast16_t value)
{
    if (lst.at(low).degree == value)
        return low;
    else if (lst.at(hight).degree == value)
        return hight;
    else if (lst.at((hight + low) / 2).degree == value)
        return (hight + low) / 2;
    else if (lst.at((hight + low) / 2).degree > value)
        return binarySearch(lst, low, (hight + low) / 2, value);
    else if (lst.at((hight + low) / 2).degree < value)
        return binarySearch(lst, (hight + low) / 2, hight, value);

    throw ExponentNotFound(value);
    return -1;
}

size_t Polynomial::findExponent(int_fast16_t exponent) const { return binarySearch(_Terms, 0, _Terms.size(), exponent); }
