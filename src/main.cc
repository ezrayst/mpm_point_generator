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
    std::string outputfilename_points;
    std::string outputfilename_stress;

    std::cout
        << "Type the input file name, default: [../bin/soilParticles.txt]: ";
    std::getline(std::cin, inputfilename);
    if (inputfilename == "") inputfilename = "../bin/soilParticles.txt";

    std::cout << "Type the output file name for soil particles, default: "
                 "[../bin/soilParticles.smf]: ";
    std::getline(std::cin, outputfilename_points);
    if (outputfilename_points == "")
      outputfilename_points = "../bin/soilParticles.smf";

    std::cout << "Type the output file name for initial stress, default: "
                 "[../bin/initStressSoilP.dat]: ";
    std::getline(std::cin, outputfilename_stress);
    if (outputfilename_stress == "")
      outputfilename_stress = "../bin/initStressSoilP.dat";

    const unsigned Tdim = 2;

    std::unique_ptr<Mesh<Tdim>> points(new Mesh<Tdim>(inputfilename));
    points->generate_material_points();
    points->generate_initial_stress();
    points->write_output_points(outputfilename_points);
    points->write_output_stress(outputfilename_stress);

  }

  catch (std::exception& except) {
    std::cout << "Caught exception: '" << except.what() << "'\n";
    return EXIT_FAILURE;
  }
}
