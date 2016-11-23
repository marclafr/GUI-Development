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