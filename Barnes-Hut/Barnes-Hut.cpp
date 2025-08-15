// Barnes-Hut.cpp : Defines the entry point for the application.
//

#include "Barnes-Hut.h"
#include <Vector>
#include <raylib.h>
#include <raymath.h>
#include <deque>

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

	Vector2 force = {0, 0};
	//Vector2 direction; Removing direction because it makes things harder and can just be stored in force
	Vector2 acceleration = {0, 0};
	Vector2 velocity = {0, 0};


	Vector2 position;
		
	vector<Vector2> area_points;	//Planned Experimental for now
	deque<Vector2> position_history;


	Planet(float mass, Vector2 position, float radius, bool stable)	
	{
		this->mass = mass;
		this->position = position;


		//this->velocity = Vector2Add(this->velocity, return_velocity_delta_from_force(force, GetFrameTime()));


		//cout << "Starting Velocity: { " << this->velocity.x << ", " << this->velocity.y  << " }" << endl;
		this->radius = radius;
		this->stable = stable;
	}

	Vector2 return_velocity_delta_from_force(Vector2 force, float delta_time)
	{
		Vector2 acceleration = { force.x / this->mass, force.y / this->mass };
		Vector2 new_velocity = { acceleration.x * delta_time, acceleration.y * delta_time };
		return new_velocity;
	}

	void set_acceleration()
	{
		this->acceleration = { this->force.x / this->mass, this->force.y / this->mass };
	}
	void apply_acceleration(float delta_time)
	{
		Vector2 new_velocity = { 0,0 };
		new_velocity = { this->acceleration.x * delta_time, this->acceleration.y * delta_time };
		this->velocity = Vector2Add(this->velocity, new_velocity);
	}
	void update_position(float delta_time)
	{
		set_acceleration();
		apply_acceleration(delta_time);
		//These lines are for adding trails to planets
		this->position_history.push_back(this->position);
		if (this->position_history.size() > 100)
		{
			this->position_history.pop_front();
		}

		
		this->position += this->velocity;
	}
	void set_force(Vector2 force)
	{
		this->force = Vector2Add(this->force, force);
	}
	void apply_impulse(Vector2 impulse) 
	{               
		velocity = Vector2Add(velocity, { impulse.x / mass, impulse.y / mass });
	}
	void telemetry()
	{
		
		cout << "ID: " << this->id
			<< " Force: (" << this->force.x << ", " << this->force.y << ")"
			<< " Accel: (" << this->acceleration.x << ", " << this->acceleration.y << ")"
			<< " Vel: (" << this->velocity.x << ", " << this->velocity.y << ")" << endl;
	}
	//Might remove from this class, but it's convient to have whereever there are planets
	static void IDize_vector(vector<Planet>& planets)
	{
		for (size_t i = 0; i < planets.size(); i++)
		{
			planets[i].id = i;
		}
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

class Render
{
public:
	float width;
	float height;

	float zoom;


	Vector2 offset;
	Vector2 center;

	Render(float width, float height, float zoom, Vector2 offset, Vector2 center)
	{
		this->width = width;
		this->height = height;
		this->zoom = zoom;
		this->offset = offset;
		this->center = center;

	}

	void render(vector<Planet> planets)	//This will render all planets
	{
		for (size_t i = 0; i < planets.size(); i++)
		{
			Vector2 planet_position = world_to_screen(planets[i].position);
			DrawCircle(planet_position.x, planet_position.y, scale_radius(planets[i].radius), RAYWHITE);
		}
	}

	void render_planet_history(vector<Planet> planets)
	{
		for (size_t i = 0; i < planets.size(); i++)
		{
			for (size_t h = 1; h < planets[i].position_history.size(); h++)
			{
				Vector2 position_1 = world_to_screen(planets[i].position_history[h]);
				Vector2 position_2 = world_to_screen(planets[i].position_history[h-1]);
				if (planets[i].position_history.size() > 2)
				{
					DrawLine(position_1.x, position_1.y, position_2.x, position_2.y, LIGHTGRAY);
				}
			}
		}
	}


	void renderUI()
	{

	}

	Vector2 world_to_screen(Vector2 world_coordinates)
	{
		//pygame.Vector2(pygame.Vector2(grouped_tuple) * self.zoom) + self.CURRENT_OFFSET + self.center
		return Vector2Add(Vector2Add(Vector2Multiply(world_coordinates, { zoom, zoom }), offset), center);
	}

	Vector2 screen_to_world(Vector2 screen_coordinates)
	{
		//(pygame.Vector2(grouped_tuple) - self.center - self.CURRENT_OFFSET)/self.zoom
		Vector2 numerator = Vector2Subtract(Vector2Subtract(screen_coordinates, center), offset);
		return { numerator.x / zoom, numerator.y / zoom };
	}
	float scale_radius(float radius)
	{
		return max(1.0f, (radius * zoom));
	}

};

class Input_Handler
{
public:
	bool dragging = false;
	Vector2 screen_last_mouse_pos = {0,0};		//This is for moving the screen
	Vector2 screen_current_mouse_pos = { 0,0 };//This is also for moving the scrren 
	Render& rend;
	vector<Planet>& planet_list;
	


	Input_Handler(Render& rend, vector<Planet>& planet_list) 
		: rend(rend), planet_list(planet_list) {}

	void handle_inputs()
	{
		float wheel = GetMouseWheelMove();
		float zoom_level = 0.1;
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			DrawText("Left mouse button is being held down!", 100, 100, 20, RED);
		}
		if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
		{
			DrawText("Right mouse button is being held down!", 100, 100, 20, RED);
			float min_distance = 400.0f;
			float max_distance = 10000.0f;
			float min_impulse = 200.0f;
			float max_impulse = 800.0f;

			for (size_t i = 0; i < 70; i++)
			{
				Planet new_planet = Planet(100, { (rend.width / 2) + min_distance + max_distance * GetRandomValue(0, 1000) / 1000.0f , rend.height / 2 }, 10, false);
				new_planet.apply_impulse({ 0, min_impulse + max_impulse * GetRandomValue(0, 1000) / 1000.0f });
				planet_list.push_back(new_planet);
			}
			//planet_list[planet_list.size() - 1].apply_impulse({ 0, 300 });

			Planet::IDize_vector(planet_list);


		}
		if (IsKeyDown(KEY_SPACE))
		{

		}
		if (IsKeyPressed(KEY_R))
		{

		}
		if (wheel > 0) {
			rend.zoom += zoom_level;
			rend.zoom = Clamp(rend.zoom, .00001f, 100.0f);
			zoom_level = rend.zoom / 10;
		}
		else if (wheel < 0) {
			rend.zoom -= zoom_level;
			rend.zoom = Clamp(rend.zoom, .00001f, 100.0f);
			zoom_level = rend.zoom / 10;
		}
		// Left mouse button pressed
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			dragging = true;
			screen_last_mouse_pos = GetMousePosition();
		}

		// Left mouse button released
		if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
		{
			dragging = false;
		}

		// Mouse moved while dragging
		if (dragging && IsMouseButtonDown(MOUSE_LEFT_BUTTON))
		{
			Vector2 mouse_pos = GetMousePosition();
			Vector2 movement = Vector2Subtract(mouse_pos, screen_last_mouse_pos);
			Vector2 current_offset = Vector2Add(rend.offset, movement);
			rend.offset = current_offset;
			screen_last_mouse_pos = mouse_pos;
		}
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
		for (size_t g = 0; g < planets.size(); g++)
		{
			if (planets[i].id != planets[g].id)
			{
				//Force = (g*m1*m2)/(r_2)
				distance = Vector2Distance(planets[i].position, planets[g].position);
				direction = Vector2Normalize(Vector2Subtract(planets[g].position, planets[i].position));
				//std::cout << "Actual Mass: " << planets[i].mass << std::endl;
				if (distance != 0)	//Easiest possible guard to prevent NAN propagation
				{
					force_1d = (gravity * planets[i].mass * planets[g].mass) / (distance * distance);
				}
				planets[i].force += { direction.x* force_1d, direction.y* force_1d };
			}
		}
	}
	//Applies all forces to the position_update pipeline, then resets force
	for (size_t i = 0; i < planets.size(); i++)
	{
		if (planets[i].stable == false)
		{
			planets[i].update_position(GetFrameTime());
			planets[i].force = { 0, 0 }; // Reset force
		}
	}
}

