#ifndef __ANIMATED_IMAGE__
#define __ANIMATED_IMAGE__

#include "j1Gui.h"
#include "j1Image.h"

class j1AnimatedImage :public j1Image
{
public:
	j1AnimatedImage(const SDL_Rect& rect, int id) : j1Image(elem_type::anim_image, rect, id) {}
	~j1AnimatedImage() {}

	//Animation anim;
public:
	//bool Draw(float dt);
	//bool Update(float dt);
};

#endif // !__ANIMATED_IMAGE__