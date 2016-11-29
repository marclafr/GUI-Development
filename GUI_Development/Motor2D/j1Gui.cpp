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
	p2List_item<Element*>* item;
	item = elements.start;
	j1Module* pModule = NULL;

	iPoint mouse;
	App->input->GetMousePosition(mouse.x, mouse.y);

	for (item = elements.start; item != NULL && ret == true; item = item->next)
	{
		if (mouse.IsInRect(item->data->rect) == true)
		{
			item->data->mouse_inside = true;

			if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT))
			{
				item->data->l_click = true;
				item->data->r_click = false;
			}

			if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT))
			{
				item->data->r_click = true;
				item->data->l_click = false;
			}
		}
		else
		{
			item->data->mouse_inside = false;
			item->data->l_click = false;
			item->data->r_click = false;
		}
		

		ret = item->data->Update(dt);
		ret = item->data->Draw(dt);
		ret = item->data->ManageInput();
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