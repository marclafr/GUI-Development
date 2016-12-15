#include "j1Slider.h"
#include "j1Render.h"
#include "j1App.h"
#include "j1Fonts.h"
#include "j1Input.h"

j1Slider::j1Slider(const SDL_Rect sect, SDL_Rect rect, SDL_Rect back_rect, SDL_Rect back_section, SliderType s_type, int id) : section(sect), slider_type(s_type), back_rect(back_rect), back_section(back_section), Min_slider{ rect.x, rect.y }, Element(elem_type::button, rect, 0, id)
{
	if (s_type == VERTICAL)
		Max_slider = { rect.x, rect.y + back_rect.h };
	else if (s_type == VERTICAL)
		Max_slider = { rect.x + back_rect.w, rect.y };
}

j1Slider::~j1Slider()
{
}

bool j1Slider::Update(float dt, Element* item)
{
	p2List_item<Element*>* childs_item;
	for (childs_item = item->childs.start; childs_item; childs_item = childs_item->next)
		childs_item->data->Update(dt, childs_item->data);
	

	j1Slider* slider = (j1Slider*)item;
	if (item->l_click == true && slider->slider_type == VERTICAL)
	{
		DragVerticalSlider();
		for (p2List_item<Element*>* scroll_item = slider->scroll_elements.start; scroll_item; scroll_item = scroll_item->next)
		{
			if(slider->Max_reached==false && slider->Min_reached==false)
				scroll_item->data->DragElementAxisY();
		}
	}

	if (item->l_click == true && slider->slider_type == HORITZONTAL)
	{
		DragHoritzontalSlider();
	
	}

	return true;
}

bool j1Slider::Draw(float dt, Element* item)
{
	j1Slider* slider = (j1Slider*)item;
	App->render->Blit(App->gui->GetAtlas(), item->position.x - App->render->camera.x, item->position.y - App->render->camera.y, &slider->section);
	App->render->Blit(App->gui->GetAtlas(), slider->back_rect.x - App->render->camera.x, slider->back_rect.y - App->render->camera.y, &slider->back_section);
	for (p2List_item<Element*>* childs_item = item->childs.start; childs_item; childs_item = childs_item->next)
		childs_item->data->Draw(dt, childs_item->data);
	

	return true;
}

void j1Slider::DragVerticalSlider()
{
	iPoint mouse_motion;
	App->input->GetMouseMotion(mouse_motion.x, mouse_motion.y);
	if (position.y >= Max_slider.y)
	{
		position.y = Max_slider.y;
		Max_reached = true;
	}
	if (position.y <= Min_slider.y)
	{
		position.y = Min_slider.y;
		Min_reached = true;
	}
	if (position.y >= Min_slider.y && position.y <= Max_slider.y)
	{
		position.y += mouse_motion.y;
		Max_reached = false;
		Min_reached = false;
	}
}

void j1Slider::DragHoritzontalSlider()
{
	/*TODO
	iPoint mouse_motion;
	App->input->GetMouseMotion(mouse_motion.x, mouse_motion.y);
	position.x += mouse_motion.x;
	*/
}
