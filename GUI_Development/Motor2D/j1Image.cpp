#include "j1Image.h"
#include "j1Render.h"
#include "j1App.h"

bool j1Image::Draw(float dt)
{
	for (p2List_item<Element*>* item = App->gui->elements.start; item; item = item->next)
	{
		if (item->data->e_type == image && item->data->is_visible == true)
		{
			j1Image* temp = (j1Image*)item->data;
			App->render->Blit(App->gui->GetAtlas(), item->data->position.x, item->data->position.y, &temp->section);
		}
	}
	return true;
}
