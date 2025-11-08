#include <iostream>
#include <cassert>
#include "knot.hpp"
#include "Polynomials.hpp"

using namespace std;
using namespace arma;

// clang++ -std=c++14 src/tests.cpp -o main -I/opt/homebrew/include -L/opt/homebrew/lib -larmadillo
// clang++ -std=c++20 src/tests.cpp src/Polynomials.cpp -I/opt/homebrew/include -L/opt/homebrew/lib -larmadillo -Wall

int main()
{
    mat A = randu<mat>(2,2);
    cout << A(1, 1) << endl;
    A(1, 1) = -1;
    cout << A(1, 1) << endl;
    std::cout << "Hello, Armadillo!\n";
    cout << sizeof(int_fast16_t) << endl;
    A.print("Random matrix A:");

    cout << "______________________________" << endl;

    Polynomial poly;
    cout << poly.toString() << endl;
    
    cout << Polynomial(vector<double>{1,2,3}, -1, 1).toString() << endl;
    assert(Polynomial(vector<double>{1,2,3}, 0, 2).toString() == "1.000000x^0 + 2.000000x^1 + 3.000000x^2");
    assert(Polynomial(vector<double>{1,2,3}, -1, 1).toString() == "1.000000x^-1 + 2.000000x^0 + 3.000000x^1");
    assert(Polynomial(vector<double>{}, 0, 0).toString() ==  "... + 0x^-1 + 0x^0 + 0x^1 + ...");

    poly.setFromStr("3x^0 + 1x^1 + 0x^2 + 9x^3");

    cout << poly.toString() << endl;
    assert(poly.toString() == "3x^0 + 1x^1 + 0x^2 + 9x^3");
    return 0;
}