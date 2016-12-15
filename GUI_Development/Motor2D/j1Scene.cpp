#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Gui.h"
#include "j1Scene.h"
#include "j1TextBox.h"
#include "j1Fonts.h"
#include "j1Slider.h"
#include "j1Image.h"

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
	/*if(App->map->Load("iso_walk.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;
		if(App->map->CreateWalkabilityMap(w, h, &data))
			App->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);
	}

	debug_tex = App->tex->Load("maps/path2.png");
*/

	///SCREEN
	Element* screen = (Element*)App->gui->CreateImage({ 0,0,0,0 }, { 0,0, 768, 579 }, false);
	screen->parent = nullptr;
	screen->priority = 0;

	//EXERCISE 1
	Element* background = (Element*)App->gui->CreateImage({ 970, 1844, 768, 579 }, { 0, 0, 768, 579 }, false);
	screen->AddChild(background);
	//--

	//EXERCISE 2
	blue_sel_box = App->gui->CreateImage({ 1485, 110, 72, 109 }, { 240, 80, 288, 191 }, true);
	screen->AddChild(blue_sel_box);
	blue_sel_box->is_interactive = true;
	//--

	//EXERCISE 3
	player1_char = App->gui->CreateImage({ 925, 605, 168, 279 }, { 24, 61, 168, 279 }, false);
	blue_sel_box->AddChild(player1_char);
	//--

	//EXERCISE 4
	red_sel_box = App->gui->CreateImage({ 1560, 110, 72, 109 }, { 312, 80, 288, 191 }, true);
	screen->AddChild(red_sel_box);
	red_sel_box->is_interactive = true;
	player2_char = App->gui->CreateImage({ 1093, 605, 168, 279 }, { 543, 61, 168, 279 }, false);
	red_sel_box->AddChild(player2_char);
	//--

	/*
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
	*/

	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	/*
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
	}*/

	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	//EXERCISE 2 && 3
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
	{
		if (blue_sel_box->tab_focus == true && blue_sel_box->position.x < 456)
		{
			blue_sel_box->position.x += 72;
			player1_char->section.x += 168;
		}
		else if (red_sel_box->tab_focus == true && red_sel_box->position.x < 456)
		{
			red_sel_box->position.x += 72;
			player2_char->section.x += 168;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
	{
		if (blue_sel_box->tab_focus == true && blue_sel_box->position.x > 240)
		{
			blue_sel_box->position.x -= 72;
			player1_char->section.x -= 168;
		}
		else if (red_sel_box->tab_focus == true && red_sel_box->position.x > 240)
		{
			red_sel_box->position.x -= 72;
			player2_char->section.x -= 168;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_UP))
	{
		if (blue_sel_box->tab_focus == true && blue_sel_box->position.y > 80)
		{
			blue_sel_box->position.y -= 95;
			player1_char->section.y -= 279;
		}
		else if (red_sel_box->tab_focus == true && red_sel_box->position.y > 80)
		{
			red_sel_box->position.y -= 95;
			player2_char->section.y -= 279;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN)
	{
		if (blue_sel_box->tab_focus == true && blue_sel_box->position.y < 175)
		{
			blue_sel_box->position.y += 95;
			player1_char->section.y += 279;
		}
		else if (red_sel_box->tab_focus == true && red_sel_box->position.y < 175)
		{
			red_sel_box->position.y += 95;
			player2_char->section.y += 279;
		}
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
