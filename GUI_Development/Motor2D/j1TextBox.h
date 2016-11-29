#ifndef __TEXT_BOX__
#define __TEXT_BOX__

#include "j1Gui.h"

class j1TextBox :public Element
{
public:
	j1TextBox(p2SString text, int size, bool is_password, SDL_Rect& rect, int id) : text(text, size), is_password(is_password), Element(elem_type::text_box, rect, id) {}
	~j1TextBox() {}

	bool is_password;
	
private:
	UI_String text;

public:
	void SetText(const char* text);
	const char* GetText();
	bool Draw(float dt);
	//bool Update(float dt);
};

#endif // !__TEXT_BOX__