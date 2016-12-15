#include "j1Label.h"
#include "j1Render.h"
#include "j1App.h"
#include "j1Fonts.h"

j1Label::j1Label(p2SString txt, int size, SDL_Rect rect, int id) : text(txt, size), Element(elem_type::label, rect, 0, id)
{
	text.SetFont("fonts/open_sans/OpenSans-Regular.ttf", 20);
	text_texture = App->font->Print(text.text.GetString(), SDL_Color { (255), (0), (255), (255) });
}

j1Label::~j1Label()
{

}

void j1Label::SetText(const char * txt)
{
	text.text = txt;	
}

bool j1Label::Draw(float dt, Element* item)
{
	j1Label* temp = (j1Label*)item;
	App->render->Blit(temp->text_texture, item->position.x - App->render->camera.x, item->position.y - App->render->camera.y);

	for (p2List_item<Element*>* childs_item = item->childs.start; childs_item; childs_item = childs_item->next)
	{
		childs_item->data->Draw(dt, childs_item->data);
	}

	return true;
}
