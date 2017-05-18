#ifndef MESH_H
#define MESH_H

//! C Header
#include <cmath>

#include <array>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

#include "point.h"

//! \brief    Class for the mesh
//! \tparam   Tdim (1D, 2D or 3D)

template <unsigned Tdim> class Mesh {
public:
  //! Make a constructor for Mesh which contains corners and spacings
  Mesh(const std::string &inputfilename) {
    read_file(inputfilename);
    compute_num_points();
  }

  //! Function to read the inputfile and store the corners and spacings
  void read_file(const std::string &);

  //! Function to produce the output file containing the materials points
  //! generated
  void write_output_file(const std::string &);

  //! Small function to convert spacings to number of points generated in the
  //! directions
  void compute_num_points();

  //! Main function to generate the material points
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

  std::vector<std::unique_ptr<MaterialPoint<Tdim>>> points_;
  std::vector<std::vector<double>> corners_;
  std::vector<double> spacings_;
  std::vector<int> num_points_;
};

#include "mesh.tcc"

#endif /* MESH_H */