#ifndef MESH_H
#define MESH_H

#include <cmath>

#include <algorithm>
#include <array>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <vector>

#include "point.h"

//! \brief    Class to generate MaterialPoint 
//! \details  Get input, generate material points, write output
//! \tparam   Tdim (1D, 2D or 3D)

template <unsigned Tdim>
class Mesh {
 public:
  //! Make a constructor for Mesh which contains corners and spacings
  Mesh(const std::string& inputfilename) {
    read_file(inputfilename);
    compute_num_points();
  }

  //! Read the inputfile and store the corners and spacings from it
  void read_file(const std::string&);

  //! Produce the output file containing the materials points generated
  void write_output_file(const std::string&);

  //! Convert spacings to number of points generated in each direction
  void compute_num_points();

  //! Main function to loop and generate the material points
  void generate_material_points();

  //! Get the private properties
  //! Return num_points_
  const std::vector<unsigned> num_points() { return num_points_; }

 private:
  //! points_ is the vector that contains the MaterialPoint
  std::vector<std::unique_ptr<MaterialPoint<Tdim>>> points_;

  //! corners_ contains arrays of x,y,z coordinates of the corners
  std::vector<std::vector<double>> corners_;
  
  //! spacing_ contains the spacing specified in x,y,z directions
  std::vector<double> spacings_;
  
  //! num_points_ contains the total number of points in x,y,z directions.
  //! This depends on specified spacings
  std::vector<unsigned> num_points_;  
};

#include "mesh.tcc"

#endif /* MESH_H */