#ifndef INITSTRESS_H
#define INITSTRESS_H

#include <array>
#include <vector>

//! \brief    Class to store initial stress
//! \details  Includes constructor to make the MaterialPoint
//! \tparam   Tdim (1D, 2D or 3D)

template <unsigned Tdim>
class InitStress {
 public:
  //! \brief  Make constructor for initial stress
  InitStress(unsigned id, const std::array<double, 6> stress) {
    id_ = id;
    stress_ = stress;
  }

  //! Get the private properties using two functions
  //! To return id_
  unsigned id() const { return id_; }

  //! To return stress_
  std::array<double, 6> stress() const { return stress_; }

 private:
  //! id_ is the index would be a positive integer starting from 0 as index
  unsigned id_;

  //! stress_ is the array of stresses in Voigt Notation
  //! sig_x  sig_y  sig_z  tau_yz  tau_zx  tau_xy
  //! Note that positive is tension
  std::array<double, 6> stress_;
};

#endif /* INITSTRESS_H */