#ifndef POINT_H
#define POINT_H

#include <array>
#include <vector>

//! \brief    Class to store points with index and coordinates
//! \details  Includes constructor to make the MaterialPoint
//! \tparam   Tdim (1D, 2D or 3D)

template <unsigned Tdim>
class MaterialPoint {
 public:
  //! \brief  Make constructor for point including index and coordinates
  MaterialPoint(unsigned id, const std::vector<double> coords) {
    id_ = id;
    coords_ = coords;
  }

  //! Get the private properties using two functions
  //! To return id_
  unsigned id() const { return id_; }
  
  //! To return coords_
  std::vector<double> coords() const { return coords_; }

 private:
  //! id_ is the index would be a positive integer starting from 0 as index
  unsigned id_;
  
  //! coords_ would be an array of size Tdim, containing x,y,z coordinates
  std::vector<double> coords_;
};

#endif /* POINT_H */