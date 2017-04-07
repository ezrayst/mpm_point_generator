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

  generate_material_points(x1, x2, y1, y2, x_spacing, y_spacing);
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

void Mesh::generate_material_points(const double& x1, const double& x2,
                                    const double& y1, const double& y2,
                                    const double& x_spacing,
                                    const double& y_spacing) {
  //! Calculations to generate material points
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