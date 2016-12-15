#include "j1Slider.h"
#include "j1Render.h"
#include "j1App.h"
#include "j1Fonts.h"
#include "j1Input.h"

j1Slider::j1Slider(const SDL_Rect sect, SDL_Rect rect, SDL_Rect back_rect, SDL_Rect back_section, SliderType s_type, int viewport_distance, int id) : section(sect), slider_type(s_type), back_rect(back_rect), back_section(back_section), Min_slider{ rect.x, rect.y }, viewport_distance(viewport_distance), Element(elem_type::slider, rect, 0, id)
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
	j1Slider* slider = (j1Slider*)item;

	if (item->l_click == true && slider->slider_type == VERTICAL)
	{
		DragVerticalSlider();
		for (p2List_item<Element*>* scroll_item = slider->scroll_elements.start; scroll_item; scroll_item = scroll_item->next)
		{
			if (slider->Max_reached == false && slider->Min_reached == false)
			{
				float movement = (float)this->back_rect.h / (scroll_elements_distance - this->back_rect.h);
				scroll_item->data->DragElementAxisY(movement);
			}
		}
	}

	if (item->l_click == true && slider->slider_type == HORITZONTAL)
	{
		DragHoritzontalSlider();
	
	}

	p2List_item<Element*>* childs_item;
	for (childs_item = item->childs.start; childs_item; childs_item = childs_item->next)
		childs_item->data->Update(dt, childs_item->data);

	return true;
}

bool j1Slider::AddScrollElement(Element * item)
{
	if (this->can_drag == true)
		item->can_drag = true;

	scroll_elements.add(item);
	if (this->slider_type == VERTICAL)
		scroll_elements_distance += item->position.h;

	else if (this->slider_type == HORITZONTAL)
		scroll_elements_distance += item->position.w;

	return true;
}

bool j1Slider::Draw(float dt, Element* item)
{
	j1Slider* slider = (j1Slider*)item;
	App->render->Blit(App->gui->GetAtlas(), slider->back_rect.x - App->render->camera.x, slider->back_rect.y - App->render->camera.y, &slider->back_section);
	App->render->Blit(App->gui->GetAtlas(), item->position.x - App->render->camera.x, item->position.y - App->render->camera.y, &slider->section);
	for (p2List_item<Element*>* childs_item = item->childs.start; childs_item; childs_item = childs_item->next)
		childs_item->data->Draw(dt, childs_item->data);
	if (this->slider_type == VERTICAL)
		view_port = { this->Min_slider.x, this->Min_slider.y, viewport_distance, this->Max_slider.y - this->Min_slider.y};
	else if (this->slider_type == HORITZONTAL)
		view_port = { this->Min_slider.x, this->Min_slider.y, this->Max_slider.x - this->Min_slider.x, viewport_distance };

	SDL_RenderSetViewport(App->render->renderer, &view_port);
	for (p2List_item<Element*>* scroll_elem = scroll_elements.start; scroll_elem; scroll_elem = scroll_elem->next)
		scroll_elem->data->Draw(dt, scroll_elem->data);

	SDL_RenderSetViewport(App->render->renderer, NULL);

	return true;
}

void j1Slider::DragVerticalSlider()
{
	iPoint mouse_motion;
	App->input->GetMouseMotion(mouse_motion.x, mouse_motion.y);

	if (position.y >= Min_slider.y && position.y <= Max_slider.y)
	{
		position.y += mouse_motion.y;
		Max_reached = false;
		Min_reached = false;
	}
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
}

void j1Slider::DragHoritzontalSlider()
{
	/*TODO
	iPoint mouse_motion;
	App->input->GetMouseMotion(mouse_motion.x, mouse_motion.y);
	position.x += mouse_motion.x;
	*/
}
