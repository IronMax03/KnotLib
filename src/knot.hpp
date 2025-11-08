#pragma once

#include <armadillo>
#include <cstdint>
#include <vector>

/**
 * @struct crossing
 * @brief Encapsulates the four directed arcs that meet at a knot crossing.
 *
 * The arcs follow the customary overstrand/understrand orientation ordering.
 */
struct crossing
{
  crossing(uint16_t arcsA, uint16_t arcsB, uint16_t arcsC, uint16_t arcsD)
  {
    arcs[0] = arcsA;
    arcs[1] = arcsB;
    arcs[2] = arcsC;
    arcs[3] = arcsD;
  }

  /// Identifiers of the four oriented arcs at the crossing.
  uint16_t arcs[4];

  /// @brief True for a right-handed crossing, false for left-handed.
  bool sign;

  inline uint16_t over_in() { return arcs[0]; }
  inline uint16_t under_out() { return arcs[1]; }
  inline uint16_t over_out() { return arcs[2]; }
  inline uint16_t under_in() { return arcs[3]; }
};

class Knot
{
public:
  Knot();
  Knot(const std::vector<crossing> &planarDiagram);

  arma::Mat<std::string> alexanderMatrix() const;
  arma::Mat<int> colorMatrix() const;

private:
  std::vector<crossing> _planarDiagram;

  bool isConcistent() const;
  void reduce() const;
};