#include "mesh.h"

//! \brief    Open and read input files
//! \details  Get input, store in private variables
//! \tparam   Tdim (1D, 2D or 3D)
template <unsigned Tdim>
void Mesh<Tdim>::read_file(const std::string& inputfilename) {

  //! Open input file
  std::ifstream inputFile;
  inputFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  inputFile.open(inputfilename);

  //! Declare 2 vectors of the corner
  corners_.resize(2);

  //! Create a temporary variable that would be used in the for loop
  double value;

  //! Loop through the input file to get the data
  for (unsigned i = 0; i < Tdim; ++i) {
    inputFile >> value;
    corners_.at(0).push_back(value);
  }

  for (unsigned i = 0; i < Tdim; ++i) {
    inputFile >> value;
    corners_.at(1).push_back(value);
  }

  for (unsigned i = 0; i < Tdim; ++i) {
    inputFile >> value;
    spacings_.push_back(value);
  }

  //! Close input file and print notification
  inputFile.close();
  std::cout << "The input file has been read."
            << "\n";
}

//! \brief    Open and write output files
//! \details  Write total number of points, and coordinates of points
//! \tparam   Tdim (1D, 2D or 3D)
template <unsigned Tdim>
void Mesh<Tdim>::write_output_file(const std::string& outputfilename) {
  std::ofstream outputFile(outputfilename);

  //! Comput eand write the total number of points generated
  unsigned tot_points = std::accumulate(num_points_.begin(), num_points_.end(),
                                        1, std::multiplies<unsigned>());
  outputFile << tot_points << "\n";

  //! Set precision
  // outputFile.precision(5);
  // outputFile.setf(std::ios::fixed);
  // outputFile.setf(std::ios::showpoint);

  //! Write the coordinates of the points generated
  //! [X] [Y] [Z]
  //! Note that for 2D, z values are 0
  //! For 1D, both y and z values are 0
  for (auto const& point : points_) {
    for (double coordinate : point->coords()) {
      outputFile << coordinate << "\t";
    }
    outputFile << "\n";
  }

  //! Close output file and print notification
  outputFile.close();
  std::cout << "The output file has been generated."
            << "\n";
}

//! \brief    Calculate the number of points in each direction
//! \details  Get spacings_ (private), calculate, and store into private
//! \tparam   Tdim (1D, 2D or 3D)
template <unsigned Tdim>
void Mesh<Tdim>::compute_num_points() {

  //! Loop to obtain the number in each direction
  for (unsigned i = 0; i < Tdim; ++i) {
    num_points_.emplace_back(static_cast<unsigned>(ceil(
        (corners_.at(1).at(i) - corners_.at(0).at(i)) / spacings_.at(i) + 1)));
  }
}

//! \brief    Generate MaterialPoints and store them
//! \details  Generalize private variables, loop to generate points
//! \tparam   Tdim (1D, 2D or 3D)
template <unsigned Tdim>
void Mesh<Tdim>::generate_material_points() {
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

  //! Fill empty vectors so they are general 3D
  for (unsigned i = Tdim; i <= 3; ++i) {
    num_points_.push_back(1);
    corners_.at(0).push_back(0);
    corners_.at(1).push_back(0);
    spacings_.push_back(0);
  }

  //! Main loop to generate material points - generalized 3D
  unsigned l = 0;
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