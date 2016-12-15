#ifndef __IMAGE__
#define __IMAGE__

#include "j1Gui.h"

class j1Image :public Element
{
public:
	j1Image(elem_type image_type, const SDL_Rect& section, SDL_Rect& rect, uint tab_order, int id) : section(section), Element(image_type, rect, tab_order, id)
	{
		if (tab_order != 0 && rect.x == 240 && rect.y == 80)
			tab_focus = true;
	}
	~j1Image() {}

	SDL_Rect section;

public:
	bool Draw(float dt, Element* item);
	bool Update(float dt, Element* item);
};

#endif // !__IMAGE__