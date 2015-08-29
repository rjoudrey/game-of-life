// Ricky Joudrey
// Game of Life 

#include "dependencies.h"

int main(int argc, char *args[])
 {
	Uint32 timer = SDL_GetTicks();
	bool pause = false;
	srand(time(NULL));
	System::LoadConfig();
	System system("Game of Life");
	Button::Initialize();
	Grid grid(system.buffer);
	UI ui(system.buffer);

	while (!system.quit)
	{
		SDL_EnableKeyRepeat(0, 0);
		while (SDL_PollEvent(&system.event))
		{
			if (system.event.type == SDL_QUIT)
					system.quit = true; 
			if (system.event.type == SDL_KEYDOWN)
			{
				switch (system.event.key.keysym.sym)
				{
					case SDLK_SPACE: 
						pause = !pause;
						break; 
					case SDLK_g:
						grid.SetShowGrid(!grid.GetShowGrid()); 
					break;
					case SDLK_ESCAPE:
						system.quit = true; 
						break;
				}
			}
			grid.GetInput();
		}
		ui.Update(&system, &grid);
		if (SDL_GetTicks() > timer + System::timeSpeed && !pause) {
			timer = SDL_GetTicks();
				grid.Update();	}
		SDL_FillRect(system.buffer,NULL, 0x36648B);
		grid.Draw(system.buffer);
		ui.Draw(system.buffer);
		SDL_Flip(system.buffer);
	}
	Button::Deallocate();
	return 0;
 }