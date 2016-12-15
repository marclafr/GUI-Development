#include "j1Image.h"
#include "j1Render.h"
#include "j1App.h"
#include "j1Input.h"

bool j1Image::Draw(float dt, Element* item)
{
	j1Image* temp = (j1Image*)item;
	App->render->Blit(App->gui->GetAtlas(), item->position.x - App->render->camera.x, item->position.y - App->render->camera.y, &temp->section);
	for (p2List_item<Element*>* childs_item = item->childs.start; childs_item; childs_item = childs_item->next)
	{
		childs_item->data->Draw(dt, childs_item->data);
	}

	return true;
}

bool j1Image::Update(float dt, Element* item)
{
	j1Image* temp = (j1Image*)item;
	iPoint mouse_motion;

	p2List_item<Element*>* childs_item;
	for (childs_item = item->childs.start; childs_item; childs_item = childs_item->next)
		childs_item->data->Update(dt, childs_item->data);
	
	if (temp->l_click == true && item->can_drag == true)
			item->DragElement();

	return true;
}