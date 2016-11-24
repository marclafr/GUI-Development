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
		//DeleteElement(elements[i]->id);

	elements.clear();

	return true;
}

// const getter for atlas
SDL_Texture* j1Gui::GetAtlas() const
{
	return atlas;
}

// class Gui ---------------------------------------------------

Element* j1Gui::CreateElement(elem_type type, SDL_Rect rect)
{
	static_assert(elem_type::unknown == 6, "elements type needs update");

	Element* ret = nullptr;

	switch (type)
	{
	case elem_type::label: break;
	case elem_type::text_box: ret = new j1TextBox("Hello world", 12, false, element_id); break;
	case elem_type::image: ret = new j1Image(rect, element_id); break;
	case elem_type::anim_image: break;
	case elem_type::button: break;
	case elem_type::input: break;
	}

	if (ret != nullptr)
		elements.add(ret); element_id++;

	return ret;
}

bool j1Gui::DeleteElement(int id)
{
	/*for (int i = 0; i < elements.count(); i++)
	{
		if (elements[i]->id == id)
		{
			RELEASE(elements[i]);
			delete elements[i];
		}
	}*/
	return true;
}
