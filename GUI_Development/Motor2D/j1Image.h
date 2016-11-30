#ifndef __IMAGE__
#define __IMAGE__

#include "j1Gui.h"

class j1Image :public Element
{
public:
	j1Image(elem_type image_type, const SDL_Rect& section, SDL_Rect& rect, int id) : section(section), Element(image_type, rect, id) {}
	~j1Image() {}

	SDL_Rect section;
public:
	bool Draw(float dt);
	bool Update(float dt);
};

#endif // !__IMAGE__