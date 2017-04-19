//! MPM Point Generator
//!
//! The main code to generate points within a rectangle
//! Rectangular with input: (x1) x-coordinate left bottom corner
//!                         (y1) y-coordinate left bottom corner
//!                         (x2) x-coordinate right top corner
//!                         (y2) y-coordinate right top corner
//!                         (m)     making n grid in x-direction
//!                         (n)     making m grid in y-direction
//!

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

    Mesh points(inputfilename);
    points.generate_material_points();
    points.write_output_file(outputfilename);

  }

  catch (std::exception& except) {
    std::cout << "Caught exception: '" << except.what() << "'\n";
    return EXIT_FAILURE;
  }
}
