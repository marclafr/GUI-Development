#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Render.h"
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
bool j1Scene::Awake(pugi::xml_node& conf)
{
	LOG("Loading Scene");
	bool ret = true;

	///SCREEN
	screen = App->gui->screen;

	for (pugi::xml_node labels = conf.child("label"); labels; labels = labels.next_sibling("label"))
	{
		Element* label = (Element*)App->gui->CreateLabel(labels.attribute("text").as_string(), 50, { labels.attribute("position_x").as_int(), labels.attribute("position_y").as_int(), 200, 75 });
		if (labels.attribute("draggable").as_bool() == true)
		{
			label->can_click = true;
			label->can_drag = true;
		}
		screen->AddChild(label);
	}

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{

	/*//LOL UI
	Element* background = (Element*)App->gui->CreateImage({ 0, 1600, 1024, 576 }, { 0,0, 1024, 576 }, false);
	screen->AddChild(background);
	Element* window = (Element*)App->gui->CreateImage({ 0, 512, 483, 512 }, { 285,25,483,512 }, false);
	screen->AddChild(window);
	Element* button = (Element*)App->gui->CreateButton({ 645, 165, 229, 69 }, { 415, 425, 225, 61 }, false);
	window->AddChild(button);
	button->can_click = true;
	Element* wind_title = (Element*)App->gui->CreateLabel("Select Your Character", 22, { 415, 75, 225, 61 });
	window->AddChild(wind_title);
	Element* butt_title = (Element*)App->gui->CreateLabel("Continue", 15, { 485, 445, 225, 61 });
	button->AddChild(butt_title);
	Element* heroes_1 = (Element*)App->gui->CreateImage({ 0, 1024, 1025, 287 }, { heroes1_x_pos_min, heroes_y_pos, 2050, 287 }, false);
	window->AddChild(heroes_1);
	heroes_1->can_click = true;
	heroes_1->can_drag = true;
	Element* heroes_2 = (Element*)App->gui->CreateImage({ 0, 1311, 1025, 287 }, { heroes2_x_pos_min, heroes_y_pos, 1025, 287 }, false);
	heroes_1->AddChild(heroes_2);
	heroes1 = (j1Image*)heroes_1;
	heroes1->CreateViewport({ 415, heroes_y_pos, 205, 287 });
	heroes2 = (j1Image*)heroes_2;
	heroes2->CreateViewport({ 415, heroes_y_pos, 205, 287 });
	*/


	/*
	//EXERCISE 1
	Element* background = (Element*)App->gui->CreateImage({ 970, 1844, 768, 579 }, { 0, 0, 768, 579 }, false);
	screen->AddChild(background);
	//--

	//EXERCISE 2
	blue_sel_box = App->gui->CreateImage({ 1485, 110, 72, 109 }, { 240, 80, 288, 191 }, true);
	screen->AddChild(blue_sel_box);
	blue_sel_box->is_interactive = true;
	blue_sel_box->tab_focus = true;
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
	*/
	
	/*
	Element* img = (Element*)App->gui->CreateImage({ 485, 829, 328, 103 },  { 800, 100, 328, 103 },false);
	Element* window = (Element*)App->gui->CreateImage({ 31,542,424,454 }, { 300,100,424,454 },false);
	Element* button = (Element*)App->gui->CreateButton({ 647, 173, 225, 61 }, { 400, 350, 225, 61 },false);
	Element* wind_title = (Element*)App->gui->CreateLabel("Window Title", 40, { 310, 110, 50, 25 });
	Element* butt_title = (Element*)App->gui->CreateLabel("Button", 40, { 410, 360, 50, 25 });
	Element* input_image = (Element*)App->gui->CreateImage({ 494, 573, 333, 52 }, { 325, 275, 333, 52 }, false);
	Element* input_txt = (Element*)App->gui->CreateTextBox("", App->font->Print("", { (255),(0),(100),(255) }), 20, false, { 325, 300, 333, 52 },false);
	Element* input_txt2 = (Element*)App->gui->CreateTextBox("ayy", App->font->Print("ayy", { (255),(0),(100),(255) }), 20, false, { 325, 600, 333, 52 }, false);
	Element* slider = (Element*)App->gui->CreateSlider({ 1001, 882, 17, 17 }, { 100, 100, 17, 17 }, { 100,100,17,148 }, { 986,874,11,148 }, VERTICAL, 328);
	Element* image_slider = (Element*)App->gui->CreateImage({ 485, 829, 328, 103 }, { 17, 0, 328, 103 }, false);
	Element* image_slider2 = (Element*)App->gui->CreateImage({ 485, 829, 328, 103 }, { 17, 103, 328, 103 }, false);
	Element* image_slider3 = (Element*)App->gui->CreateImage({ 485, 829, 328, 103 }, { 17, 206, 328, 103 }, false);
	Element* image_slider4 = (Element*)App->gui->CreateImage({ 485, 829, 328, 103 }, { 17, 309, 328, 103 }, false);
	Element* image_slider5 = (Element*)App->gui->CreateImage({ 485, 829, 328, 103 }, { 17, 412, 328, 103 }, false);
	Element* image_slider6 = (Element*)App->gui->CreateImage({ 485, 829, 328, 103 }, { 17, 515, 328, 103 }, false);
	
	screen->AddChild(window);
	screen->AddChild(img);
	window->AddChild(button);
	window->AddChild(wind_title);
	button->AddChild(butt_title);
	window->AddChild(input_txt);
	window->AddChild(input_image);
	window->AddChild(input_txt2);
	window->AddChild(slider);

	j1Slider* slider1 = (j1Slider*)slider;
	slider1->AddScrollElement(image_slider);
	slider1->AddScrollElement(image_slider2);
	slider1->AddScrollElement(image_slider3);
	slider1->AddScrollElement(image_slider4);
	slider1->AddScrollElement(image_slider5);
	slider1->AddScrollElement(image_slider6);

	input_txt2->can_click = true;
	input_txt->can_click = true;
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
	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{

	if (App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		App->LoadGame("save_file.xml");

	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		App->SaveGame("save_file.xml");

	/*
	//LOL UI
	if (heroes1->position.y != heroes_y_pos)
		heroes1->position.y = heroes_y_pos;

	if (heroes1->position.x <= heroes1_x_pos_min - heroes1_x_pos_max)
	{
		heroes1->position.x = heroes1_x_pos_min - heroes1_x_pos_max;
		heroes2->position.x = heroes2_x_pos_min - heroes1_x_pos_max;
	}
	if (heroes1->position.x >= heroes1_x_pos_min + 1)
	{
		heroes1->position.x = heroes1_x_pos_min;
		heroes2->position.x = heroes2_x_pos_min;
	}

	if (heroes2->position.y != heroes_y_pos)
		heroes2->position.y = heroes_y_pos;
	*/


	//EXERCISE 2 && 3
	/*if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
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
	}*/

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


bool j1Scene::Load(pugi::xml_node& node)
{
	for (pugi::xml_node labels = node.child("label"); labels; labels = labels.next_sibling("label"))
	{
		Element* label = (Element*)App->gui->CreateLabel(labels.attribute("text").as_string(), 50, { labels.attribute("position_x").as_int(), labels.attribute("position_y").as_int(), 200, 75 });
		if (labels.attribute("draggable").as_bool() == true)
		{
			label->can_click = true;
			label->can_drag = true;
		}
		screen->AddChild(label);
	}
	return true;
}

bool j1Scene::Save(pugi::xml_node& node) const
{
	node.append_child("label");
	for (p2List_item<Element*>* item = App->gui->elements.start; item; item = item->next)
	{
		if (item->data->can_drag == true)
		{

		}
	}
	return true;
}