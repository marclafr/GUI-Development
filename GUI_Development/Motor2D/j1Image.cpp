#include "j1Image.h"
#include "j1Render.h"
#include "j1App.h"
#include "j1Input.h"

bool j1Image::Draw(float dt)
{
	/*for (p2List_item<Element*>* item = App->gui->elements.start; item; item = item->next)
	{
		if (item->data->e_type == image && item->data->is_visible == true)
		{
			j1Image* temp = (j1Image*)item->data;
			App->render->Blit(App->gui->GetAtlas(), item->data->position.x, item->data->position.y, &temp->section);
		}
	}*/
	/*Element* screen = App->gui->elements.start->data;
	for (p2List_item<Element*>* item = screen->sons.start; item; item = item->next)
	{
		item->data->Draw(dt);
	}*/

	return true;
}

bool j1Image::Update(float dt)
{
	for (p2List_item<Element*>* item = App->gui->elements.start; item; item = item->next)
	{
		if (item->data->e_type == image && item->data->l_click == true)
		{
			j1Image* temp = (j1Image*)item->data;
			iPoint mouse;
			App->input->GetMousePosition(mouse.x, mouse.y);
			//TODO calculate origin position once
			iPoint origin;
			origin.x = mouse.x - item->data->position.x;
			origin.y = mouse.y - item->data->position.y;
			item->data->position.x = mouse.x - origin.x;
			item->data->position.y = mouse.y - origin.y;
		}
	}
	return true;
}
