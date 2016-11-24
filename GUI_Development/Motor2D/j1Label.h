#ifndef __LABEL__
#define __LABEL__

#include "j1Gui.h"

class j1Label :public Element
{
public:
	j1Label(p2SString text, int size, int id) : text(text, size), Element(elem_type::label, rect, id) {}
	~j1Label() {}

	UI_String text;

public:
	//bool Draw();
};

#endif // !__LABEL__