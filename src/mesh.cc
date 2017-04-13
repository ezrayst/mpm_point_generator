#include "mesh.h"

void Mesh::read_file(const std::string& inputfilename) {
  double x1, x2, y1, y2, x_spacing, y_spacing;

  std::ifstream inputFile;
  inputFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  inputFile.open(inputfilename);

  inputFile >> x1 >> y1 >> x2 >> y2 >> x_spacing >> y_spacing;
  inputFile.close();

  std::cout << "The input file has been read."
            << "\n";

  std::array<double, 2> corner1{{x1, y1}};
  std::array<double, 2> corner2{{x2, y2}};
  Mesh::register_corners(corner1, corner2);

  Mesh::register_spacing(x_spacing, y_spacing);

  Mesh::compute_num_points(corners_, spacing_);

  generate_material_points();
}

void Mesh::write_output_file(const std::string& outputfilename) {
  std::ofstream outputFile(outputfilename);
  for (auto const& point : points_) {
    outputFile << point->id() << "," << point->coords().at(0) << ","
               << point->coords().at(1) << "\n";
  }

  outputFile.close();
  std::cout << "The output file has been generated."
            << "\n";
}

void Mesh::generate_material_points() {
  //! Calculations to generate material points

  //! double x1 = corners_.at(0).at(0);
  //! double y1 = corners_.at(0).at(1);
  //! double x2 = corners_.at(1).at(0);
  //! double y2 = corners_.at(1).at(1);
  //! double x_spacing = spacing_.at(0);
  //! double y_spacing = spacing_.at(1);
  //! int num_points_x = num_points_.at(0);
  //! int num_points_y = num_points_.at(1);

  int k = 0;

  for (int i = 0; i < num_points_.at(1); ++i)
    for (int j = 0; j < num_points_.at(0); ++j) {
      std::array<double, 2> coord{{corners_.at(0).at(0) + j * spacing_.at(0), corners_.at(0).at(1) + i * spacing_.at(1)}};
      points_.emplace_back(
          std::unique_ptr<MaterialPoint>(new MaterialPoint(k, coord)));
      k += 1;
    }
}

  void Mesh::register_corners(const std::array<double, 2> &corner1, const std::array<double, 2> &corner2) {
    //! Make function for corners
    //! Input would include x and y coordinate of the corner
    corners_.push_back(corner1);
    corners_.push_back(corner2);
  };

  void Mesh::register_spacing(const double& x_spacing, const double& y_spacing) {
    //! Make function for spacing
    spacing_.push_back(x_spacing);
    spacing_.push_back(y_spacing);
  }

  void Mesh::compute_num_points(std::vector<std::array<double, 2>> &corners, std::vector<double> &spacing) {
    
    //! Make function to compute the total number of points in both x and y directions

    const int num_points_x = static_cast<int>(ceil((corners.at(1).at(0) - corners.at(0).at(0)) / spacing.at(0) + 1));
    const int num_points_y = static_cast<int>(ceil((corners.at(1).at(1) - corners.at(0).at(1)) / spacing.at(1) + 1));
    
    num_points_.push_back(num_points_x);
    num_points_.push_back(num_points_y);
  }