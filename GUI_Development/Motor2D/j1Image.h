#ifndef __IMAGE__
#define __IMAGE__

#include "j1Gui.h"

class j1Image :public Element
{
public:
	j1Image(SDL_Rect rect, int id) : Element(elem_type::image, rect, id) {}
	~j1Image() {}

public:
	//void Draw();
	//void Update();

};

#endif // !__IMAGE__

/*
#include "j1Image.h"
#include "j1Render.h"
#include "j1App.h"

void j1Image::Draw()
{
	App->render->Blit(App->gui->GetAtlas(), 350, 75, &App->gui->elements.start->data->rect);
}
*/