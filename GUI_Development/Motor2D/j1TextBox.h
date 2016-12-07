#ifndef __TEXT_BOX__
#define __TEXT_BOX__

#include "j1Gui.h"

//Editable Text
class j1TextBox :public Element
{
public:
	j1TextBox(p2SString text, SDL_Texture& tex, int size, bool is_password, SDL_Rect& rect, int id) : text(text, size), text_texture(&tex), is_password(is_password), Element(elem_type::text_box, rect, id) {}
	~j1TextBox() {}

	bool is_password;
	bool text_clicked = false;
	UI_String text;
	SDL_Texture* text_texture;

private:
	bool text_changed = true;

public:
	void SetText(const char* text);
	const char* GetText();
	bool Draw(float dt, Element* item);
	bool Update(float dt, Element* item);
};

#endif // !__TEXT_BOX__