#ifndef __TEXT_BOX__
#define __TEXT_BOX__

#include "j1Gui.h"

//Editable Text
class j1TextBox :public Element
{
public:
	j1TextBox(p2SString text, SDL_Texture& tex, int size, bool is_password, SDL_Rect& rect, uint tab_order, int id);
	~j1TextBox();

	bool is_password;
	bool text_clicked = false;
	UI_String text;
	SDL_Texture* text_texture;

private:
	p2SString partial_text;
	bool text_changed = true;
	int write_pos = 0;

public:
	void SetText(const char* text);
	const char* GetText();
	bool Draw(float dt, Element* item);
	bool Update(float dt, Element* item);
};

#endif // !__TEXT_BOX__