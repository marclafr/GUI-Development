#include "j1TextBox.h"
#include "j1Render.h"
#include "j1App.h"
#include "j1Fonts.h"

bool j1TextBox::Draw(float dt)
{
	SDL_Color a{ ((0),(0),(0),(255)) };
	App->render->Blit(App->font->Print(text.text.GetString(), a), 400, 50);
	return true;
}