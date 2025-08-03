// Barnes-Hut.cpp : Defines the entry point for the application.
//

#include "Barnes-Hut.h"
#include <Vector>
#include <raylib.h>


using namespace std;


class Planet
{
public:
	float mass;
	float center;
	vector<Vector2> area_points;



	Planet()
	{
		
	}
};

class Quadtree
{
public:
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
	float combined_planet_mass;		//Mass of the region
	vector<float> mass_center;		//Center of Mass 


	float calculate_region_mass()
	{
		return 0; //Returns the entire region's mass
	}

	void check_root()
	{
		if (parent == nullptr)
		{
			isRoot = true;
		}
	}

	vector<Planet> points_in_region(float x, float y, float w, float h, vector<Planet> region_planets)
	{
		//Take a list of all planets within the tree
		//Return the a list off all planets within the sector
		for (size_t i = 0; i < region_planets.size(); i++)
		{

		}

	}

	void subdivide()
	{
		++depth;

		if (region_planets.size() > max && depth < 100)
		{

		}

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

		this->width = abs(x - w);
		this->combined_planet_mass = calculate_region_mass();
	}

};

int main()
{
	// Initialization
   //--------------------------------------------------------------------------------------
	const int screenWidth = 800;
	const int screenHeight = 800;

	InitWindow(screenWidth, screenHeight, "Barnes-Hut-Simulation"); // Initialize window with dimensions and title

	SetTargetFPS(60); // Set desired framerate (frames-per-second)



	//--------------------------------------------------------------------------------------


	vector<Planet> region_planets;	//All planets in the region
	region_planets.push_back(Planet());
	Vector2 test = { 0,0 };
	cout << "Hello CMake." << endl;
	cout << "Hello CMake. " << test.x<<endl;

	Quadtree* testNull = nullptr;

	Quadtree tester(testNull, 0.0f, 0.0f, 100.0f, 100.0f, region_planets, 0, 10);
	
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawText("Created with C++ and Raylib!", screenWidth / 2 - 50, 10, 30, LIGHTGRAY); // Draw 

		DrawFPS(5, 0);

		EndDrawing(); // End drawing and swap buffers
	}


	CloseWindow(); // Close window and unload OpenGL context


	return 0;
}


