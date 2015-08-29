#include "tile.h"

Tile::Tile()
{
	life = DEAD;
}

bool Tile::IsDead()
{
	bool status;
	switch(life)
	{
		case ALIVE: status = false; break;
		case DEAD: status = true; break;
	}
	return status;
}

void Tile::SetLife(LIFE_STATUS status) 
{ 
	this->life = status;
}