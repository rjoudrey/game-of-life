#include "system.h"

int System::screenW, System::screenH, System::tileSize, 
	System::mapW, System::mapH, System::timeSpeed, System::borderSize;

System::System(string programName)
{
	timeSpeed = 1000;
    quit = false;
    buffer = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
#ifdef _DEBUG
        fprintf(stderr, "Could not initialize SDL!\n");
#endif
        exit(-2);
    }
    else
    {
#ifdef _DEBUG
        fprintf(stdout, "SDL initialized properly!\n");
#endif
        atexit(SDL_Quit);
    }
    buffer = SDL_SetVideoMode(screenW, screenH, 32, SDL_SWSURFACE || SDL_DOUBLEBUF);

#ifdef _DEBUG
    if (buffer == NULL)
    {
        fprintf(stderr, "Main surface could not be initialized!\n");
    }
    else
    {
        fprintf(stdout, "Main surface initialized properly!\n\n");
    }
#endif
    SDL_WM_SetCaption(programName.c_str(), NULL);
	SDL_WM_SetIcon(SDL_LoadBMP("data/gol.bmp"), NULL);
}

System::~System()
{
    SDL_FreeSurface(buffer);
}

void System::LoadConfig()
{
    ifstream infile;
    infile.open("config.txt");
    if (infile.fail())
    {
#ifdef _DEBUG
		cout << "No config file found. Creating new.\n";
#endif
		ofstream outfile;
		outfile.open("config.txt");
		screenW = 800; screenH = 640; tileSize = 12;
		outfile << "Screen_W: " << screenW << "\n";
		outfile << "Screen_H: " << screenH << "\n";
		outfile << "Tile_size: " << tileSize << "\n";
#ifdef _DEBUG
		cout << "Config file successfully created.\n";
#endif
		outfile.close();
    }

	else
	{
	    string temp;
		while (infile >> temp)
		{
			if  (!temp.compare("Screen_W:"))
				infile >> screenW;
			else if  (!temp.compare("Screen_H:"))
				infile >> screenH;
			else if  (!temp.compare("Tile_size:"))
				infile >> tileSize;
		}
#ifdef _DEBUG
		cout << "Config file found and loaded.\n";
#endif
	}
	borderSize = 28;
	if (tileSize > 0) {
		mapW = (screenW - borderSize * 2) / tileSize;
		mapH = (screenH - borderSize * 2) / tileSize; }
	else exit(-3);
}

