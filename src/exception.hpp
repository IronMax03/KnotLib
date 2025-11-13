#pragma once

#include <exception>
#include <string>

/*
** Base class for all Knotlib Exceptions
 */
class KnotlibExceptions : public std::exception
{
public:
    explicit KnotlibExceptions(const std::string& msg) :  _message(msg) {}
    explicit KnotlibExceptions(const char* msg) :  _message(msg) {}
    ~KnotlibExceptions() override = default;

    const char *what() const noexcept override{ return _message.c_str(); }

private:
        std::string _message;
};

/*
** thrown when the Planar Diagram of a knot is not properly formated or consistent.
 */
class InconsistentPlanarDiagram : public KnotlibExceptions // NOTE: not finished
{
public:
    InconsistentPlanarDiagram(const std::string& msg) : KnotlibExceptions(msg)  {};
};

/*
**
 */
class PolynomialBoundException : public KnotlibExceptions
{
public:
    PolynomialBoundException(const std::string& msg) : KnotlibExceptions(msg) {}
};

/*
** Thrown when a Polynomial arithmetic operation failed.
 */
class PolynomialArithmeticException : public KnotlibExceptions
{
private:
    std::string _operationType; // +, -, *, ==, +=, etc.

public:
    PolynomialArithmeticException(const std::string& opType, const std::string& msg) :  KnotlibExceptions(opType + ": " + msg), _operationType(opType) {}
};

/*
** Thrown when failed searching for a term with a specific exponent.
 */
class ExponentNotFound : public KnotlibExceptions
{
private:
    int_fast16_t _exp;

public:
    ExponentNotFound(const int_fast16_t& exponent) : _exp(exponent), KnotlibExceptions(std::to_string(exponent) + " was not found in the polynomial.") {}

};

/**
 * Thrown when the formating of a Polynomial object is incorect.
 * */
class PolynomialRepresentationException : public KnotlibExceptions
{
public:
    PolynomialRepresentationException(const std::string& msg) : KnotlibExceptions(msg) {}
};
