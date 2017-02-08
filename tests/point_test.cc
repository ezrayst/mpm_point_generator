// Pointbase test
#include <limits>

#include "catch.hpp"
#include "point.h"

//! \brief Check node base class for 1D case
TEST_CASE("Point base is checked for 1D case", "[point][2D]") {
  //! Check for id = 0
  SECTION("Point id is zero") {
    // long long id = 0;
    // auto node = std::make_shared<felib::Point>(id, coords);
    // REQUIRE(node->id() == 0);
  }
}
