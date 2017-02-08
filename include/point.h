#include<array>

class mat_points
{
public:
	//! Make a constructor
	mat_points(int id, std::array<double, 2> coords)
	{
		id_ = id;
		coords_ = coords;
	}

	//! Get the private properties using two functions
	//! To get the id_ and coords_
	int const id()
	{
		return id_;
	}
	std::array<double, 2> const coords()
	{
		return coords_;
	}

private:
	int id_;
	std::array<double, 2> coords_;
};
