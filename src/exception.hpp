#pragma once

#include <exception>
#include <iostream>
#include <string>

class InconsistenPlanarDiagram : public std::exception // NOTE: not finished
{
public:
    InconsistenPlanarDiagram() {};

    const char *what() const noexcept
    {
        return "";
    }
};

class PolynomialBoundException : public std::exception
{
private:
    std::string _message;

public:
    PolynomialBoundException(const std::string msg) : _message(msg) {}

    const char *what() const noexcept
    {
        return _message.c_str();
    }
};


class PolynomialArithmeticException : public std::exception
{
private:
    std::string _operationType; // +, -, *, ==, +=, etc
    std::string _message;

public:
    PolynomialArithmeticException(const std::string opType, const std::string msg) : _operationType(opType), _message(msg) {}

    const char *what() const noexcept
    {
        return std::move((_operationType + ": " + _message).c_str());
    }
};


class ExponentNotFound : public std::exception
{
private:
    int_fast16_t _exp;

public:
    ExponentNotFound(const int_fast16_t exponent) : _exp(exponent) {}

    const char *what() const noexcept
    {
        return std::move((std::to_string(_exp) + " was not fund in the polynom.").c_str());
    }
};
