#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1PathFinding.h"
#include "j1Gui.h"
#include "j1Scene.h"
#include "j1TextBox.h"
#include "j1Fonts.h"
#include "j1Slider.h"

j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	if(App->map->Load("iso_walk.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;
		if(App->map->CreateWalkabilityMap(w, h, &data))
			App->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);
	}

	debug_tex = App->tex->Load("maps/path2.png");

	//SCREEN
	Element* screen = (Element*)App->gui->CreateImage(SDL_Rect{ 0,0,0,0 }, SDL_Rect{ 0,0, 640,480 });
	
	Element* img = (Element*)App->gui->CreateImage(SDL_Rect{ 485, 829, 328, 103 }, SDL_Rect { 800, 100, 328, 103 });
	//Element* txt = (Element*)App->gui->CreateTextBox("Hello world", 12, false, SDL_Rect { 750, 50, 100, 25 });
	Element* window = (Element*)App->gui->CreateImage(SDL_Rect{ 31,542,424,454 }, SDL_Rect{ 300,100,424,454 });
	Element* button = (Element*)App->gui->CreateButton(SDL_Rect{ 647, 173, 225, 61 }, SDL_Rect{ 400, 350, 225, 61 });
	Element* wind_title = (Element*)App->gui->CreateLabel("Window Title", 40, SDL_Rect{ 310, 110, 50, 25 });
	Element* butt_title = (Element*)App->gui->CreateLabel("Button", 40, SDL_Rect{ 410, 360, 50, 25 });
	Element* input_image = (Element*)App->gui->CreateImage(SDL_Rect{ 494, 573, 333, 52 }, SDL_Rect{ 325, 275, 333, 52 });
	Element* input_txt = (Element*)App->gui->CreateTextBox("", App->font->Print("", SDL_Color{ (255),(0),(100),(255) }), 20, false, SDL_Rect{ 325, 300, 333, 52 });
	Element* input_txt2 = (Element*)App->gui->CreateTextBox("ayy", App->font->Print("ayy", SDL_Color{ (255),(0),(100),(255) }), 20, false, SDL_Rect{ 325, 600, 333, 52 });
	Element* slider = (Element*)App->gui->CreateSlider(SDL_Rect{ 1001, 882, 17, 17 }, SDL_Rect{ 100, 100, 17, 17 }, SDL_Rect{ 100,100,17,148 }, SDL_Rect{ 986,874,11,148 }, VERTICAL);
	Element* image_slider = (Element*)App->gui->CreateImage(SDL_Rect{ 485, 829, 328, 503 }, SDL_Rect{ 117, 100, 328, 103 });
																					//103
	screen->parent = nullptr;
	screen->priority = 0;
	screen->AddChild(window);
	//screen->AddChild(txt);
	screen->AddChild(img);
	window->AddChild(button);
	window->AddChild(wind_title);
	button->AddChild(butt_title);
	window->AddChild(input_txt);
	window->AddChild(input_image);
	window->AddChild(input_txt2);
	screen->AddChild(slider);
	screen->AddChild(image_slider);
	j1Slider* slider1 = (j1Slider*)slider;
	slider1->scroll_elements.add(image_slider);

	input_txt2->can_click = true;
	input_txt->can_click = true;
	//txt->can_click = true;
	window->can_drag = true;
	window->can_click = true;
	button->can_drag = true;
	button->can_click = true;
	wind_title->can_drag = true;
	butt_title->can_drag = true;
	slider->can_click = true;
	slider->can_drag = true;

	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{

	// debug pathfing ------------------
	static iPoint origin;
	static bool origin_selected = false;

	int x, y;
	App->input->GetMousePosition(x, y);
	iPoint p = App->render->ScreenToWorld(x, y);
	p = App->map->WorldToMap(p.x, p.y);

	if(App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		if(origin_selected == true)
		{
			App->pathfinding->CreatePath(origin, p);
			origin_selected = false;
		}
		else
		{
			origin = p;
			origin_selected = true;
		}
	}

	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	// Gui ---

	// -------
	if (App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		App->LoadGame("save_game.xml");

	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		App->SaveGame("save_game.xml");

	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		App->render->camera.y += floor(200.0f * dt);

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		App->render->camera.y -= floor(200.0f * dt);

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		App->render->camera.x += floor(200.0f * dt);

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		App->render->camera.x -= floor(200.0f * dt);

	App->map->Draw();

	int x, y;
	App->input->GetMousePosition(x, y);
	iPoint map_coordinates = App->map->WorldToMap(x - App->render->camera.x, y - App->render->camera.y);
	p2SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d Tile:%d,%d",
		App->map->data.width, App->map->data.height,
		App->map->data.tile_width, App->map->data.tile_height,
		App->map->data.tilesets.count(),
		map_coordinates.x, map_coordinates.y);

	//App->win->SetTitle(title.GetString());

	// Debug pathfinding ------------------------------
	//int x, y;
	App->input->GetMousePosition(x, y);
	iPoint p = App->render->ScreenToWorld(x, y);
	p = App->map->WorldToMap(p.x, p.y);
	p = App->map->MapToWorld(p.x, p.y);

	App->render->Blit(debug_tex, p.x, p.y);

	const p2DynArray<iPoint>* path = App->pathfinding->GetLastPath();

	for (uint i = 0; i < path->Count(); ++i)
	{
		iPoint pos = App->map->MapToWorld(path->At(i)->x, path->At(i)->y);
		App->render->Blit(debug_tex, pos.x, pos.y);
	}
	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}
