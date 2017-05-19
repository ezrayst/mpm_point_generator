#include "mesh.h"

template <unsigned Tdim>
void Mesh<Tdim>::read_file(const std::string& inputfilename) {

  std::ifstream inputFile;
  inputFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  inputFile.open(inputfilename);

  //! Create a temporary variable that would be used in the for loop
  double file;

  //! Declare 2 vectors of the corner
  corners_ = {{},{}};

  //! Loop through the input file to get the data
  for (unsigned i = 0; i < Tdim * 3; ++i) {
    inputFile >> file;

    if (i < Tdim) {
      corners_.at(0).push_back(file);
    } else if (i < Tdim * 2) {
      corners_.at(1).push_back(file);
    } else {
      spacings_.push_back(file);
    }
  }

  inputFile.close();

  std::cout << "The input file has been read."
            << "\n";
}

template <unsigned Tdim>
void Mesh<Tdim>::write_output_file(const std::string& outputfilename) {
  std::ofstream outputFile(outputfilename);

  //! Write number of points generated
  unsigned tot_points = std::accumulate(num_points_.begin(), num_points_.end(), 1, std::multiplies<unsigned>()); 

  outputFile << tot_points << "\n";

  //! Set precision
  // outputFile.precision(5);
  // outputFile.setf(std::ios::fixed);
  // outputFile.setf(std::ios::showpoint);

  //! Write the coordinates of the points generated
  //! [X] [Y] [Z] --> check the precision of the number
  for (auto const& point : points_) {
    for (double coordinate : point->coords()) {
      outputFile << coordinate << "\t";
    }
    outputFile << "\n";
  }

  outputFile.close();
  std::cout << "The output file has been generated."
            << "\n";
}

template <unsigned Tdim>
void Mesh<Tdim>::compute_num_points() {

  //! Make function to compute the total number of points in both x and y
  //! directions
  double number_point;

  for (unsigned i = 0; i < Tdim; ++i) {
    num_points_.emplace_back(static_cast<unsigned>(ceil(
        (corners_.at(1).at(i) - corners_.at(0).at(i)) / spacings_.at(i) + 1)));
  }
}

template <unsigned Tdim>
void Mesh<Tdim>::generate_material_points() {
  //! Calculations to generate material points
  //! i refers to z
  //! j refers to y
  //! k refers to x

  //! double x1 = corners_.at(0).at(0);
  //! double y1 = corners_.at(0).at(1);
  //! double z1 = corners_.at(0).at(2);
  //! double x2 = corners_.at(1).at(0);
  //! double y2 = corners_.at(1).at(1);
  //! double z2 = corners_.at(!).at(2);
  //! double x_spacing = spacing_.at(0);
  //! double y_spacing = spacing_.at(1);
  //! double z_spacing = spacing_.at(2);
  //! int num_points_x = num_points_.at(0);
  //! int num_points_y = num_points_.at(1);
  //! int num_points_z = num_points_.at(2);

  unsigned l = 0;

  if (Tdim == 1) {
    for (unsigned i = 0; i < num_points_.at(0); ++i) {
      std::vector<double> coord{corners_.at(0).at(0) + i * spacings_.at(0)};
      points_.emplace_back(std::unique_ptr<MaterialPoint<Tdim>>(
          new MaterialPoint<Tdim>(l, coord)));
      ++l;
    }
  } else if (Tdim == 2) {
    for (unsigned i = 0; i < num_points_.at(1); ++i)
      for (unsigned j = 0; j < num_points_.at(0); ++j) {
        std::vector<double> coord{corners_.at(0).at(0) + j * spacings_.at(0),
                                  corners_.at(0).at(1) + i * spacings_.at(1)};
        points_.emplace_back(std::unique_ptr<MaterialPoint<Tdim>>(
            new MaterialPoint<Tdim>(l, coord)));
        ++l;
      }
  } else {
    for (unsigned i = 0; i < num_points_.at(2); ++i)
      for (unsigned j = 0; j < num_points_.at(1); ++j)
        for (unsigned k = 0; k < num_points_.at(0); ++k) {
          std::vector<double> coord{corners_.at(0).at(0) + k * spacings_.at(0),
                                    corners_.at(0).at(1) + j * spacings_.at(1),
                                    corners_.at(0).at(2) + i * spacings_.at(2)};
          points_.emplace_back(std::unique_ptr<MaterialPoint<Tdim>>(
              new MaterialPoint<Tdim>(l, coord)));
          ++l;
        }
  }
}