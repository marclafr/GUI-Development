#include "j1Button.h"
#include "j1Render.h"
#include "j1App.h"
#include "j1Input.h"

bool j1Button::Draw(float dt)
{
	for (p2List_item<Element*>* item = App->gui->elements.start; item; item = item->next)
	{
		if (item->data->e_type == button && item->data->is_visible == true)
		{
			j1Button* temp = (j1Button*)item->data;
			App->render->Blit(App->gui->GetAtlas(), item->data->rect.x, item->data->rect.y, &temp->section);
		}
	}
	return true;
}

bool j1Button::Update(float dt)
{

	for (p2List_item<Element*>* item = App->gui->elements.start; item; item = item->next)
	{
		if (item->data->e_type == button)
		{
			j1Button* temp = (j1Button*)item->data;
			if (item->data->l_click == true || item->data->r_click == true)
			{
				if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT || App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_REPEAT)
					temp->section = { 415,172,225,61 };
				
				if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_UP || App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_UP)
					temp->section = { 5, 117, 225, 61 };
			}

			else if (item->data->mouse_inside == true)
			{
				temp->section = { 5, 117, 225, 61 };
			}

			if (item->data->mouse_inside == false)
			{
				temp->section = { 647, 173, 225, 61 };
			}
		}
	}
	return true;
}
