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
#include <array>
#include <vector>

using namespace std;

int main()
{
	double x1, y1;
	double x2, y2;
	int i, j, k, n, m, p;
	double hx;          // the distance of every point in x-direction
	double hy;          // the distance of every point in y-direction

	cout << "Enter left bottom corner coordinate (x1): \n";
	cin >> x1;

	cout << "Enter left bottom corner coordinate (y1): \n";
	cin >> y1;

	cout << "Enter right top corner coordinate (x2): \n";
	cin >> x2;

	cout << "Enter right top corner coordinate (y2): \n";
	cin >> y2;

	cout << "Enter the number of grid points in x direction (m): \n";
	cin >> m;

	cout << "Enter the number of grid points in y direction (n): \n";
	cin >> n;

	hx = (x2 - x1) / (m - 1);
	hy = (y2 - y1) / (n - 1);
	p = m*n;

	std::vector<double> xarr(p);
	std::vector<double> yarr(p);

	for (i=0; i < n; ++i)			// i is respect to y
		for (j=0; j < m; ++j)		// j is respect to x
		{
			k = i*n + j;
			xarr[k] = x1 + j*hx;
			yarr[k] = y1 + i*hy;
		}

	std::ofstream mpm_points("mpm_points.txt");
	for (i=0; i < n; ++i)			// i is respect to y
		for (j=0; j < m; ++j)		// j is respect to x
		{
			k = i*n + j;
			mpm_points << xarr[k] << "," << yarr[k] << "\n";
		}
	mpm_points.close();

	cout << "The file has been generated.";
}


