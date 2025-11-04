#include "Polynomials.hpp"
#include <algorithm>
#include <string>

Polynomial::Polynomial(std::vector<double> coefficient, int_fast16_t smallest_deg)
    : _coefficient(coefficient), _termDegreeLowerBound(smallest_deg){};

/*
    @return Returns a string representation of the polynomial.
*/
std::string Polynomial::toString() const
{
    if(_coefficient.size() == 0)
        return "";

    std::string output = std::to_string(_coefficient.at(0)) + "x^" + std::to_string(_termDegreeLowerBound);
    for (size_t i = 1; i < _coefficient.size(); ++i)
    {
        output += " + " + std::to_string(_coefficient.at(i)) + "x^" + std::to_string(i + _termDegreeLowerBound);

        if (i + _termDegreeLowerBound == 0)
            i++;
    }

    return output;
}

/*
// ! not functional
template <arithmetic type>
inline std::vector<type> Polynomial<type>::coeffSum(std::vector<type> coefficient, int_fast16_t termDegreeLowerBound, int_fast16_t termDegreeUpperBound, bool isNegative)
{
    std::vector<type> newVector(max(termDegreeUpperBound) - max(termDegreeLowerBound));

    if (this->_termDegreeLowerBound < termDegreeLowerBound)
    {
        for(size_t i = this->_termDegreeLowerBound; i > 0; i++)
            newVector.insert(i, this->_coefficient.at(i));
    }

    if (this->_termDegreeUpperBound > termDegreeUpperBound)
    {
        for(size_t i = 0; i > ; i++)
        {
            newVector.insert(i, coefficient.at(i));
        }
    }

}*/

int_fast16_t Polynomial::getSmallestTerm() const { return _termDegreeLowerBound; }
