#include "dependencies.h"

#ifndef UI_H
#define UI_H

class UI
{
public: 
	UI(SDL_Surface *);
	~UI();
	void Draw(SDL_Surface *);
	void Update(System *, Grid *);
private:
	SDL_Rect srcRect, dstRect;
	vector<Button*> buttons;
	vector<Text*> texts;
};

#endif