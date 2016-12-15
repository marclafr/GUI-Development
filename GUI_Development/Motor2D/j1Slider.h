#ifndef __SLIDER__
#define __SLIDER__

#include "j1Gui.h"
#include "p2Point.h"

class j1Slider :public Element
{
public:
	j1Slider(const SDL_Rect sect, SDL_Rect rect, SDL_Rect back_rect, SDL_Rect back_section, SliderType s_type, int viewport_distance, int id);
	~j1Slider();

	//slider -> viewport
	SDL_Rect section;
	SDL_Rect view_slider;


	bool slider_selected;
	SliderType slider_type;

	SDL_Rect back_rect;
	SDL_Rect back_section;
	iPoint Max_slider;
	bool Max_reached;
	iPoint Min_slider;
	bool Min_reached;
	
public:
	bool Draw(float dt, Element* item);
	bool Update(float dt, Element* item);

	bool AddScrollElement(Element* item);

private:
	void DragVerticalSlider();
	void DragHoritzontalSlider();

	p2List<Element*> scroll_elements;
	int scroll_elements_distance = 0;
	SDL_Rect view_port;
	int viewport_distance;

};

#endif // !__SLIDER__