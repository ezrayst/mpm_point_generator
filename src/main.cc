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
    std::string inputFilename;
    std::string outputFilename;

    std::cout << "Type the input file name, default: [../bin/input_coords.txt]: ";
    std::getline(std::cin, inputFilename);

    if (inputFilename == "")
      inputFilename = "../bin/input_coords.txt";

    std::cout << "Type the output file name, default: [../bin/mpm_points.txt]: ";  
    std::getline(std::cin, outputFilename);
   
    if (outputFilename == "")
      outputFilename = "../bin/mpm_points.txt";
   
    
    Mesh points;
    points.ReadFile(inputFilename);
    points.WriteOutputFile(outputFilename);  

  }

  catch (std::exception& except) {
    std::cout << "Caught exception: '" << except.what() << "'\n";
    return EXIT_FAILURE;
  }
}
