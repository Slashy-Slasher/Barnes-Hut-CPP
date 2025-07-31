// Barnes-Hut.cpp : Defines the entry point for the application.
//

#include "Barnes-Hut.h"
#include <raylib>
#include <iomanip>
#include <cmath>
#include <random>

using namespace std;

class Quadtree
{
	float x;			//Top x_left corner of the area
	float y;			//Top y_left corner of the area
	float w;			//Bottom x_right corner of the area
	float h;			//Bottom y_right corner of the area
	float width;		//Width of the box

	int max;			//Max depth
	int depth;			//Current Depth

	Quadtree* parent;;  //Points backwards to the parent
	Quadtree* tlc;		//Pointer to the top left corner
	Quadtree* trc;		//Pointer to the top right corner
	Quadtree* blc;		//Pointer to the bottom left corner
	Quadtree* brc;		//Pointer to the bottom right corner
	bool isRoot;

	Quadtree()
	{

	}
	subdivide()
	{

	}


};

int main()
{
	cout << "Hello CMake." << endl;
	return 0;
}


