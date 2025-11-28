#include "knot.hpp"
#include "exception.hpp"

/*
    @brief Constructs a Knot object from a given planar diagram.
    @param planarDiagram A vector of crossings representing the knot's planar diagram.
    ! planarDiagram must be simplified to protect it from isomophism ambiguity
*/
Knot::Knot(const std::vector<crossing> &planarDiagram)
{
    if(isConcistent())
    {
      throw kle::InconsistentPlanarDiagram("");
    }

    _planarDiagram = std::move(planarDiagram);
}

/*

    Source: Knot Theory by Charles Livingston, chapter Section 3.5. The Alexander Polynomial
*/
arma::Mat<std::string> Knot::alexanderMatrix() const
{
    

}

void Knot::reduce() const
{

}
