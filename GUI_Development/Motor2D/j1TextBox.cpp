#include "j1TextBox.h"
#include "j1Render.h"
#include "j1App.h"
#include "j1Fonts.h"

bool j1TextBox::Draw(float dt)
{
	SDL_Color color{ ((0),(0),(0),(255)) };
	
	for (p2List_item<Element*>* item = App->gui->elements.start; item; item = item->next)
	{
		if (item->data->e_type == text_box)
		{
			j1TextBox* temp = (j1TextBox*)item->data;
			App->render->Blit(App->font->Print(temp->text.text.GetString(), color), item->data->rect.x, item->data->rect.y);
		}
	}
	return true;
}
//temp->is_visible == true && 