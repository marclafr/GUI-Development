#ifndef __BUTTON__
#define __BUTTON__

#include "j1Gui.h"

class j1Button :public Element
{
public:
	j1Button(SDL_Rect rect, int id) : Element(elem_type::button, rect, id) {}
	~j1Button() {}

	bool is_pressed;
	bool in_area;

public:
	//bool Draw();
	//bool Update();
};

#endif // !__BUTTON__