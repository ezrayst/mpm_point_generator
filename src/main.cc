//! MPM Point Generator
//!
//! The main code to generate points within a rectangle
//! Rectangular with input: (x1)          x-coordinate left bottom corner
//!                         (y1)          y-coordinate left bottom corner
//!                         (z1)          z-coordinate left bottom corner
//!                         (x2)          x-coordinate right top corner
//!                         (y2)          y-coordinate right top corner
//!                         (z2)          z-coordinate right top corner
//!                         (x_spacing)   spacing in x-coordinate
//!                         (y_spacing)   spacing in y-coordinate
//!                         (z_spacing)   spacing in z-coordinate
//!                         For 2D case, the z component is ignored
//!                         For 1D case, both the y and z component are ignored

#include <array>
#include <cmath>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

#include "mesh.h"

int main() {
  try {
    //! Reading input file
    //! Error would be reported

    //! User input inputFilename and outputFilename
    std::string inputfilename;
    std::string outputfilename;

    std::cout
        << "Type the input file name, default: [../bin/input_coords.txt]: ";
    std::getline(std::cin, inputfilename);
    if (inputfilename == "") inputfilename = "../bin/input_coords.txt";

    std::cout
        << "Type the output file name, default: [../bin/mpm_points.txt]: ";
    std::getline(std::cin, outputfilename);
    if (outputfilename == "") outputfilename = "../bin/mpm_points.txt";

    const unsigned Tdim = 3;

    std::unique_ptr<Mesh<Tdim>> points(new Mesh<Tdim>(inputfilename));
    points->generate_material_points();
    points->write_output_file(outputfilename);

  }

  catch (std::exception& except) {
    std::cout << "Caught exception: '" << except.what() << "'\n";
    return EXIT_FAILURE;
  }
}
