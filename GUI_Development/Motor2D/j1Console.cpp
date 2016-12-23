#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Console.h"

j1Console::j1Console() : j1Module()
{
	name.create("console");
}

// Destructor
j1Console::~j1Console()
{}

// Called before render is available
bool j1Console::Awake(pugi::xml_node& conf)
{
	LOG("Loading console");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Console::Start()
{

	return true;
}

// Update all guis
bool j1Console::PreUpdate()
{
	return true;
}

bool j1Console::Update(float dt)
{
	bool ret = true;

	return ret;
}

// Called after all Updates
bool j1Console::PostUpdate()
{
	return true;
}

// Called before quitting
bool j1Console::CleanUp()
{
	LOG("Freeing console");

	return true;
}