/*
Simple method which takes the array reference and apply an ID to each planet
*/

void IDize_vector(vector<Planet>& planets)
{
	for (size_t i = 0; i < planets.size(); i++)
	{
		planets[i].id = i;
	}
}

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
	Vector2 planetPos3 = { (screenWidth / 2) + 300, screenHeight / 2 };

	Render rend = Render(screenWidth, screenHeight,.5f, { 0,0 }, {0,0});
	vector<Planet> region_planets;	//All planets in the region

	region_planets.push_back(Planet(10000000, planetPos, 30, true));
	region_planets.push_back(Planet(100, planetPos2, 10, false));
	region_planets.push_back(Planet(300, planetPos3, 10, false));
	region_planets[1].apply_impulse({0, 1000});
	region_planets[2].apply_impulse({ 0, 1300 });

	


	IDize_vector(region_planets);	//I call this so that no matter how many planets are created that the IDs are assigned correctly

	Input_Handler input = Input_Handler(rend, region_planets);


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

		DrawText(TextFormat("Current Planets: %d", (int)region_planets.size()), 5, 50, 30, LIGHTGRAY); // Draw 

		DrawFPS(5, 0);


		gravity(region_planets);
		//region_planets[1].telemetry();
		//render(region_planets);
		rend.render(region_planets);
		rend.render_planet_history(region_planets);
		input.handle_inputs();


		EndDrawing(); // End drawing and swap buffers
	}


	CloseWindow(); // Close window and unload OpenGL context


	return 0;
}


