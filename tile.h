#include "dependencies.h"

#ifndef TILE_H
#define TILE_H

class Tile
{
public:
	Tile();
	bool IsDead();
	void SetLife(LIFE_STATUS status);
private:
	LIFE_STATUS life;
};
#endif