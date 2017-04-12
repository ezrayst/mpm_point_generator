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

  //! Make function for corners
  //! Input would include x and y coordinate of the corner
  void compute_corners(const std::array<std::array<double, 2>, 2> corners) {
    corners_ = corners;
  };

  //! Make function for spacing
  void compute_spacing(const std::array<double, 2> spacings) {
    spacing_ = spacings;
  }

  //! To get the corners_ and spacing_
  std::array<std::array<double, 2>, 2> const corners() { return corners_ ; }
  std::array<double, 2> const spacing() { return spacing_ ; }

private:
  //! These are the parameters of the class Mesh
  //! points_ is the vector that contains the MaterialPoint
  //! corners_ contains arrays of x-y coordinates of the corners
  //! spacing_ contains the spacing specified in x and y directions 
  
  std::vector<std::unique_ptr<MaterialPoint>> points_;
  std::array<std::array<double, 2>, 2> corners_;
  std::array<double, 2> spacing_;

};