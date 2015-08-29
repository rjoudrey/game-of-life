#include "dependencies.h"

#ifndef BUTTON_H
#define BUTTON_H

class Button
{
public:
	Button(BUTTON_NAME);
	static void Initialize();
	static void Deallocate();
	void Draw(SDL_Surface *surface);
	void Update();
	void Setup(BUTTON_NAME name);
	inline bool getDone() { 
		return done; }
	inline void setDone(bool tf) { 
		done = tf; }
	inline bool GetSelected() { 
		return selected; }
	inline void SetSelected(bool selected) { 
		this->selected = selected; }
	inline const int getName() { 
		return name; }
private:
	SDL_Rect dstRect;
	SDL_Rect srcRect;
	static SDL_Surface *surface;
	static SDL_Surface *selectedSurface;
	static SDL_Surface *highlightedSurface;
	static Uint32 colorKey;
	BUTTON_NAME name; BUTTON_TYPE type;
	bool set, selected, highlighted, done;
	int activationTime;
};

#endif