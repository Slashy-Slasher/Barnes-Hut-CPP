// Barnes-Hut.cpp : Defines the entry point for the application.
//

#include "Barnes-Hut.h"
#include <Vector>
#include <raylib.h>
#include <raymath.h>


using namespace std;


class Planet
{
public:
	float mass;
	float radius;
	float color;
	float id;
	

	Vector2 direction;
	Vector2 force;
	Vector2 position;

	vector<Vector2> area_points;	//Planned Experimental for now

	Planet(float mass, Vector2 position, float radius)
	{
		this->mass = mass;
		this->position = position;
		this->radius = radius;
	}
	/*
	void apply_force()
	{

	}
	*/
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


/*
Renders every planet in the Universe
*/

void render(vector<Planet> planets)	//This will render all planets
{
	for (size_t i = 0; i < planets.size(); i++)
	{
		DrawCircle(planets[i].position.x, planets[i].position.y, planets[i].radius, RAYWHITE);
	}
}



/*
Method which applies N^2 Newtonian Gravity
- This method of applying force should only be applied when the planets are very close(Most accurate)
*/

void gravity(vector<Planet>& planets)
{
	float g = 0.01;
	float distance = 0.0f;
	float force = 0.0f;
	Vector2 dir = { 0, 0 };
	
	for (size_t i = 0; i < planets.size(); i++)
	{
		for (size_t g = 0; g < planets.size(); g++)
		{
			if (planets[i].id != planets[g].id)
			{
				//Force = (g*m1*m2)/(r_2)
				distance = Vector2Distance(planets[i].position, planets[g].position);
				force = (g * planets[i].mass * planets[g].mass) / (distance * distance);
				planets[i].direction = Vector2Normalize(Vector2Subtract(planets[g].position, planets[i].position));
				planets[i].force += { planets[i].direction.x * force, planets[i].direction.y * force };
			}
		}
	}
}

/*
Simple method which will take the array reference and apply an ID to each planet
*/

void IDize_vector(vector<Planet>& planets)
{
	for (size_t i = 0; i < planets.size(); i++)
	{
		planets[i].id = i;
	}
}


int main()
{
	// Initialization
   //--------------------------------------------------------------------------------------
	const int screenWidth = 800;
	const int screenHeight = 800;

	InitWindow(screenWidth, screenHeight, "Barnes-Hut-Simulation"); // Initialize window with dimensions and title

	SetTargetFPS(60); // Set desired framerate (frames-per-second)

	Vector2 planetPos = {screenWidth/2, screenHeight/2};
	Vector2 planetPos2 = { (screenWidth / 2) + 200, screenHeight / 2 };


	vector<Planet> region_planets;	//All planets in the region

	region_planets.push_back(Planet(100, planetPos, 30));
	region_planets.push_back(Planet(100, planetPos2, 10));
	IDize_vector(region_planets);	//I call this so that no matter how many planets are created that the IDs are assigned correctly
	
	for (size_t i = 0; i < region_planets.size(); i++)
	{
		cout << "i: " << region_planets[i].id << endl;
	}


	Vector2 test = { 0,0 };
	cout << "Hello CMake." << endl;
	cout << "Hello CMake. " << test.x<<endl;
	cout << region_planets.size();
	Quadtree* testNull = nullptr;

	Quadtree tester(testNull, 0.0f, 0.0f, 100.0f, 100.0f, region_planets, 0, 10);


	//--------------------------------------------------------------------------------------

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);
		DrawText("Created with C++ and Raylib!", screenWidth / 2 - 50, 10, 30, LIGHTGRAY); // Draw 
		DrawFPS(5, 0);
		render(region_planets);

		EndDrawing(); // End drawing and swap buffers
	}


	CloseWindow(); // Close window and unload OpenGL context


	return 0;
}


