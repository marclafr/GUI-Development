#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"

#define CURSOR_WIDTH 2

// TODO 1: Create your structure of classes
enum elem_type
{
	label = 0,
	text_box,
	image,
	anim_image,
	button,
	input,
	unknown
};

struct Element
{
	Element(elem_type type, SDL_Rect rectangle, int ident) : e_type(type), rect(rectangle), id(ident) {}
	~Element() {}

	SDL_Rect rect;
	int id;
	elem_type e_type;

	void SetRect(SDL_Rect rect); //set position and size

	virtual bool Update() { return true; }
	virtual bool Draw() { return true; }
	virtual void ManageInput() {}
};

struct UI_String
{
	UI_String(p2SString text, int text_size) : text(text), text_size(text_size) {}
	UI_String(UI_String& txt) { text = txt.text; text_size = txt.text_size; }
	p2SString text;
	int text_size;
	//SDL_Texture* font;
};
// ---------------------------------------------------

class j1Gui : public j1Module
{
public:

	j1Gui();

	// Destructor
	virtual ~j1Gui();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// TODO 2: Create the factory methods
	// Gui creation functions
	p2List<Element*> elements;
	int element_id = 0;
	Element* CreateElement(elem_type type, SDL_Rect rect);
	bool DeleteElement(int entity_id);

	SDL_Texture* GetAtlas() const;

private:

	SDL_Texture* atlas;
	p2SString atlas_file_name;
};

#endif // __j1GUI_H__