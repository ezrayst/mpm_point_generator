#include <array>
#include <cmath>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

#include "point.h"

class Mesh {
public:
  //! Make a constructor
  void read_file(const std::string &);

  void write_output_file(const std::string &);

private:
  //! These are the parameters of the class Mesh
  //! points_ is the vector that contains the MaterialPoint

  std::vector<std::unique_ptr<MaterialPoint>> points_;
};