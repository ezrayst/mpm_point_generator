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
  std::array<std::array<double, 2>, 2> corner{{corner1, corner2}};
  Mesh::compute_corners(corner);

  std::array<double, 2> space{{x_spacing, y_spacing}};      
  Mesh::compute_spacing(space);

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

  double x1 = corners().at(0).at(0);
  double y1 = corners().at(0).at(1);
  double x2 = corners().at(1).at(0);
  double y2 = corners().at(1).at(1);
  double x_spacing = spacing().at(0);
  double y_spacing = spacing().at(1);

  const int num_points_x = static_cast<int>(ceil((x2 - x1) / x_spacing + 1));
  const int num_points_y = static_cast<int>(ceil((y2 - y1) / y_spacing + 1));

  int k = 0;

  for (int i = 0; i < num_points_y; ++i)
    for (int j = 0; j < num_points_x; ++j) {
      std::array<double, 2> coord{{x1 + j * x_spacing, y1 + i * y_spacing}};
      points_.emplace_back(
          std::unique_ptr<MaterialPoint>(new MaterialPoint(k, coord)));
      k += 1;
    }
}