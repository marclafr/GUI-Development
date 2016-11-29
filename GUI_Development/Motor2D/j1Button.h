#ifndef __BUTTON__
#define __BUTTON__

#include "j1Gui.h"

class j1Button :public Element
{
public:
	j1Button(const SDL_Rect section, SDL_Rect rect, int id) : section(section), Element(elem_type::button, rect, id) {}
	~j1Button() {}

	bool is_pressed;
	bool in_area;
	SDL_Rect section;

public:
	bool Draw(float dt);
	//bool Update(float dt);
};

#endif // !__BUTTON__