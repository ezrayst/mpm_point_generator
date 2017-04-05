#include <array>
#include <vector>

#include "point.h"

class Mesh {
public:
  //! Make a constructor

  void read_file(const std::string& inputfilename){
    double x1, x2, y1, y2, x_spacing, y_spacing;

    std::ifstream inputFile;
    inputFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    inputFile.open(inputfilename);

    inputFile >> x1 >> y1 >> x2 >> y2 >> x_spacing >> y_spacing;
    inputFile.close();

    std::cout << "The input file has been read."
              << "\n";

    //! Main calculation
    const int num_points_x = static_cast<int>(ceil((x2 - x1) / x_spacing + 1));
    const int num_points_y = static_cast<int>(ceil((y2 - y1) / y_spacing + 1)); 

    int k = 0;

    for (int i = 0; i < num_points_y; ++i)
      for (int j = 0; j < num_points_x; ++j) {
        std::array<double, 2> coord{{x1 + j * x_spacing, y1 + i * y_spacing}};
        points_.emplace_back(std::unique_ptr<MaterialPoint> (new MaterialPoint(k, coord)));
        k += 1;
      }
  }


  void write_output_file(std::string outputfilename){
    std::ofstream outputFile(outputfilename);
    for (auto const& point : points_) {
      outputFile << point->id() << "," << point->coords().at(0) << ","
                 << point->coords().at(1) << "\n";
    }

    outputFile.close();

    std::cout << "The output file has been generated."
              << "\n";
  }

private:
  //! These are the parameters of the class Mesh
  //! points is the vector that contains the MaterialPoint

   std::vector<std::unique_ptr<MaterialPoint>> points_;
};