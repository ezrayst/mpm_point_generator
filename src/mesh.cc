#include "mesh.h"

template <unsigned Tdim>
void Mesh<Tdim>::read_file(const std::string& inputfilename) {
  double x1, x2, y1, y2, z1, z2, x_spacing, y_spacing, z_spacing;

  std::ifstream inputFile;
  inputFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  inputFile.open(inputfilename);

  inputFile >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> x_spacing >> y_spacing >>
      z_spacing;
  inputFile.close();

  std::cout << "The input file has been read."
            << "\n";

  std::array<double, Tdim> corner1;
  std::array<double, Tdim> corner2;
  std::vector<double> spacings;

  if (Tdim == 1) {
    corner1 = {x1};
    corner2 = {x2};
    spacings = {x_spacing};
  } else if (Tdim == 2) {
    corner1 = {x1, y1};
    corner2 = {x2, y2};
    spacings = {x_spacing, y_spacing};
  } else {
    corner1 = {x1, y1, z1};
    corner2 = {x2, y2, z2};
    spacings = {x_spacing, y_spacing, z_spacing};
  }

  std::vector<std::array<double, Tdim>> corners{corner1, corner2};
  corners_ = corners;
  spacings_ = spacings;
}

template <unsigned Tdim>
void Mesh<Tdim>::write_output_file(const std::string& outputfilename) {
  std::ofstream outputFile(outputfilename);
  for (auto const& point : points_) {
    if (Tdim == 1) {
      outputFile << point->id() << "," << point->coords().at(0) << "\n";
    } else if (Tdim == 2) {
      outputFile << point->id() << "," << point->coords().at(0) << ","
                 << point->coords().at(1) << "\n";
    } else {
      outputFile << point->id() << "," << point->coords().at(0) << ","
                 << point->coords().at(1) << "," << point->coords().at(2)
                 << "\n";
    }
  }

  outputFile.close();
  std::cout << "The output file has been generated."
            << "\n";
}

template <unsigned Tdim>
void Mesh<Tdim>::compute_num_points() {

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

  int l = 0;
  std::array<double, Tdim> coord;

  if (Tdim == 1) {
    for (int i = 0; i < num_points_.at(0); ++i) {
      coord = {corners_.at(0).at(0) + i * spacings_.at(0)};
      points_.emplace_back(std::unique_ptr<MaterialPoint<Tdim>>(
          new MaterialPoint<Tdim>(l, coord)));
      l += 1;
    }
  } else if (Tdim == 2) {
    for (int i = 0; i < num_points_.at(1); ++i)
      for (int j = 0; j < num_points_.at(0); ++j) {
        coord = {corners_.at(0).at(0) + j * spacings_.at(0),
                 corners_.at(0).at(1) + i * spacings_.at(1)};
        points_.emplace_back(std::unique_ptr<MaterialPoint<Tdim>>(
            new MaterialPoint<Tdim>(l, coord)));
        l += 1;
      }
  } else {
    for (int i = 0; i < num_points_.at(2); ++i)
      for (int j = 0; j < num_points_.at(1); ++j)
        for (int k = 0; k < num_points_.at(0); ++k) {
          coord = {corners_.at(0).at(0) + k * spacings_.at(0),
                   corners_.at(0).at(1) + j * spacings_.at(1),
                   corners_.at(0).at(2) + i * spacings_.at(2)};
          points_.emplace_back(std::unique_ptr<MaterialPoint<Tdim>>(
              new MaterialPoint<Tdim>(l, coord)));
          l += 1;
        }
  }
}