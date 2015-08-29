#include "ui.h"

UI::UI(SDL_Surface *surface)
{
	TTF_Init();
	
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = System::screenW /32 * 32;
	srcRect.h = 32;

	dstRect.x = 0;
	dstRect.y = 3;
	dstRect.h = 32;
	dstRect.w = System::screenW /32 * 32;

	buttons.push_back(new Button(INC_SPEED));
	buttons.push_back(new Button(DEC_SPEED));
	buttons.push_back(new Button(LOAD));
	buttons.push_back(new Button(SAVE));
	buttons.push_back(new Button(CLEAR));
	buttons.push_back(new Button(BRUSH_SIZE_1));
	buttons.push_back(new Button(BRUSH_SIZE_9));
}

UI::~UI()
{
	for (Uint32 i = 0; i < buttons.size(); i++)
    {
        delete buttons[i];
    }
}

void UI::Draw(SDL_Surface *surface)
{
    for (Uint32 i = 0; i < buttons.size(); i++)
        buttons[i]->Draw(surface);
}

void UI::Update(System *system, Grid *level)
{
    for (Uint32 i = 0; i < buttons.size(); i++)
	{
        buttons[i]->Update();

		// If a button has been pressed but no action has been taken...
		if (!buttons[i]->getDone())
		{
			switch (buttons[i]->getName()) // Give it an action
			{
			case DEC_SPEED:
				if (System::timeSpeed < 4000)
					System::timeSpeed += 250;
				break;
			case INC_SPEED:
				if (System::timeSpeed > 0)
				System::timeSpeed -= 250;
				break;
			case SAVE:
				level->SaveMap(); break;
			case LOAD:
				level->LoadMap(); break;
			case CLEAR:
				level->Clear(); break;
			case BRUSH_SIZE_1:
				level->SetBrushSize(1);
				buttons[i+1]->SetSelected(false);
				break;
			case BRUSH_SIZE_9:
				level->SetBrushSize(9);
				buttons[i-1]->SetSelected(false);
				break;
			}
			// The button's action has been taken
			buttons[i]->setDone(true);
		}
	}
}