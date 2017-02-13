// MPM Point Generator
//
// The main code to generate points within a rectangle
// Rectangular with input: (x1) x-coordinate left bottom corner
//                         (y1) y-coordinate left bottom corner
//                         (x2) x-coordinate right top corner
//                         (y2) y-coordinate right top corner
//                         (m)     making n grid in x-direction
//                         (n)     making m grid in y-direction
//

#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <memory>

#include "point.h"

int main()
{
	double x1, x2, y1, y2, x_spacing, y_spacing;
	
	try
	{
		//! Reading input file
		std::ifstream inputFile;
		inputFile.open("../bin/input_coords.txt");

		if (inputFile.fail())
		{
			throw "Error: input file cannot be read.";
		}

		inputFile >> x1 >> y1 >> x2 >> y2 >> x_spacing >> y_spacing;
		inputFile.close();
	}
	
	catch (char const* errormesg)
	{
			std::cerr << errormesg;
			return EXIT_FAILURE;
	}

	
	std::cout << "The input file has been read." << "\n";
	
	//! Main calculation
	const int num_points_x = (x2 - x1) / x_spacing + 1;
	const int num_points_y = (y2 - y1) / y_spacing + 1;

	std::vector<std::shared_ptr<MaterialPoint>> points;

	for (int i=0; i < num_points_y; ++i)			//!< i is respect to y
		for (int j=0; j < num_points_x; ++j)		//!< j is respect to x
		{
			int k = i*num_points_y + j;
			std::array<double, 2> coord{{x1 + j*x_spacing, y1 + i*y_spacing}};
			std::shared_ptr<MaterialPoint> dummy_points(new MaterialPoint(k, coord));
			points.push_back(dummy_points);
		}
	std::ofstream outputFile("../bin/mpm_points.txt");
	for (auto& point : points)
	{
		outputFile << point->id() << "," << point->coords().at(0) << "," << point->coords().at(1) << "\n";
		point.reset();
	}

	outputFile.close();

	std::cout << "The output file has been generated.";
}


