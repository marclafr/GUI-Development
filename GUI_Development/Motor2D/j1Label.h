#ifndef __LABEL__
#define __LABEL__

#include "j1Gui.h"

//Non-Editable text
class j1Label :public Element
{
public:
	j1Label(p2SString text, int size, SDL_Rect rect, int id);
	~j1Label();

	UI_String text;
	SDL_Texture* text_texture;

	void SetText(const char * txt);

public:
	bool Draw(float dt, Element* item);
};

#endif // !__LABEL__