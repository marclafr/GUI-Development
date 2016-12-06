#include "j1Button.h"
#include "j1Render.h"
#include "j1App.h"
#include "j1Input.h"

bool j1Button::Draw(float dt, Element* item)
{
	j1Button* temp = (j1Button*)item;
	App->render->Blit(App->gui->GetAtlas(), item->position.x, item->position.y, &temp->section);
	p2List_item<Element*>* childs_item = item->childs.start;
	for (p2List_item<Element*>* childs_item = item->childs.start; childs_item; childs_item = childs_item->next)
	{
		childs_item->data->Draw(dt, childs_item->data);
	}

	return true;
}

bool j1Button::Update(float dt, Element* item)
{
	p2List_item<Element*>* childs_item;
	for (childs_item = item->childs.start; childs_item; childs_item = childs_item->next)
	{
		childs_item->data->Update(dt, childs_item->data);
	}
	
	j1Button* temp = (j1Button*)item;
	if (item->l_click == true || item->r_click == true)
	{
		if (item->l_click == true || item->r_click == true)
			temp->section = { 415,172,225,61 };

		else
			temp->section = { 5, 117, 225, 61 };
	}

	else if (item->mouse_inside == true)
	{
		temp->section = { 5, 117, 225, 61 };
	}

	if (item->mouse_inside == false)
	{
		temp->section = { 647, 173, 225, 61 };
	}

	if ((temp->l_click == true || item->parent->l_click == true) && item->can_drag == true)
	{
		iPoint mouse_motion;
		App->input->GetMouseMotion(mouse_motion.x, mouse_motion.y);
		temp->position.x += mouse_motion.x;
		temp->position.y += mouse_motion.y;
		for (childs_item = item->childs.start; childs_item; childs_item = childs_item->next)
		{
			childs_item->data->position.x += mouse_motion.x;
			childs_item->data->position.y += mouse_motion.y;
		}
	}

	return true;
}
