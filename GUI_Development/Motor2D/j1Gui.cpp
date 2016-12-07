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
	
	for (int i = MAX_PRIORITY; i > 0; i--)
	{
		for (p2List_item<Element*>* all = elements.start; all; all = all->next)
		{
			if (all->data->priority == i)
			{
				if (all->data->can_click == true && some_is_clicked == false)
				{
					if (mouse.IsInRect(all->data->position) == true)
					{
						all->data->mouse_inside = true;

						if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
						{
							all->data->l_click = true;
							some_is_clicked = true;
						}
						if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_REPEAT)
						{
							all->data->r_click = true;
							some_is_clicked = true;
						}
					}
					else
						all->data->mouse_inside = false;
				}

				if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_UP || App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_UP)
				{
					all->data->l_click = false;
					all->data->mouse_inside = false;
					all->data->r_click = false;
					some_is_clicked = false;
				}

				if (all->data->e_type == text_box)
				{
					if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN && all->data->mouse_inside == true)
					{
						for (p2List_item<Element*>* other_texts = elements.start; other_texts; other_texts = other_texts->next)
						{
							if (other_texts->data->e_type == text_box)
							{
								j1TextBox* other = (j1TextBox*)other_texts->data;
								other->text_clicked = false;
							}
						}
						j1TextBox* text = (j1TextBox*)all->data;
						text->text_clicked = true;						
					}
				}
				if (App->input->GetKey(SDL_SCANCODE_BACKSPACE) == KEY_DOWN && all->data->e_type == text_box)
				{
					j1TextBox* text = (j1TextBox*)all->data;
					if (text->text_clicked == true)
					{
						text->text.text.Cut(text->text.text.Length() - 1, text->text.text.Length() + 1);
						text->text_texture = App->font->Print(text->text.text.GetString(), SDL_Color{ (255),(0),(100),(255) });
					}
				}

			}
		}
	}
	
	p2List_item<Element*>* item = screen->childs.start;
	for (int i = 0; screen->childs.count() > i; i++, item = item->next)
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

	DeleteElements();

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

j1TextBox * j1Gui::CreateTextBox(const p2SString& text, SDL_Texture* tex, int size, bool is_pw, SDL_Rect& rect)
{
	static_assert(elem_type::unknown == UNKNOWN_NUM, "elements type needs update");
	j1TextBox* ret = new j1TextBox(text, *tex, size,  false, rect, element_id);
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

bool j1Gui::DeleteElements()
{
	for (int i = 0; i < elements.count(); i++)
		delete elements[i];

	elements.clear();
	return true;
}

// struct Element ---------------------------------------------------

void Element::SetPosition(SDL_Rect& rect)
{
	position = rect;
}

void Element::AddChild(Element* child)
{
	childs.add(child);
	child->parent = this;
	child->priority = priority + 1;
}

void Element::DragElement()
{
	iPoint mouse_motion;
	App->input->GetMouseMotion(mouse_motion.x, mouse_motion.y);
	position.x += mouse_motion.x;
	position.y += mouse_motion.y;
	for (p2List_item<Element*>* childs_item = childs.start; childs_item; childs_item = childs_item->next)
		childs_item->data->DragElement();	
}