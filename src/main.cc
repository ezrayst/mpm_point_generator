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
#include <fstream>
#include <iostream>
#include <math.h>
#include <memory>
#include <vector>

#include "point.h"

int main() {
  double x1, x2, y1, y2, x_spacing, y_spacing;

  try {
    //! Reading input file
    //! Error would be reported

    std::ifstream inputFile;
    inputFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    inputFile.open("../bin/input_coords.txt");

    inputFile >> x1 >> y1 >> x2 >> y2 >> x_spacing >> y_spacing;
    inputFile.close();

    std::cout << "The input file has been read."
              << "\n";

    //! Main calculation
    const int num_points_x = static_cast<int>(ceil((x2 - x1) / x_spacing + 1));
    const int num_points_y = static_cast<int>(ceil((y2 - y1) / y_spacing + 1));

    std::vector<std::shared_ptr<MaterialPoint>> points;
    int k = 0;

    for (int i = 0; i < num_points_y; ++i)
      for (int j = 0; j < num_points_x; ++j) {
        std::array<double, 2> coord{{x1 + j * x_spacing, y1 + i * y_spacing}};
        std::shared_ptr<MaterialPoint> point(new MaterialPoint(k, coord));
        points.push_back(point);
        k += 1;
      }

    std::ofstream outputFile("../bin/mpm_points.txt");
    for (auto& point : points) {
      outputFile << point->id() << "," << point->coords().at(0) << ","
                 << point->coords().at(1) << "\n";
    }

    outputFile.close();

    std::cout << "The output file has been generated." << "\n";
  }

  catch (std::exception& except) {
    std::cout << "Caught exception: '" << except.what() << "'\n";
    return EXIT_FAILURE;
  }
}
