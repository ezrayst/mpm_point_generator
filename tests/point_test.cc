// Pointbase test
#include <limits>
#include <array>

#include "catch.hpp"
#include "point.h"

//! \brief 		Check that MaterialPoint will store right values
//! \details	Write arbritrary index and coordinate and store them

TEST_CASE("MaterialPoint base is checked in 3D", "[MaterialPoint][3D]") {
  
    unsigned index = 0;
    const unsigned Tdim = 3;
    std::array<double, 3> coordinate{0, 0, 0};
    auto node = std::unique_ptr<MaterialPoint<Tdim>>(new MaterialPoint<Tdim>(index, coordinate));
    
    REQUIRE(node->id() == 0);
    REQUIRE(node->coords().at(0) == 0);
    REQUIRE(node->coords().at(1) == 0);
    REQUIRE(node->coords().at(2) == 0);
}
