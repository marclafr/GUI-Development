#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"
#include "j1Image.h"
#include "j1TextBox.h"
#include "j1Label.h"
#include "j1AnimatedImage.h"
#include "j1Button.h"

j1Gui::j1Gui() : j1Module()
{
	name.create("gui");
}

// Destructor
j1Gui::~j1Gui()
{}

// Called before render is available
bool j1Gui::Awake(pugi::xml_node& conf)
{
	LOG("Loading GUI atlas");
	bool ret = true;

	atlas_file_name = conf.child("atlas").attribute("file").as_string("");

	return ret;
}

// Called before the first frame
bool j1Gui::Start()
{
	atlas = App->tex->Load(atlas_file_name.GetString());

	return true;
}

// Update all guis
bool j1Gui::PreUpdate()
{
	return true;
}

bool j1Gui::Update(float dt)
{
	bool ret = true;

	iPoint mouse;
	App->input->GetMousePosition(mouse.x, mouse.y);
		
	Element* screen = elements.start->data;
	int j = screen->sons.count();
	p2List_item<Element*>* item = screen->sons.start;
	
	for (p2List_item<Element*>* a = elements.start; a; a = a->next)
	{
		if (mouse.IsInRect(a->data->position) == true)
		{
			a->data->mouse_inside = true;

			if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
				a->data->l_click = true;

			if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_REPEAT)
				a->data->r_click = true;

			if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_UP)
				a->data->l_click = false;

			if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_UP)
				a->data->r_click = false;
		}
		else
		{
			a->data->mouse_inside = false;
			a->data->l_click = false;
			a->data->r_click = false;
		}
	}
	
	for (int i = 0; screen->sons.count() > i; i++, item = item->next)
	{
		ret = item->data->Update(dt, item->data);
		ret = item->data->Draw(dt, item->data);
	}

	return ret;
}

// Called after all Updates
bool j1Gui::PostUpdate()
{
	return true;
}

// Called before quitting
bool j1Gui::CleanUp()
{
	LOG("Freeing GUI");

	for (int i = 0; i < elements.count(); i++)
		delete elements[i];

	elements.clear();

	return true;
}

// const getter for atlas
SDL_Texture* j1Gui::GetAtlas() const
{
	return atlas;
}

// class Gui ---------------------------------------------------

j1Label * j1Gui::CreateLabel(const p2SString& text, int size, SDL_Rect& rect)
{
	static_assert(elem_type::unknown == UNKNOWN_NUM, "elements type needs update");
	j1Label* ret = new j1Label(text, size, rect, element_id);
	if (ret != nullptr)
		elements.add(ret); element_id++;

	return ret;
}

j1TextBox * j1Gui::CreateTextBox(const p2SString& text, int size, bool is_pw, SDL_Rect& rect)
{
	static_assert(elem_type::unknown == UNKNOWN_NUM, "elements type needs update");
	j1TextBox* ret = new j1TextBox(text, size, false, rect, element_id);
	if (ret != nullptr)
		elements.add(ret); element_id++;

	return ret;
}

j1Image * j1Gui::CreateImage(SDL_Rect& section, SDL_Rect& rect)
{
	static_assert(elem_type::unknown == UNKNOWN_NUM, "elements type needs update");
	j1Image* ret = new j1Image(image, section, rect, element_id);
	if (ret != nullptr)
		elements.add(ret); element_id++;

	return ret;
}

j1AnimatedImage * j1Gui::CreateAnimImage(SDL_Rect& section, SDL_Rect& rect)
{
	static_assert(elem_type::unknown == UNKNOWN_NUM, "elements type needs update");
	j1AnimatedImage* ret = new j1AnimatedImage(section, rect, element_id);
	if (ret != nullptr)
		elements.add(ret); element_id++;

	return ret;
}

j1Button * j1Gui::CreateButton(SDL_Rect& section, SDL_Rect& rect)
{
	static_assert(elem_type::unknown == UNKNOWN_NUM, "elements type needs update");
	j1Button* ret = new j1Button(section, rect, element_id);
	if (ret != nullptr)
		elements.add(ret); element_id++;

	return ret;
}

bool j1Gui::DeleteElement(int id)
{
	p2List_item<Element*>* item = elements.start;
	for (; item; item = item->next)
	{
		if (item->data->id == id)
		{
			delete item;
			elements.del(item);
		}
	}
	return true;
}

// struct Element ---------------------------------------------------

void Element::SetPosition(SDL_Rect& rect)
{
	position = rect;
}