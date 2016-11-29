#include "j1Button.h"
#include "j1Render.h"
#include "j1App.h"

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
