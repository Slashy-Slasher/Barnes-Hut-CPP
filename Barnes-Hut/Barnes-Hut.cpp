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

	bool stable;



	//Find force with Gravity
	//Find acceleration from force and mass(f/m)
	//Apply (acceleration * dt) * direction{ x, y } to velocity
	//Postion += velocity*dt

	Vector2 force;
	//Vector2 direction; Removing direction because it makes things harder and can just be stored in force
	Vector2 acceleration = {0, 0};
	Vector2 velocity = {0, 0};


	Vector2 position;

	vector<Vector2> area_points;	//Planned Experimental for now

	Planet(float mass, Vector2 position, Vector2 force, float radius, bool stable)	
	{
		this->mass = mass;
		this->position = position;
		this->force = force;
		this->radius = radius;
		this->stable = stable;
	}




	void set_acceleration()
	{
		this->acceleration = { this->force.x / this->mass, this->force.y / this->mass };
	}
	void apply_acceleration(float delta_time)
	{
		cout << this->id << "'s: Delta Time: " << delta_time << endl;
		Vector2 new_velocity = { this->acceleration.x * delta_time, this->acceleration.y * delta_time };
		this->velocity = Vector2Add(this->velocity, new_velocity);
	}
	void update_position(float delta_time)
	{
		set_acceleration();
		apply_acceleration(delta_time);
		Vector2 velocity_dt = { this->velocity.x * delta_time, this->velocity.y * delta_time };
		this->position += velocity_dt;
	}

	void telemetry()
	{
		
		cout << "ID: " << this->id
			<< " Force: (" << this->force.x << ", " << this->force.y << ")"
			<< " Accel: (" << this->acceleration.x << ", " << this->acceleration.y << ")"
			<< " Vel: (" << this->velocity.x << ", " << this->velocity.y << ")" << endl;
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
	//float gravity = 1e-14f;
	float gravity = 1.0f;
	float distance = 0.0f;
	float force_1d = 0.0f;	//Force in 1 dimension
	Vector2 direction;

	for (size_t i = 0; i < planets.size(); i++)
	{
		planets[i].force = { 0, 0 }; // Reset force before summing
		for (size_t g = 0; g < planets.size(); g++)
		{
			if (planets[i].id != planets[g].id)
			{
				planets[i].telemetry();
				//Force = (g*m1*m2)/(r_2)
				distance = Vector2Distance(planets[i].position, planets[g].position);
				cout << planets[i].id << "'s Distance: " << distance << endl;
				direction = Vector2Normalize(Vector2Subtract(planets[g].position, planets[i].position));
				cout << planets[i].id << "'s Direction:" << direction.x << " , " << direction.y << endl;
				std::cout << "Actual Mass: " << planets[i].mass << std::endl;
				force_1d = (gravity * planets[i].mass * planets[g].mass) / (distance * distance);
				cout << planets[i].id << "'s Force:" << direction.x << " , " << direction.y << endl;
				planets[i].force += { direction.x* force_1d, direction.y* force_1d };
				planets[i].telemetry();
			}
		}
	}
	for (size_t i = 0; i < planets.size(); i++)
	{
		if (planets[i].stable == false)
		{
			planets[i].update_position(GetFrameTime());
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
/*
void apply_force(vector<Planet>& planets)
{
	for (size_t i = 0; i < planets.size(); i++)
	{
		planets[i].position += planets[i].force;
	}
}
*/
void print_positions(vector<Planet>& planets)
{
	for (size_t i = 0; i < planets.size(); i++)
	{
		cout << planets[i].id << ": {" << planets[i].position.x << ", " << planets[i].position.y << "}" << endl;
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

	Vector2 planetPos = { screenWidth / 2, screenHeight / 2 };
	Vector2 planetPos2 = { (screenWidth / 2) + 200, screenHeight / 2};


	vector<Planet> region_planets;	//All planets in the region

	region_planets.push_back(Planet(1000000, planetPos, { 0 , 0 }, 30, true));
	region_planets.push_back(Planet(100, planetPos2, { 0 , 1 }, 10, false));


	IDize_vector(region_planets);	//I call this so that no matter how many planets are created that the IDs are assigned correctly

	for (size_t i = 0; i < region_planets.size(); i++)
	{
		cout << "i: " << region_planets[i].id << endl;
	}


	Vector2 test = { 0,0 };
	cout << "Number of planets: " << region_planets.size() << endl;
	Quadtree* testNull = nullptr;

	Quadtree tester(testNull, 0.0f, 0.0f, 100.0f, 100.0f, region_planets, 0, 10);


	//--------------------------------------------------------------------------------------

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);
		DrawText("Created with C++ and Raylib!", screenWidth / 2 - 50, 10, 30, LIGHTGRAY); // Draw 
		DrawFPS(5, 0);

		print_positions(region_planets);
		//region_planets[1].telemetry();

		gravity(region_planets);


		render(region_planets);

		EndDrawing(); // End drawing and swap buffers
	}


	CloseWindow(); // Close window and unload OpenGL context


	return 0;
}


