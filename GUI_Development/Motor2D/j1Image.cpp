#include "j1Image.h"
#include "j1Render.h"
#include "j1App.h"
#include "j1Input.h"

bool j1Image::Draw(float dt, Element* item)
{
	j1Image* temp = (j1Image*)item;
	App->render->Blit(App->gui->GetAtlas(), item->position.x, item->position.y, &temp->section);
	p2List_item<Element*>* son_item = item->sons.start;
	for (int i = 0; item->sons.count() > i; i++, son_item = son_item->next)
	{
		p2List_item<Element*>* son_item = item->sons.start;
		son_item->data->Draw(dt, son_item->data);
	}

	return true;
}

bool j1Image::Update(float dt, Element* item)
{
	j1Image* temp = (j1Image*)item;
	iPoint mouse;
	App->input->GetMousePosition(mouse.x, mouse.y);
	//TODO calculate origin position once
	iPoint origin;
	origin.x = mouse.x - item->position.x;
	origin.y = mouse.y - item->position.y;
	item->position.x = mouse.x - origin.x;
	item->position.y = mouse.y - origin.y;

	p2List_item<Element*>* son_item = item->sons.start;
	for (int i = 0; item->sons.count() > i; i++, son_item = son_item->next)
	{
		p2List_item<Element*>* son_item = item->sons.start;
		son_item->data->Update(dt, son_item->data);
	}
	return true;
}
