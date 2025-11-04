#include <iostream>
#include <cassert>
#include "knot.hpp"
#include "Polynomials.hpp"

using namespace std;
using namespace arma;

// clang++ -std=c++14 src/tests.cpp -o main -I/opt/homebrew/include -L/opt/homebrew/lib -larmadillo

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

    Polynomial poly(std::vector<double>{3,2,0,5,}, -1);
    cout << poly.toString() << endl;

    return 0;
}