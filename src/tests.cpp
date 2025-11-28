#include <iostream>
#include <cassert>

#define DEGREE_TYPE int

#include "knot.hpp"
#include "Polynomials.hpp"

using namespace std;
using namespace arma;

// clang++ -std=c++14 src/tests.cpp -o main -I/opt/homebrew/include -L/opt/homebrew/lib -larmadillo
// clang++ -std=c++20 src/tests.cpp src/Polynomials.cpp -I/opt/homebrew/include -L/opt/homebrew/lib -larmadillo -Wall

void runTests();
void equalAsserts(vector<Term> poly1);
void testPolySum(vector<Term> poly1, vector<Term> poly2, vector<Term> Expected);

int main()
{
    mat A = randu<mat>(2, 2);
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
    cout << "_________________________________[Term Tests]________________________________" << endl;
    Term t1{3, 1};
    Term t2{3, 1};
    assert(t1 == t2);

    t1 *= 2;
    t2.coefficient *= 2;
    assert(t1 == t2);

    t1 /= 2;
    t2.coefficient /= 2;
    assert(t1 == t2);

    cout << "All Term Tests Passed" << endl << endl;
    cout << "______________________________[Polnomial Tests]______________________________" << endl;

    // constructor
    equalAsserts(vector<Term>{Term{1, -2}, Term{8, -1}, Term{2, 1}, Term{0, 2}, Term{5, 4}});
    equalAsserts(vector<Term>{Term{3, 0}, Term{1, 1}, Term{0, 2}, Term{9, 3}});
    equalAsserts(vector<Term>{Term{0, -20}, Term{3, 34}});
    equalAsserts(vector<Term>{Term{0, -20}});
    equalAsserts(vector<Term>{Term{3, 34}});
    equalAsserts(vector<Term>{});
    cout << endl << "Constructor Tests [PASSED]" << endl << endl<< endl;

    // scalar operation and .toString()
    Polynomial poly(vector<Term>{Term{3, 0}, Term{1, 1}, Term{0, 2}, Term{9, 3}});
    cout << (poly + 2.0).toString() << endl;
    assert((poly + 2.0).toString() == "5.000000x^0 + 1.000000x^1 + 0.000000x^2 + 9.000000x^3");
    assert(poly.toString() == "3.000000x^0 + 1.000000x^1 + 0.000000x^2 + 9.000000x^3");
    assert((poly - 2.0).toString() == "1.000000x^0 + 1.000000x^1 + 0.000000x^2 + 9.000000x^3");
    assert((poly * 2.0).toString() == "6.000000x^0 + 2.000000x^1 + 0.000000x^2 + 18.000000x^3");
    assert((poly / 2.0).toString() == "1.500000x^0 + 0.500000x^1 + 0.000000x^2 + 4.500000x^3");
    cout << (poly / 2.0).toString() << endl;
    cout << endl << ".toString() Tests [PASSED]" << endl << endl<< endl;


    assert(Polynomial(vector<Term>{Term{4, 0}}, 0, 0) == 4);

    // isMonomial
    cout << (Polynomial().isMonomial() ? "True" : "False") << endl;
    cout << (Polynomial(vector<Term>{Term{3, 2}}, 2, 2).isMonomial() ? "True" : "False") << endl;
    assert(Polynomial().isMonomial());
    assert(Polynomial(vector<Term>{Term{3, 2}}, 2, 2).isMonomial());
    assert(!Polynomial(vector<Term>{Term{3, 2}, Term{1, 2}}, 2, 2).isMonomial());
    cout << endl << ".isMonomial() Tests [PASSED]" << endl << endl<< endl;
    

    // findExponent(int)
    assert(Polynomial(vector<Term>{Term{3, -1},
                                   Term{1, 2}},
                      2, 2)
               .findExponent(2) == 1);

    assert(Polynomial(vector<Term>{Term{3, -2},
                                   Term{1, -1},
                                   Term{3, 2},
                                   Term{1, 3}},
                      2, 2)
               .findExponent(3) == 3);

    assert(Polynomial(vector<Term>{Term{2, -20},
                                   Term{4, -15},
                                   Term{8, -10},
                                   Term{16, -5},
                                   Term{32, -1}},
                      2, 2)
               .findExponent(-10) == 2);
    cout << endl << ".findExponent(int) Tests [PASSED]" << endl << endl<< endl;


    // density()
    Polynomial poly2(vector<Term>{Term{3, -1}, Term{1, 2}}, -1, 2);
    poly2.densify();
    cout << poly2.toString() << endl;
    assert(poly2 == Polynomial(vector<Term>{Term{3, -1},
                                            Term{0, 0},
                                            Term{0, 1},
                                            Term{1, 2}},
                               -1, 2));

    poly2 = Polynomial(vector<Term>{Term{3, 1}, Term{1, 2}}, 1, 2);
    poly2.densify(-1, 3);
    assert(poly2 == Polynomial(vector<Term>{Term{0, -1},
                                            Term{0, 0},
                                            Term{3, 1},
                                            Term{1, 2},
                                            Term{0, 3}},
                               -1, 3));
    cout << endl << ".density() Tests [PASSED]" << endl << endl<< endl;


    // simplify()
    poly2 = Polynomial(vector<Term>{Term{0, -1},
                                    Term{3, 0},
                                    Term{0, 1},
                                    Term{5, 2},
                                    Term{0, 3}},
                       -1, 3);
    poly2.simplify();
    cout << poly2.toString() << endl;
    assert(poly2 == Polynomial(vector<Term>{Term{3, 0}, Term{5, 2}}, 0, 2));

    poly2 = Polynomial(vector<Term>{Term{0, 0}, Term{0, 1}, Term{0, 2}}, 0, 2);
    poly2.simplify();
    cout << poly2.toString() << endl;
    assert(poly2 == Polynomial(vector<Term>{Term{0, 0}}, 0, 0));

    poly2 = Polynomial(vector<Term>{Term{1, -5}, Term{0, -4}, Term{2, -3}}, -5, -3);
    poly2.simplify();
    cout << poly2.toString() << endl;
    assert(poly2 == Polynomial(vector<Term>{Term{1, -5}, Term{2, -3}}, -5, -3));
    cout << endl << ".simplify() Tests [PASSED]" << endl << endl<< endl;


    // polynomial operation
    poly = Polynomial();
    cout << poly.toString() << endl;

    assert(poly == Polynomial(std::vector<Term>{Term{0, 0}}, 0, 0));
    assert(poly == Polynomial(std::vector<Term>{Term{0, 0}}, 0, 9));
    assert(poly == Polynomial(std::vector<Term>{Term{0, 0}}, -3, 4));

    poly = Polynomial(vector<Term>{Term{3, 0}, Term{1, 1}, Term{0, 2}, Term{9, 3}}, 0, 3);
    cout << poly.toString() << endl;
    assert(poly.toString() == "3.000000x^0 + 1.000000x^1 + 0.000000x^2 + 9.000000x^3");

    poly2 = Polynomial(vector<Term>{Term{3, -1}, Term{3, 1}}, 0, 3);

    assert(poly != poly2);
    assert(!(poly == poly2));

    // addition
    testPolySum(vector<Term>{Term{1, 5}, Term{2, 6}},
                vector<Term>{Term{1, 5}, Term{2, 6}},
                vector<Term>{Term{2, 5}, Term{4, 6}});

    testPolySum(vector<Term>{Term{3, 5}, Term{2, 6}},
                vector<Term>{Term{2, 5}, Term{2, 6}},
                vector<Term>{Term{5, 5}, Term{4, 6}});

    testPolySum(vector<Term>{Term{3, 0}, Term{1, 1}, Term{-1, 2}},
                vector<Term>{Term{3, -1}, Term{3, 1}, Term{0, 2}, Term{4, 3}},
                vector<Term>{Term{3, -1}, Term{3, 0}, Term{4, 1}, Term{-1, 2}, Term{4, 3}});

    cout << endl << "polynomial operation Tests [PASSED]" << endl << endl<< endl;


    cout << "_____________________________________________________________________________" << endl;
}

void equalAsserts(const vector<Term> poly1)
{
    const Polynomial poly2 = Polynomial(poly1);
    assert(poly1.size() == poly2.Terms.size());

    cout << "equal: ";
    for (size_t i = 0; i < poly1.size(); i++)
    {   
        cout << poly1.at(i).coefficient << "x^" << poly1.at(i).degree << " + ";
        assert(poly1.at(i) == poly2.Terms.at(i));
    }
    cout << endl;
}

void testPolySum(vector<Term> poly1, vector<Term> poly2, vector<Term> Expected)
{
    cout << " ________________________________________________________________" << endl;
    cout << Polynomial(poly1).toString() << endl;
    cout << "+" << endl;
    cout << Polynomial(poly2).toString() << endl;
    Polynomial sum = (Polynomial(poly1) + Polynomial(poly2));
    cout << "poly1 + poly2 = " << sum.toString() << endl;

    assert(sum == Polynomial(Expected));

    cout << "poly2 + poly1 = " << (Polynomial(poly2) + Polynomial(poly1)).toString() << endl;
    assert(sum == Polynomial(poly2) + Polynomial(poly1));
}
