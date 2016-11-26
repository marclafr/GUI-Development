#include "j1TextBox.h"
#include "j1Render.h"
#include "j1App.h"
#include "j1Fonts.h"

bool j1TextBox::Draw(float dt)
{
	SDL_Color a{ ((0),(0),(0),(255)) };
	
	for (p2List_item<Element*>* item = App->gui->elements.start; item; item = item->next)
	{
		if (item->data->e_type == image)
			App->render->Blit(App->font->Print(text.text.GetString(), a), 400, 50);
	}
	return true;
}
//item->data->is_visible == true && 