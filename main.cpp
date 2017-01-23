// MPM Point Generator
//
// The main code to generate points within a rectangle
// Rectangular with input: (x1,y1) coordinates left bottom corner
//                         (x2,y2) coordinates right top corner
//                         (m)     making n grid in x-direction
//						   (n)     making m grid in y-direction
//
//
// Input the left bottom and right top coordinates
// Users will need to type the coordinate
// Test: (x1,y1,x2,y2) = (0,0,1,1)
//                 (m) = (3)
//                 (n) = (3)
// Generate points
// points: [Node#   x-coor   y-coor]
// The points will be saved to a .txt file

#include <iostream>
#include <fstream>
#include <vector>

int main()
{
	double x1, y1;
	double x2, y2;
	int i, j, k, num_points_x, num_points_y, num_points;
	double x_spacing, y_spacing;

	std::cout << "Enter left bottom corner coordinate (x1): \n";
	std::cin >> x1;

	std::cout << "Enter left bottom corner coordinate (y1): \n";
	std::cin >> y1;

	std::cout << "Enter right top corner coordinate (x2): \n";
	std::cin >> x2;

	std::cout << "Enter right top corner coordinate (y2): \n";
	std::cin >> y2;

	std::cout << "Enter the number of grid points in x direction (m): \n";
	std::cin >> num_points_x;

	std::cout << "Enter the number of grid points in y direction (n): \n";
	std::cin >> num_points_y;

	x_spacing = (x2 - x1) / (num_points_x - 1);
	y_spacing = (y2 - y1) / (num_points_y - 1);
	num_points = num_points_x*num_points_y;

	std::vector<double> xarr(num_points);
	std::vector<double> yarr(num_points);

	for (i=0; i < num_points_y; ++i)			// i is respect to y
		for (j=0; j < num_points_x; ++j)		// j is respect to x
		{
			k = i*num_points_y + j;
			xarr[k] = x1 + j*x_spacing;
			yarr[k] = y1 + i*y_spacing;
		}

	std::ofstream mpm_points("mpm_points.txt");
	for (i=0; i < num_points_y; ++i)			// i is respect to y
		for (j=0; j < num_points_x; ++j)		// j is respect to x
		{
			k = i*num_points_y + j;
			mpm_points << xarr[k] << "," << yarr[k] << "\n";
		}
	mpm_points.close();

	std::cout << "The file has been generated.";
}


