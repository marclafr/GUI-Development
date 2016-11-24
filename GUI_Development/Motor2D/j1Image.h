#ifndef __IMAGE__
#define __IMAGE__

#include "j1Gui.h"

class j1Image :public Element
{
public:
	j1Image(elem_type image_type, SDL_Rect rect, int id) : Element(image_type, rect, id) {}
	~j1Image() {}

public:
	//bool Draw();
	//bool Update();
};

#endif // !__IMAGE__