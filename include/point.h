#include <array>
#include <vector>

template <unsigned Tdim>

class MaterialPoint {
public:
  //! Make constructor for material point
  MaterialPoint(unsigned id, const std::array<double, Tdim> coords) {
    id_ = id;
    coords_ = coords;
  }

  //! Get the private properties using two functions
  //! To get the id_ and coords_

  unsigned id() const { return id_; }
  std::array<double, Tdim> coords() const { return coords_; }

private:
  //! These are the parameters of the class MaterialPoint
  //! id_ would be a positive integer starting from 0 as index
  //! coords_ would be an array of size Tdim, containing x and y coordinates

  unsigned id_;
  std::array<double, Tdim> coords_;
};