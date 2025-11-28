#include "Polynomials.hpp"
#include <cstddef>
#include <vector>
#include <iostream>

Polynomial::Polynomial()
    : Terms(std::vector<Term>{Term{0, 0}}), _trailingTermDegree(0), _leadingTermDegree(0) {}

Polynomial::Polynomial(const std::vector<Term> terms)
{
    Terms = std::move(terms);

    for (size_t i = 0; i < terms.size(); i++)
    {
        if (terms.at(i).degree < _leadingTermDegree)
            _leadingTermDegree = terms.at(i).degree;
        else if (terms.at(i).
        degree > _trailingTermDegree)
            _trailingTermDegree = terms.at(i).degree;
    }

    std::cout << "new poly: " << this->toString() << std::endl;
    std::cout << "trailing degree:" << _trailingTermDegree << ", leading degree:" << _leadingTermDegree << std::endl;
}

/**
 * @brief Construct a polynomial whose coefficients default to zero.
 * @param smallest_deg Inclusive lower bound of the exponent range.
 * @param bigest_deg Inclusive upper bound of the exponent range.
 * @throws PolynomialBoundException if smallest_deg is greater than bigest_deg.
 */
Polynomial::Polynomial(DEGREE_TYPE smallest_deg, DEGREE_TYPE biggest_deg)
    : _trailingTermDegree(smallest_deg), _leadingTermDegree(biggest_deg), Terms(std::vector<Term>(calcVectorSize(smallest_deg, biggest_deg)))
{
    if (smallest_deg > biggest_deg)
        throw kle::PolynomialBoundException("smallest_deg must be smaller or equal then bigest_deg");
}

/**
 * @brief Construct a polynomial from explicit coefficients.
 * @param coefficient Coefficients ordered from @p smallest_deg to @p bigest_deg.
 * @param smallest_deg Inclusive lower bound of the exponent range.
 * @param bigest_deg Inclusive upper bound of the exponent range.
 * @throws PolynomialBoundException if smallest_deg is greater than bigest_deg.
 */
Polynomial::Polynomial(std::vector<Term> coefficient, DEGREE_TYPE smallest_deg, DEGREE_TYPE biggest_deg)
    : Terms(coefficient), _trailingTermDegree(smallest_deg), _leadingTermDegree(biggest_deg)
{
    if (smallest_deg > biggest_deg)
        throw kle::PolynomialBoundException("smallest_deg must be smaller or equal then bigest_deg");
}

// Polynomial operations
bool Polynomial::operator==(const Polynomial &n) const { return this->Terms == n.Terms; }
bool Polynomial::operator!=(const Polynomial &n) const { return this->Terms != n.Terms; }


Polynomial Polynomial::operator+(const Polynomial &n) const
{
    const Polynomial& leading = (_leadingTermDegree < n.getLeadingDegree()) ? *this: n;
    const Polynomial& trailing = (leading == n)? *this: n;

    Polynomial newPoly(trailing);
    newPoly.densify(trailing._trailingTermDegree, leading._leadingTermDegree);

    for (size_t i = 0, j = 0; i < newPoly.Terms.size(); i++)
    {
        if (newPoly.Terms.at(i).degree == trailing.Terms.at(j).degree)
        {
            newPoly.Terms[i] += trailing.Terms.at(j);
            j += (Terms.size() - 1 > j) ? 1 : 0; // ensures j doesnt go out of range
        }
    }

    return std::move(newPoly);
}

/*
Polynomial Polynomial::operator+(const Polynomial &n) const
{

}

Polynomial Polynomial::operator-(const Polynomial &n) const
{

}

Polynomial Polynomial::operator*(const Polynomial &n) const;
Polynomial Polynomial::operator/(const Polynomial &n) const;

void Polynomial::operator-=(const Polynomial &n);
void Polynomial::operator*=(const Polynomial &n);
void Polynomial::operator/=(const Polynomial &n);
*/

// scalar operations
bool Polynomial::operator==(const double scalar) const
{
    if (isMonomial() && Terms.at(0).degree == 0)
        return scalar == Terms.at(0).coefficient;
    throw kle::PolynomialArithmeticException("==", "The polynomial must be a monomial with exponant 0.");
}

