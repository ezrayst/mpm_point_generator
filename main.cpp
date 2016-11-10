// The main code to generate points within a rectangle
//
// Done by Ezra Y. S. Tjung <ezrayst@berkeley.edu>
//
// University of California, Berkeley
//

// MPM Point Generator
// Rectangular with input: (x1,y1) coordinates left bottom corner
//                         (x2,y2) coordinates right top corner
//                         (n)     making n-by-n grid
//


#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	double x1;
	double y1;
	double x2;
	double y2;
	int n;
	double hx;          // the distance of every point in x-direction
	double hy;          // the distance of every point in y-direction

	int i;
	int j;

	// Input the left bottom and right top coordinates
	// Users will need to type the coordinate
	// Test: (x1,y1,x2,y2) = (0,0,1,1)
	//                 (n) = (3)

	cout << "Enter left bottom corner coordinate (x1): \n";
	cin >> x1;

	cout << "Enter left bottom corner coordinate (y1): \n";
	cin >> y1;

	cout << "Enter right top corner coordinate (x2): \n";
	cin >> x2;

	cout << "Enter right top corner coordinate (y2): \n";
	cin >> y2;

	cout << "Enter the number of grid points on an edge (n): \n";
	cin >> n;

	// Get hx and hy
	hx = (x2 - x1) / (n - 1);
	hy = (y2 - y1) / (n - 1);


	// Generate points
	// Naming goes from 0 to n^2, started at bottom left to the right and then up
	// points: [Node#   x-coor   y-coor]
	// The points will be saved to a .txt file

	std::ofstream filename("mpm_points.txt");

	double points[n*n][3];          // the distance of every point in y-direction

	for (i=0; i < n; ++i)			// i is respect to y
		for (j=0; j < n; ++j)		// j is respect to x
		{
			points[i*n + j][1] = i*n + j + 1;
			points[i*n + j][2] = x1 + j*hx;
			points[i*n + j][3] = y1 + i*hy;

			filename << points[i*n + j][1] << " " << points[i*n + j][2] << " " << points[i*n + j][3] << "\n";
		}

	return 0;
}

