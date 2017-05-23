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

#include "initStress.h"
#include "point.h"

#include "json.hpp"

//! Short alias for convenience
using json = nlohmann::json;

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
  void write_output_points(const std::string&);

  //! Produce the output file containing the stress on each point
  void write_output_stress(const std::string&);

  //! Convert spacings to number of points generated in each direction
  void compute_num_points();

  //! Main function to loop and generate the material points
  void generate_material_points();

  //! Main function to loop through material points and generate initial stress
  void generate_initial_stress();

  //! Get the private properties

  //! Return num_points_
  const std::vector<unsigned> num_points() { return num_points_; }

  //! Return tot_points_
  const unsigned tot_points() { return tot_points_; }

  //! Return density_
  const double density() { return density_; }

  //! Return K0_
  const double K0() { return K0_; }

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

  //! tot_points_ is the total number of points generated
  unsigned tot_points_;

  //! density_ is the unit weight of the soil
  double density_;

  //! K0_ is the at rest pressure coefficient
  double K0_;

  //! stress_ is the array of stresses in Voigt Notation
  //! sig_x  sig_y  sig_z  tau_yz  tau_zx  tau_xy
  std::vector<std::unique_ptr<InitStress<Tdim>>> stresses_;
};

#include "mesh.tcc"

#endif /* MESH_H */