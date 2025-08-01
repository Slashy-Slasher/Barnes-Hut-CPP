// Barnes-Hut.cpp : Defines the entry point for the application.
//

#include "Barnes-Hut.h"
#include <raylib>
#include <iomanip>
#include <cmath>
#include <random>

using namespace std;


class Planet
{

};

class Quadtree
{
	float x;			//Top x_left corner of the area
	float y;			//Top y_left corner of the area
	float w;			//Bottom x_right corner of the area
	float h;			//Bottom y_right corner of the area
	float width;		//Width of the box

	int max;			//Max depth
	int depth;			//Current Depth

	Quadtree* parent;  //Points backwards to the parent
	Quadtree* tlc;		//Pointer to the top left corner
	Quadtree* trc;		//Pointer to the top right corner
	Quadtree* blc;		//Pointer to the bottom left corner
	Quadtree* brc;		//Pointer to the bottom right corner

	bool isRoot;

	vector<Planet> region_planets;	//All planets in the region
	float combined_planet_mass;



	float calculate_region_mass()
	{
		return 0; //Returns the entire region's mass
	}

	void check_root()
	{
		if (parent == is_null_pointer)
		{
			isRoot = true;
		}
	}

	void subdivide()
	{

	}

	Quadtree(Quadtree* parent, float x, float y, float w, float h, vector<Planet> planet_list, int depth, int max)	//Generates a quadtree and returns a pointer
	{
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
		this->parent = parent;
		this->region_planets = planet_list;
		this->depth = depth;
		this->max = max;
		check_root();	//Determines if the Quadtree has a parent node and configures the bool accordingly
		this->combined_planet_mass = calculate_region_mass();
	}

};

int main()
{
	cout << "Hello CMake." << endl;
	return 0;
}


