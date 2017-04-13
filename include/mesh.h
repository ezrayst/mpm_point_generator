#include <array>
#include <cmath>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

#include "point.h"

class Mesh {
public:

  void read_file(const std::string &);

  void write_output_file(const std::string &);

  void generate_material_points();

  void register_corners(const std::array<double, 2> &, const std::array<double, 2> &);

  void register_spacing(const double&, const double&);

  void compute_num_points(std::vector<std::array<double, 2>> &, std::vector<double> &);

private:
  //! These are the parameters of the class Mesh
  //! points_ is the vector that contains the MaterialPoint
  //! corners_ contains arrays of x-y coordinates of the corners
  //! spacing_ contains the spacing specified in x and y directions 
  //! num_points_ contains the number of points in x and y directions
  
  std::vector<std::unique_ptr<MaterialPoint>> points_;
  std::vector<std::array<double, 2>> corners_;
  std::vector<double> spacing_;
  std::vector<int> num_points_;

};