#include "mesh.h"

template <unsigned Tdim>
void Mesh<Tdim>::read_file(const std::string &inputfilename) {

  //! Declare vectors of corner and spacings
  std::vector<double> corner1;
  std::vector<double> corner2;
  std::vector<double> spacings;

  std::ifstream inputFile;
  inputFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  inputFile.open(inputfilename);

  //! Create a temporary variable that would be used in the for loop
  double file;

  //! Loop through the input file to get the data
  for (int i = 0; i < Tdim * 3; ++i) {
    inputFile >> file;

    if (i < Tdim) {
      corner1.push_back(file);
    } else if (i < Tdim * 2) {
      corner2.push_back(file);
    } else {
      spacings.push_back(file);
    }
  }

  inputFile.close();

  std::cout << "The input file has been read."
            << "\n";

  std::vector<std::vector<double>> corners{corner1, corner2};
  corners_ = corners;
  spacings_ = spacings;
}

template <unsigned Tdim>
void Mesh<Tdim>::write_output_file(const std::string &outputfilename) {
  std::ofstream outputFile(outputfilename);

  //! Write number of points generated
  outputFile << num_points_.at(0) * num_points_.at(1) * num_points_.at(0) << "\n";

  //! Write the coordinates of the points generated 
  //! [X] [Y] [Z] --> Check the precision of the number
  for (auto const &point : points_) {
    if (Tdim == 1) {
      outputFile << point->coords().at(0) << "\n";

    } else if (Tdim == 2) {
      outputFile << point->coords().at(0) << "\t"
                 << point->coords().at(1) << "\n";

    } else {
      outputFile << point->coords().at(0) << "\t"
                 << point->coords().at(1) << "\t" << point->coords().at(2)
                 << "\n";
      ;
    }
  }

  outputFile.close();
  std::cout << "The output file has been generated."
            << "\n";
}

template <unsigned Tdim> void Mesh<Tdim>::compute_num_points() {

  //! Make function to compute the total number of points in both x and y
  //! directions

  const int num_points_x = static_cast<int>(ceil(
      (corners_.at(1).at(0) - corners_.at(0).at(0)) / spacings_.at(0) + 1));
  num_points_.push_back(num_points_x);

  if (Tdim >= 2) {
    const int num_points_y = static_cast<int>(ceil(
        (corners_.at(1).at(1) - corners_.at(0).at(1)) / spacings_.at(1) + 1));
    num_points_.push_back(num_points_y);
  }

  if (Tdim >= 3) {
    const int num_points_z = static_cast<int>(ceil(
        (corners_.at(1).at(2) - corners_.at(0).at(2)) / spacings_.at(2) + 1));
    num_points_.push_back(num_points_z);
  }
}

template <unsigned Tdim> void Mesh<Tdim>::generate_material_points() {
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

  int l = 0;

  if (Tdim == 1) {
    for (int i = 0; i < num_points_.at(0); ++i) {
      std::vector<double> coord{corners_.at(0).at(0) + i * spacings_.at(0)};
      points_.emplace_back(std::unique_ptr<MaterialPoint<Tdim>>(
          new MaterialPoint<Tdim>(l, coord)));
      ++l;
    }
  } else if (Tdim == 2) {
    for (int i = 0; i < num_points_.at(1); ++i)
      for (int j = 0; j < num_points_.at(0); ++j) {
        std::vector<double> coord{corners_.at(0).at(0) + j * spacings_.at(0),
                                  corners_.at(0).at(1) + i * spacings_.at(1)};
        points_.emplace_back(std::unique_ptr<MaterialPoint<Tdim>>(
            new MaterialPoint<Tdim>(l, coord)));
        ++l;
      }
  } else {
    for (int i = 0; i < num_points_.at(2); ++i)
      for (int j = 0; j < num_points_.at(1); ++j)
        for (int k = 0; k < num_points_.at(0); ++k) {
          std::vector<double> coord{corners_.at(0).at(0) + k * spacings_.at(0),
                                    corners_.at(0).at(1) + j * spacings_.at(1),
                                    corners_.at(0).at(2) + i * spacings_.at(2)};
          points_.emplace_back(std::unique_ptr<MaterialPoint<Tdim>>(
              new MaterialPoint<Tdim>(l, coord)));
          ++l;
        }
  }
}