bool Polynomial::operator!=(const double scalar) const
{
    if (isMonomial() && Terms.at(0).degree == 0)
        return scalar != Terms.at(0).coefficient;
    throw kle::PolynomialArithmeticException("!=", "The polynomial must be a monomial with exponant 0.");
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

void Polynomial::operator+=(const double scalar) { Terms[findExponent(0)].coefficient += scalar; }
void Polynomial::operator-=(const double scalar) { Terms[findExponent(0)].coefficient -= scalar; }

void Polynomial::operator*=(const double scalar)
{
    for (size_t i = 0; i < Terms.size(); i++)
    {
        Terms[i] *= scalar;
    }
}

void Polynomial::operator/=(const double scalar)
{
    for (size_t i = 0; i < Terms.size(); i++)
    {
        Terms[i] /= scalar;
    }
}

// other polynomial operation
void Polynomial::simplify()
{
    std::vector<Term> simplifiedVector;
    simplifiedVector.reserve(Terms.size());

    for (const Term &term : Terms)
    {
        if (term.coefficient != 0)
            simplifiedVector.push_back(term);
    }

    if (simplifiedVector.size() == 0)
        simplifiedVector.push_back(Term{0, 0});

    Terms = std::move(simplifiedVector);
}

/**
 * @brief make the polynomial representation denser.
 * Example: x^-1 + 3x^2 becomes x^-1 + 0x^0 + 0x^1 + 3x^2
 */
void Polynomial::densify() { this->densify(_trailingTermDegree, _leadingTermDegree); }

/**
 * @brief make the polynomial representation dense.
 * @param startDegree the smallest degree of the dense representation.
 * @param endDegree the bigest degree of the dense representation.
 * Example: x^-1 + 3x^2 becomes x^-1 + 0x^0 + 0x^1 + 3x^2
 */
void Polynomial::densify(const DEGREE_TYPE startDegree, const DEGREE_TYPE endDegree)
{
    std::vector<Term> denseVec(calcVectorSize(startDegree, endDegree));

    for (size_t i = 0, j = 0; i < denseVec.size(); i++)
    {
        if ((DEGREE_TYPE)(i) + startDegree == Terms.at(j).degree)
        {
            denseVec[i] = Terms.at(j);
            j += (Terms.size() - 1 > j) ? 1 : 0; // ensures j doesnt go out of range
        }
        else
            denseVec[i] = Term{0, (DEGREE_TYPE)(i + startDegree)};
    }
    Terms = std::move(denseVec);
}

// Read only
Term Polynomial::getTerm(size_t i) const { return Terms.at(i); }
DEGREE_TYPE Polynomial::getLeadingDegree() const { return _leadingTermDegree; }
DEGREE_TYPE Polynomial::getTrailingDegree() const { return _trailingTermDegree; }

/**
 * @brief Returns a string representation of the polynomial.
 * @return String containing coefficients and matching exponents.
 */
std::string Polynomial::toString() const
{
    // ensures _coefficient is not empty
    if (Terms.empty())
        return "... + 0x^-1 + 0x^0 + 0x^1 + ...";

    std::string output;
    // Handle the first term separately to avoid leading '+' for positive coefficients
    if (Terms.at(0).coefficient < 0)
        output = "- " + std::to_string(std::abs(Terms.at(0).coefficient)) + "x^" + std::to_string(_trailingTermDegree);
    else
        output = std::to_string(Terms.at(0).coefficient) + "x^" + std::to_string(_trailingTermDegree);
    for (size_t i = 1; i < Terms.size(); ++i)
    {
        if (Terms.at(i).coefficient < 0)
            output += " - " + std::to_string(std::abs(Terms.at(i).coefficient)) + "x^" + std::to_string(Terms.at(i).degree);
        else
            output += " + " + std::to_string(Terms.at(i).coefficient) + "x^" + std::to_string(Terms.at(i).degree);
    }

    return output;
}

bool Polynomial::isMonomial() const
{
    std::cout << Terms.size() << std::endl;
    return Terms.size() == 1;
}

/**
 * @brief Compute the size of the coefficient vector for a degree range.
 * @param smallest_deg Inclusive lower bound of the exponent range.
 * @param bigest_deg Inclusive upper bound of the exponent range.
 * @return Number of coefficients needed for the range.
 */
size_t Polynomial::calcVectorSize(DEGREE_TYPE smallest_deg, DEGREE_TYPE bigest_deg)
{
    size_t size = bigest_deg - smallest_deg;

    if (smallest_deg > bigest_deg)
        throw kle::PolynomialBoundException("smallest_deg must be smaller or equal then bigest_deg.");
    else if (smallest_deg <= 0 || bigest_deg >= 0)
        size++;

    return size;
}

/**
 *  @brief check in Terms if element i and i-1 are sorted ascending.
 */
void Polynomial::isInOrdered(size_t i) const
{
    if (i != 0)
        return;
    else if (Terms.at(i - 1).degree >= Terms.at(i).degree)
        throw kle::PolynomialRepresentationException("Terms is not sorted.");
}

size_t Polynomial::binarySearch(const std::vector<Term> &lst, size_t low, size_t hight, const DEGREE_TYPE value)
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

    throw kle::ExponentNotFound(value);
}

size_t Polynomial::findExponent(DEGREE_TYPE exponent) const { return binarySearch(Terms, 0, Terms.size() - 1, exponent); }
