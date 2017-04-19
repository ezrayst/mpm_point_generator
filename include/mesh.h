#include <array>
#include <cmath>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

#include "point.h"

class Mesh {
public:
  //! Make a constructor for Mesh which contains corners and spacings

  Mesh(const std::string &inputfilename, const std::string &outputfilename) {
    read_file(inputfilename);
    compute_num_points();
    generate_material_points();
    write_output_file(outputfilename);
  }

  //! The rest of functions

  void read_file(const std::string &);

  void write_output_file(const std::string &);

  void compute_num_points();

  void generate_material_points();

  //! Function to get private variable num_points_

  const std::vector<int> num_points() { return num_points_; }

private:
  //! These are the parameters of the class Mesh
  //! points_ is the vector that contains the MaterialPoint
  //! corners_ contains arrays of x-y coordinates of the corners
  //! spacing_ contains the spacing specified in x and y directions
  //! num_points_ contains the total number of points in x and y directions.
  //! This depends on specified spacings

  std::vector<std::unique_ptr<MaterialPoint>> points_;
  std::vector<std::array<double, 2>> corners_;
  std::vector<double> spacings_;
  std::vector<int> num_points_;
};