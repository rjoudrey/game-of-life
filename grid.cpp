#include "grid.h"

Grid::Grid(SDL_Surface *surface)
{
    fileName = "map.txt";
	srcRect.x = dstRect.x = 0;
	srcRect.y = dstRect.y = 0;
	srcRect.w = dstRect.w = System::tileSize;
	srcRect.h = dstRect.h = System::tileSize;
	white = SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF);
	black = SDL_MapRGB(surface->format, 0, 0, 0);
	brushSize = 1; startX = startY = System::borderSize;
	showGrid = true;
	tile = new Tile*[System::mapW];
	for (int j = 0; j < System::mapW; j++)
	{
		tile[j] = new Tile[System::mapH];
	}
}

void Grid::FreeTiles()
{
    for (int i = 0; i < System::mapW; i++)
    {
        for (int j = 0; j < System::mapH; j++)
        {
            free(tile[i]);
            tile[i] = NULL;
        }
    }
    delete [] tile;
}

void Grid::Draw(SDL_Surface *surface)
{
	int x, y, orgX, orgY;
	orgX = orgY = x = y = 0;
    Uint8 pressed = SDL_GetMouseState(&orgX, &orgY);
	x = ((orgX - startX) / System::tileSize) * System::tileSize + startX;
	y = ((orgY - startY) / System::tileSize) * System::tileSize + startY;

	for (int i = 0; i < System::mapW; i++)
	{
		for (int j = 0; j < System::mapH; j++)
		{
			// Draw the "alive" tiles black
			if (!tile[i][j].IsDead())
			{
				SDL_Rect temp; 
				temp.x = i * System::tileSize + startX;
				temp.y = j * System::tileSize + startY;
				temp.w = temp.h = System::tileSize;
				SDL_FillRect(surface, &temp, 0x0);
			}

			// Box dimensions for the tiles
			srcRect.w = System::tileSize;
			srcRect.h = System::tileSize;
			srcRect.x = dstRect.x =  i * System::tileSize + startX;
			srcRect.y = dstRect.y =  j * System::tileSize + startY;

			// Drawing the grid			
			if (showGrid)
			{
				gridRect.x = dstRect.x;
				gridRect.y = dstRect.y;
				gridRect.w = 1;
				gridRect.h = System::tileSize;
				if (i == 0)
					SDL_FillRect(surface, &gridRect, white);
				else
					SDL_FillRect(surface, &gridRect, black);	

				gridRect.w = System::tileSize;
				gridRect.h = 1;
				if (j == 0)
					SDL_FillRect(surface, &gridRect, white);
				else
					SDL_FillRect(surface, &gridRect, black);

				gridRect.y = dstRect.y + System::tileSize;
				gridRect.w = System::tileSize;
				gridRect.h = 1;
				if (j == System::mapH - 1)
					SDL_FillRect(surface, &gridRect, white);
				else
					SDL_FillRect(surface, &gridRect, black);

				gridRect.x = dstRect.x + System::tileSize;
				gridRect.y = dstRect.y;
				gridRect.w = 1;
				gridRect.h = System::tileSize;
				if (i == System::mapW - 1)
					SDL_FillRect(surface, &gridRect, white);
				else
					SDL_FillRect(surface, &gridRect, black);
			}
		}
	}	

	if (brushSize == 1)
	{
		DrawHighlightedCell(surface, orgX, orgY, x, y);
	}
	else if (brushSize == 9)
	{
		if (x <System:: mapW * System::tileSize + startX && 
			y < System::mapH * System::tileSize + startY &&
			orgX >= startX && orgY >= startY)
			for (int h_x = -1; h_x < 2; h_x++)
				for (int h_y = -1; h_y < 2; h_y++)
					DrawHighlightedCell(surface, 
										orgX + h_x  * System::tileSize,
										orgY + h_y * System::tileSize,
										x + h_x * System::tileSize, 
										y + h_y * System::tileSize);
	}
}

void Grid::GetInput()
{
	int x, y, orgX, orgY;
	orgX = orgY = x = y = 0;
    Uint8 pressed = SDL_GetMouseState(&orgX, &orgY);
	x = ((orgX - startX) / System::tileSize);
	y = ((orgY - startY) / System::tileSize);

	if (x < System::mapW && y < System::mapH && 
		orgX >= startX && orgY >= startY)
	{
		if (pressed == SDL_BUTTON(SDL_BUTTON_LEFT))
		{
			if (brushSize == 1)
				SetTile(x, y, ALIVE); 
			else if (brushSize == 9)
			{
				for (int xOff = -1; xOff < 2; xOff++)
					for (int yOff = -1; yOff < 2; yOff++)
						SetTile(x + xOff, y + yOff, ALIVE);
			}
		}
		else if(pressed == SDL_BUTTON(SDL_BUTTON_RIGHT))
		{
			if (brushSize == 1)
				SetTile(x, y, DEAD);
			else if (brushSize == 9)
			{
				for (int xOff = -1; xOff < 2; xOff++)
					for (int yOff = -1; yOff < 2; yOff++)
						SetTile(x + xOff, y + yOff, DEAD);
			}
		}
	}
}

