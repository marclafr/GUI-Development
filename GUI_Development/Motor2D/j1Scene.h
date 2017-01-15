#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"

struct SDL_Texture;
class GuiImage;
class GuiText;
class j1Image; 

class j1Scene : public j1Module
{
public:

	j1Scene();

	// Destructor
	virtual ~j1Scene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

private:
	SDL_Texture* debug_tex;
	GuiImage* banner;
	GuiText* text;

	j1Image* heroes1;
	j1Image* heroes2;

	int heroes_y_pos = 125;
	int heroes1_x_pos_min = 415;
	int heroes1_x_pos_max = 1845;
	int heroes2_x_pos_min = 1439;
};

#endif // __j1SCENE_H__