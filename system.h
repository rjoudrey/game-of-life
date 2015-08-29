#include "dependencies.h"

#ifndef SYSTEM_H
#define SYSTEM_H

class System
{
public:
	System(string);
	~System();
	static void LoadConfig();
	static int screenW, screenH, tileSize, mapW, 
			   mapH, timeSpeed, borderSize;
	string filename;
	SDL_Surface *buffer;
	bool quit;
	SDL_Event event;
};

#endif