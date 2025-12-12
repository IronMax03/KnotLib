# Knotlib

Experimental C++20 library for computational knot theory.

## Compile Project
This project is intended to be compiled with `clang`. Other compilers might work but quality is only guaranteed with `clang`.  
### parameters:
some changes can be made during compilation by defining macros:
- `-DEGREE_TYPE=int` changes the polynomial exponent data types to `int`; this command also works for any fixed length integers among fast integers and least integers.

## Objectives
- Explore polynomial representations of knots.
- Prototype numerical tools for basic invariant computations.
- Collect reference material for future formal documentation.

## Longue Term Objectives
- GPU acceleration with CUDA
- Make an automated proofs
- Generate the Rolfsen Knot Table using KnotLib

## Current Status
- Polynomial class scaffolded.
- Exception utilities stubbed.
- Unit test harness in place (needs implementation).

# Research / References
- [Computing a Link Diagram From Its Exterior](https://www.researchgate.net/publication/372857920_Computing_a_Link_Diagram_From_Its_Exterior/link/64cb0892d394182ab39ae916/download). 

- [A user’s guide to basic knot and link theory](https://arxiv.org/pdf/2001.01472)
- [The Knot Book](https://www.math.cuhk.edu.hk/course_builder/1920/math4900e/Adams--The%20Knot%20Book.pdf?utm_source=chatgpt.com)
- [Planar Diagrams](https://katlas.org/wiki/Planar_Diagrams)
- [The Knot Atlas](https://katlas.org)
- [Knot Theory by Charles Livingsto](www.cambridge.org/core/books/knot-theory/C371803DC688F563B71257B78045753D#fndtn-information)