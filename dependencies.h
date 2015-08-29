#ifndef DEPENDENCIES_H
#define DEPENDENCIES_H

class Button;
class Grid; 
class Tile;
class UI;
class System;
class Tile;
class Text;
class Grid;
enum DIR; 
enum LIFE_STATUS;
enum BUTTON_NAME;
enum BUTTON_TYPE;

#include <iostream>
#include <fstream>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include <time.h>
 
using namespace std;

#include "system.h"
#include "button.h"
#include "ui.h"
#include "grid.h"
#include "tile.h"

enum DIR { UP, DOWN, LEFT, RIGHT };
enum LIFE_STATUS { DEAD, ALIVE };
enum BUTTON_NAME { 
	INC_SPEED, DEC_SPEED, SAVE, LOAD, FILL, 
	CLEAR, BRUSH_SIZE_1, BRUSH_SIZE_9 };
enum BUTTON_TYPE {
	TOGGLE_ENA, TOGGLE_DIS };

#endif