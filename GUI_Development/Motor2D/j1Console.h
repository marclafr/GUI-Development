#ifndef __j1CONSOLE_H__
#define __j1CONSOLE_H__

#include "j1Module.h"


class j1Console : public j1Module
{

public:

	j1Console();

	// Destructor
	virtual ~j1Console();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool PreUpdate();

	bool Update(float dt);

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

};

#endif // __j1CONSOLE_H__