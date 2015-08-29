#include "dependencies.h"

#ifndef GRID_H
#define GRID_H

class Grid
{
public:
	Grid(SDL_Surface *);
	void FreeTiles();
	void Draw(SDL_Surface *);
	void Update();
	void Fill();
	void Clear();
	void GetInput();
	void SaveMap();
	void LoadMap();
	inline void SetBrushSize(int size) { brushSize = size; }
	inline int GetBrushSize() { return brushSize; }
	inline void SetShowGrid(bool tf) { showGrid = tf; }
	inline int GetShowGrid() { return showGrid; }
private:
	bool showGrid;
	string fileName;
	void DrawHighlightedCell(SDL_Surface *, int, int, int, int);
	void SetTile(int, int, LIFE_STATUS);
	bool buttonHeld, showCollision;
	int brushSize, startX, startY;
	Uint32 white, black;
	SDL_Rect srcRect, dstRect, gridRect;
	Tile **tile;
};

#endif