#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
#include "p2List.h"

#define CURSOR_WIDTH 2


#include "SDL/include/SDL_rect.h"
struct SDL_Texture;
struct _TTF_Font;
struct Element;
class j1Image;
class j1TextBox;
class j1Button;
class j1AnimatedImage;
class j1Label;

enum elem_type
{
	label = 0,
	text_box,
	image,
	anim_image,
	button,
	unknown
};
#define UNKNOWN_NUM 5

struct Element
{
	Element(elem_type type, SDL_Rect& rectangle, int ident) : e_type(type), position(rectangle), id(ident), is_visible(true) {}
	~Element() {}

	SDL_Rect position;
	int id;
	elem_type e_type;
	bool mouse_inside;
	bool r_click;
	bool l_click;
	bool is_visible;
	p2List<Element*> childs;
	Element* parent;
	bool can_drag;
	int priority;

	void SetPosition(SDL_Rect& rect); //set position and size

	virtual bool Update(float dt, Element* item)	 { return true; }
	virtual bool Draw(float dt, Element* item)		 { return true; }

private:
	SDL_Rect section;
};

struct UI_String
{
	UI_String(p2SString& text, int text_size) : text(text), text_size(text_size) {}
	UI_String(UI_String& txt) { text = txt.text; text_size = txt.text_size; }
	~UI_String() {}
	p2SString text;
	int text_size;
	_TTF_Font* font;
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

	bool Update(float dt);

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Gui creation functions
	p2List<Element*> elements;
	int element_id = 0;
	j1Label* CreateLabel(const p2SString& text, int size, SDL_Rect& rect);
	j1TextBox* CreateTextBox(const p2SString& text, int size, bool is_pw, SDL_Rect& rect);
	j1Image* CreateImage(SDL_Rect& section, SDL_Rect& rect);
	j1AnimatedImage* CreateAnimImage(SDL_Rect& section, SDL_Rect& rect);
	j1Button* CreateButton(SDL_Rect& section, SDL_Rect& rect);

	bool DeleteElement(int entity_id);

	SDL_Texture* GetAtlas() const;

private:

	SDL_Texture* atlas;
	p2SString atlas_file_name;
};

#endif // __j1GUI_H__