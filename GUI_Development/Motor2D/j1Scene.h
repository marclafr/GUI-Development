#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"

struct SDL_Texture;
class GuiImage;
class GuiText;
class j1Image; 
struct Element;

class j1Scene : public j1Module
{
public:

	j1Scene();

	// Destructor
	virtual ~j1Scene();

	// Called before render is available
	bool Awake(pugi::xml_node&);

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

	//Load/Save
	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;

	Element* screen;

	SDL_Texture* movingtile;

private:
	SDL_Texture* debug_tex;
	GuiImage* banner;
	GuiText* text;

	p2List<p2SString> labels_txt;
	p2List<int> labels_posx;
	p2List<int> labels_posy;
	p2List<bool> labels_draggable;

	j1Image* heroes1;
	j1Image* heroes2;

	int heroes_y_pos = 125;
	int heroes1_x_pos_min = 415;
	int heroes1_x_pos_max = 1845;
	int heroes2_x_pos_min = 1439;
};

#endif // __j1SCENE_H__