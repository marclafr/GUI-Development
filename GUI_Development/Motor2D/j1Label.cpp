#include "j1Label.h"
#include "j1Render.h"
#include "j1App.h"
#include "j1Fonts.h"

void j1Label::SetText(const char * txt)
{
	text.text = txt;	
}

bool j1Label::Draw(float dt, Element* item)
{
	//SDL_Color color{ ((255),(255),(255),(255)) };

	j1Label* temp = (j1Label*)item;
	App->render->Blit(App->font->Print(temp->text.text.GetString(), SDL_Color{ (255),(0),(255),(255) }), item->position.x, item->position.y);

	for (p2List_item<Element*>* childs_item = item->childs.start; childs_item; childs_item = childs_item->next)
	{
		childs_item->data->Draw(dt, childs_item->data);
	}

	return true;
}
