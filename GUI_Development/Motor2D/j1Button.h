#ifndef __BUTTON__
#define __BUTTON__

#include "j1Gui.h"

class j1Button :public Element
{
public:
	j1Button(const SDL_Rect section, SDL_Rect rect, uint tab_order, int id) : section(section), Element(elem_type::button, rect, tab_order, id) {}
	~j1Button() {}

	bool is_pressed;
	bool in_area;
	SDL_Rect section;

	SDL_Rect button_hover	{ 5, 117, 225, 61 };
	SDL_Rect brigth_button	{ 415,172,225,61 };
	SDL_Rect dark_button	{645, 165, 229, 69};

public:
	bool Draw(float dt, Element* item);
	bool Update(float dt, Element* item);
};

#endif // !__BUTTON__