void Grid::Update()
{
	vector<Tile*> changeToAlive;
	vector<Tile*> changeToDead;

	for (int i = 0; i < System::mapW; i++) 
    {
        for (int j = 0; j < System::mapH; j++)
        {
			// Find the 8 eight neighboring tiles around the current tile
			vector<Tile*> neighbors;
			for (int n_i = -1; n_i < 2; n_i++)
				for (int n_j = -1; n_j < 2; n_j++)
					if (i + n_i >= 0 && j + n_j >= 0 && i + n_i < System::mapW && j + n_j < System::mapH)
					{
						if (n_i == 0 && n_j == 0)
							continue;
						else
							neighbors.push_back(&tile[i + n_i][j + n_j]);
					}

			// Find out how many alive neighbors the current tile has
			int numNeighbors = 0;
			for (Uint8 k = 0; k < neighbors.size(); k++)
				if (!neighbors[k]->IsDead())
					numNeighbors++;
			
			// Apply Conway's rules according to # of neighbors alive
			if ((numNeighbors < 2 || numNeighbors > 3) && !tile[i][j].IsDead())
				changeToDead.push_back(&tile[i][j]);
			else if (numNeighbors == 3 && tile[i][j].IsDead())
				changeToAlive.push_back(&tile[i][j]);
		}
	}
	// Apply changes
	for (Uint16 i = 0; i < changeToAlive.size(); i++)
		changeToAlive[i]->SetLife(ALIVE);
	for (Uint16 i = 0; i < changeToDead.size(); i++)
		changeToDead[i]->SetLife(DEAD);
}

void Grid::SetTile(int x, int y, LIFE_STATUS status)
{
	if (x >= 0 && y >= 0 && x < System::mapW && y < System::mapH)
			tile[x][y].SetLife(status);
}

void Grid::SaveMap()
{
#ifdef _DEBUG
	cout << "Saving to " << fileName.c_str() << "..." << endl;
#endif
    ofstream outfile;
    outfile.open(fileName.c_str());

    for (int i = 0; i < System::mapW; i++)  
    {
        for (int j = 0; j < System::mapH; j++)
			if (!tile[i][j].IsDead())
                outfile << ALIVE << " ";
			else
                outfile << DEAD << " ";
        outfile << endl;
    }

    outfile.close();
#ifdef _DEBUG
    cout << "Save complete\n" << endl;
#endif
}

void Grid::LoadMap()
{
#ifdef _DEBUG
    cout << "Loading from " << fileName << "..." << endl;
#endif
    ifstream infile;
    infile.open(fileName.c_str());
    string temp;
    for (int i = 0; i < System::mapW; i++)
    {
        for (int j = 0; j < System::mapH; j++)
        {
            int temp;
            infile >> temp;
			if (temp == ALIVE)
				tile[i][j].SetLife(ALIVE); 
			else tile[i][j].SetLife(DEAD);
        }
    }

    infile.close();
#ifdef _DEBUG
    cout << "Load complete\n" << endl;
#endif
}

void Grid::Clear()
{
	for (int i = 0; i < System::mapW; i++)
    {
        for (int j = 0; j < System::mapH; j++)
        {
			tile[i][j].SetLife(DEAD); 
        }
    }
}

void Grid::Fill()
{
	for (int i = 0; i < System::mapW; i++)
    {
        for (int j = 0; j < System::mapH; j++)
        {
			tile[i][j].SetLife(ALIVE); 
        }
    }
}

void Grid::DrawHighlightedCell(SDL_Surface *surface, int orgX, 
							   int orgY, int x, int y)
{
	if (x < System::mapW * System::tileSize + startX && 
		y < System::mapH * System::tileSize + startY &&
		orgX >= startX && orgY >= startY)

	{
		// Draw the white box around the tile the mouse is hovering over:
		// |
		gridRect.x = x;
		gridRect.y = y;
		gridRect.w = 1;
		gridRect.h = System::tileSize;
		SDL_FillRect(surface, &gridRect, white );
			
		//  -
		gridRect.w = System::tileSize;
		gridRect.h = 1;
		SDL_FillRect(surface, &gridRect, white);

		//   |
		gridRect.y = y + System::tileSize;
		gridRect.w = System::tileSize;
		gridRect.h = 1;
		SDL_FillRect(surface, &gridRect, white);

		//  _
		gridRect.x = x + System::tileSize;
		gridRect.y = y;
		gridRect.w = 1;
		gridRect.h = System::tileSize;
		SDL_FillRect(surface, &gridRect, white);
	}
}