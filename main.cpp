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

class mat_points
{
public:
	mat_points(int id, std::array<double, 2> coords)
	{
		id_ = id;
		coords_ = coords;
	}
	int get_id()
	{
		return id_;
	}
	std::array<double, 2> get_coords()
	{
		return coords_;
	}
private:
	int id_;
	std::array<double, 2> coords_;
};

int main()
{
	double x1, x2, y1, y2, x_spacing, y_spacing;

	std::ifstream inputFile;
	inputFile.open("input_coords.txt");

	if (inputFile.fail())
	{
		std::cerr << "Error: input file cannot be read.";
		exit(1);
	}

	inputFile >> x1 >> y1 >> x2 >> y2 >> x_spacing >> y_spacing;
	inputFile.close();
	
	std::cout << "The input file has been read." << "\n";

	const int num_points_x = (x2 - x1) / x_spacing + 1;
	const int num_points_y = (y2 - y1) / y_spacing + 1;

	std::vector<std::shared_ptr<mat_points>> points;

	for (int i=0; i < num_points_y; ++i)			// i is respect to y
		for (int j=0; j < num_points_x; ++j)		// j is respect to x
		{
			int k = i*num_points_y + j;
			std::array<double, 2> coord{{x1 + j*x_spacing, y1 + i*y_spacing}};
			std::shared_ptr<mat_points> dummy_points = std::make_shared<mat_points>(k, coord);
			points.push_back(dummy_points);
		}
	std::ofstream outputFile("mpm_points.txt");
	for (auto &point : points)
	{
		auto p = point.get();
		outputFile << p->get_id() << "," << p->get_coords().at(0) << "," << p->get_coords().at(1) << "\n";
//		std::cout << "Count before = " << point.use_count() << '\n';
		point.reset();
//		std::cout << "Count after = " << point.use_count() << '\n';

	}

	outputFile.close();

	std::cout << "The output file has been generated.";
}


