#include <iostream>
#include <cassert>
#include "knot.hpp"
#include "Polynomials.hpp"

using namespace std;
using namespace arma;

// clang++ -std=c++14 src/tests.cpp -o main -I/opt/homebrew/include -L/opt/homebrew/lib -larmadillo
// clang++ -std=c++20 src/tests.cpp src/Polynomials.cpp -I/opt/homebrew/include -L/opt/homebrew/lib -larmadillo -Wall

void runTests();

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
    runTests();

    return 0;
}

void runTests()
{
   cout << "_____________________________________________________________________________" << endl;
   cout << "______________________________[Polnomial Tests]______________________________" << endl;

    Polynomial poly;
    cout << poly.toString() << endl;

    assert(poly == Polynomial(std::vector<Term>{Term{0, 0}}, 0, 0));
    assert(poly == Polynomial(std::vector<Term>{Term{0, 0}}, 0, 9));
    assert(poly == Polynomial(std::vector<Term>{Term{0, 0}}, -3, 4));


    poly = Polynomial(vector<Term>{Term{3,0}, Term{1,1}, Term{0,2}, Term{9,3}}, 0, 3);
    cout << poly.toString() << endl;
    assert(poly.toString() == "3.000000x^0 + 1.000000x^1 + 0.000000x^2 + 9.000000x^3");

    Polynomial poly2 = Polynomial(vector<Term>{Term{3,-1}, Term{3,1}}, 0, 3);

    // polynomial operation
    assert(poly != poly2);
    assert(!(poly == poly2));

    // scalar operation and .toString()
    cout << (poly + 2.0).toString() << endl;
    assert((poly + 2.0).toString() == "5.000000x^0 + 1.000000x^1 + 0.000000x^2 + 9.000000x^3");
    assert(poly.toString() == "3.000000x^0 + 1.000000x^1 + 0.000000x^2 + 9.000000x^3");
    assert((poly - 2.0).toString() == "1.000000x^0 + 1.000000x^1 + 0.000000x^2 + 9.000000x^3");
    assert((poly * 2.0).toString() == "6.000000x^0 + 2.000000x^1 + 0.000000x^2 + 18.000000x^3");
    assert((poly / 2.0).toString() == "1.500000x^0 + 0.500000x^1 + 0.000000x^2 + 4.500000x^3");
    cout << (poly / 2.0).toString() << endl;

    assert(Polynomial(vector<Term>{Term{4,0}},0 ,0) == 4);

    // isMonomial
    cout << (Polynomial().isMonomial() ? "True" : "False") << endl;
    cout << (Polynomial(vector<Term>{Term{3,2}}, 2, 2).isMonomial() ? "True" : "False") << endl;
    assert(Polynomial().isMonomial());
    assert(Polynomial(vector<Term>{Term{3,2}}, 2, 2).isMonomial());
    assert(!Polynomial(vector<Term>{Term{3,2}, Term{1,2}}, 2, 2).isMonomial());

    // findExponent(int)
    assert(Polynomial(vector<Term>{Term{3, -1},
                                   Term{1, 2}}, 2, 2)
                                   .findExponent(2) == 1);

    assert(Polynomial(vector<Term>{Term{3, -2},
                                   Term{1, -1},
                                   Term{3, 2},
                                   Term{1, 3}}, 2, 2)
                                   .findExponent(3) == 3);

    assert(Polynomial(vector<Term>{Term{2, -20},
                                   Term{4, -15},
                                   Term{8, -10},
                                   Term{16, -5},
                                   Term{32, -1}}, 2, 2)
                                   .findExponent(-10) == 2);

    // density()
    poly2 = Polynomial(vector<Term>{Term{3,-1}, Term{1,2}}, -1, 2);
    std::cout << "<------------->" << std::endl;
    poly2.densify();
    std::cout << "<------------->" << std::endl;
    assert(poly2 == Polynomial(vector<Term>{Term{3, -1},
                                            Term{0, 0},
                                            Term{0, 1},
                                            Term{1, 2}}, -1, 2));
    std::cout << "<------------->" << std::endl;


    poly2 = Polynomial(vector<Term>{Term{3,1}, Term{1,2}}, 1, 2);
      std::cout << "<------------->" << std::endl;

    poly2.densify(-1,3);
      std::cout << "<------------->" << std::endl;

    assert(poly2 == Polynomial(vector<Term>{Term{0, -1},
                                            Term{0, 0},
                                            Term{3, 1},
                                            Term{1, 2},
                                            Term{0, 3}}, 2, 2));

    cout << "_____________________________________________________________________________" << endl;
}
