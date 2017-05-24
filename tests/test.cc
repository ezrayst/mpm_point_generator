#define CATCH_CONFIG_MAIN

#include <array>
#include <cmath>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

#include "catch.hpp"
#include "mesh.h"

TEST_CASE("main is checked through 3D", "[main][3D]") {
	
	const unsigned Tdim = 3;
	std::string inputfilename = "../bin/test.json";
	std::string outputfilename_points = "../bin/test_output_points.txt";
	std::string outputfilename_stress = "../bin/test_output_stress.txt";

	std::unique_ptr<Mesh<Tdim>> points(new Mesh<Tdim>(inputfilename));
	points->generate_material_points();
	points->generate_initial_stress();
	points->write_output_points(outputfilename_points);
	points->write_output_stress(outputfilename_stress);

	REQUIRE(points->density() == 20);
	REQUIRE(points->K0() == 0.5);
	REQUIRE(points->tot_points() == 27);
	REQUIRE(points->num_points().at(0) == 3);
	REQUIRE(points->num_points().at(1) == 3);
	REQUIRE(points->num_points().at(2) == 3);
}





