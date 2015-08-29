#include "button.h"

SDL_Surface *Button::surface;
SDL_Surface *Button::selectedSurface;
SDL_Surface *Button::highlightedSurface;
Uint32 Button::colorKey;


Button::Button(BUTTON_NAME name)
{
    dstRect.w = srcRect.w = 20;
    dstRect.h = srcRect.h = 20;
    this->name = name;
	srcRect.y = 0;
    Setup(name);
    set = false;
    highlighted = false;
	activationTime = 0;
	done = true;
}

void Button::Initialize()
{
	surface = NULL;
    surface = SDL_LoadBMP("data/buttons.bmp");

    if (surface == NULL)
    {
#ifdef _DEBUG
        fprintf(stderr, "buttons.bmp could not be loaded!\n");
#endif
        exit(-2);
    }
	selectedSurface = SDL_CreateRGBSurface(SDL_HWSURFACE, 20, 20, 32, 0, 0, 0, 220);
    highlightedSurface = SDL_CreateRGBSurface(SDL_HWSURFACE, 20, 20, 32, 0, 0, 0, 220);
    SDL_SetAlpha(selectedSurface, SDL_SRCALPHA, 200);
    SDL_SetAlpha(highlightedSurface, SDL_SRCALPHA, 200);
    colorKey = SDL_MapRGB(surface->format, 0xFF, 0, 0xFF);
    SDL_SetColorKey(surface, SDL_SRCCOLORKEY, colorKey);
}


void Button::Deallocate()
{
	SDL_FreeSurface(Button::selectedSurface);
    SDL_FreeSurface(Button::highlightedSurface);
    SDL_FreeSurface(Button::surface);
}


void Button::Draw(SDL_Surface *surface)
{
	dstRect.x -= 1;
	dstRect.y -= 1;
	dstRect.w += 2;
	dstRect.h += 2;
	SDL_FillRect(surface, &dstRect, SDL_MapRGB(Button::selectedSurface->format, 120, 120, 120));
	dstRect.x += 1;
	dstRect.y += 1;
	dstRect.w -= 2;
	dstRect.h -= 2;

    if (selected)
    {
		SDL_FillRect(Button::selectedSurface, NULL, SDL_MapRGB(Button::selectedSurface->format, 245, 220, 75));
        SDL_BlitSurface(Button::selectedSurface, NULL, surface, &dstRect);
    }
    else if (highlighted)
    {
        SDL_FillRect(Button::highlightedSurface, NULL, SDL_MapRGB(Button::selectedSurface->format, 0xFF, 0xFF, 0xFF));
        SDL_BlitSurface(Button::highlightedSurface, NULL, surface, &dstRect);
    }

    else
    {
        SDL_FillRect(Button::selectedSurface, NULL, SDL_MapRGB(Button::selectedSurface->format, 200, 200, 200));
        SDL_BlitSurface(Button::selectedSurface, NULL, surface, &dstRect);
    }

	SDL_BlitSurface(Button::surface, &srcRect, surface, &dstRect);
}

void Button::Update()
{
    int x, y;
    Uint8 pressed;
    SDL_PumpEvents();
    pressed = SDL_GetMouseState(&x, &y);

    if (pressed != SDL_BUTTON_LEFT && type == TOGGLE_DIS)
	{
        set = false;
		selected = false;
	}

    if (dstRect.x < x &&
        dstRect.x + dstRect.w > x &&
        dstRect.y < y &&
        dstRect.y + dstRect.h > y)
    {
        if (!highlighted && !selected  && !set)
            highlighted = true;
        if (pressed == SDL_BUTTON_LEFT &&  !set)
        {
            if (!selected)
            {
				activationTime = SDL_GetTicks();
                selected = true;	
				done = false;
            }
        }
    }

    else
    {
        highlighted = false;
		if (type == TOGGLE_DIS)
			selected = false;
    }
}

void Button::Setup(BUTTON_NAME name)
{
	int bottomY = System::screenH - 24;

	switch (name)
	{
	case INC_SPEED:
		dstRect.x = 40;
		dstRect.y = bottomY;
		srcRect.x = 360; 
		selected = false; 
		type = TOGGLE_DIS; break;
	case DEC_SPEED:
		dstRect.x = 70;
		dstRect.y = bottomY;
		srcRect.x = 380; 
		selected = false; 
		type = TOGGLE_DIS; break;
	case SAVE:
		dstRect.x = 100;
        dstRect.y = bottomY;
        srcRect.x = 180;
		selected = false; 
		type = TOGGLE_DIS; break;
	case LOAD:
		dstRect.x = 130;
        dstRect.y = bottomY;
        srcRect.x = 160;
		selected = false; 
		type = TOGGLE_DIS; break;
	case CLEAR:
		dstRect.x = 160;
        dstRect.y = bottomY;
        srcRect.x = 40;
		selected = false; 
		type = TOGGLE_DIS; break;
	case BRUSH_SIZE_1:
		dstRect.x = 190;
        dstRect.y = bottomY;
        srcRect.x = 0;
        selected = true; 
		type = TOGGLE_ENA; break;
	case BRUSH_SIZE_9:
        dstRect.x = 220;
        dstRect.y = bottomY;
        srcRect.x = 20;
		selected = false;
		type = TOGGLE_ENA; break;
    }
}


