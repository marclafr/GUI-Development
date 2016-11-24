#ifndef __ANIMATED_IMAGE__
#define __ANIMATED_IMAGE__

#include "j1Gui.h"
#include "j1Image.h"

class j1AnimatedImage :public j1Image
{
public:
	j1AnimatedImage(SDL_Rect rect, int id) : j1Image(elem_type::anim_image, rect, id) {}
	~j1AnimatedImage() {}

	//SDL_Animation anim;
public:
	//bool Draw();
	//bool Update();
};

#endif // !__ANIMATED_IMAGE__