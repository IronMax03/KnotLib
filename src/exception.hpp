#pragma once
#include <exception>
#include <iostream>

class InconsistenPlanarDiagram : public std::exception
{
public:
    InconsistenPlanarDiagram() {};

    const char *what() const noexcept
    {
        return "";
    }
};

class PolynomBoundException : public std::exception
{
private:
    std::string message;

public:
    PolynomBoundException(const std::string msg) : message(msg) {}

    const char *what() const noexcept
    {
        return message.c_str();
    }
};

/* 
! to be finished
class PolynomDegreeOverflow : public std::exception
{
private:
    size_t _polynomSize;
    intmax_t _index;

public:
    PolynomOverflow(const size_t polySize, const uint16_t smallestDegree, const uint16_t biggestDegree, const intmax_t i) 
    : _polynomSize(polySize), _index(i){}

    const char *what() const noexcept
    {
        std::string str = "The vector  ";
        return ;
    }
};*/