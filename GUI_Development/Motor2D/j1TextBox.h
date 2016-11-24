#ifndef __TEXT_BOX__
#define __TEXT_BOX__

#include "j1Gui.h"

class j1TextBox :public Element
{
public:
	j1TextBox(p2SString text, int size, bool is_password, int id) : text(text, size), is_password(is_password), Element(elem_type::image, rect, id) {}
	~j1TextBox() {}

	UI_String text;
	bool is_password;

public:
	//bool Draw();
	//bool Update();
};

#endif // !__TEXT_BOX__