/*
 * src/Game/LoadMenu.cpp
 *
 * Copyright (C) 2011 Wilson Tang.
 *
 * This file is part of Slysics and is free software, distributed,
 * and licensed under the GNU General Public License, version 3.
 *
 * You should have received a copy of the GNU General Public License.
 * If not, see <http://www.gnu.org/licenses/gpl-3.0.html>.
*/

#include "LoadMenu.h"
#include "SDL/SDL_gfxPrimitives.h"
#include <ftw.h>
#include <fnmatch.h>
#include <iostream>
#include <fstream>
#include <algorithm>

LoadMenu *loadMenu = NULL;

LoadMenu::LoadMenu()
{
	visibility = false;
	gCanvas = NULL;
	loadMenu = this;
	selection = 0;
	//imageVisibility = true;
	//tImage = NULL;
}

LoadMenu::~LoadMenu()
{
	gCanvas = NULL;
	spawn = NULL;

	//if ( tImage )
	//	delete tImage;

	//tImage = NULL;
}

void LoadMenu::SetupMenu( GameCanvas *gCanv, Spawn *spwn )
{
	gCanvas = gCanv;
	spawn = spwn;

	fontSans20.LoadFont( FONT_FILE, 42 );
}

void LoadMenu::LoadMap()
{
	gCanvas->ClearCanvas();
	gCanvas->ClearTraceLines();

	std::string line;
	std::ifstream mapFile ( mapFileNames[selection].c_str() );
	if ( mapFile.is_open() )
	{
		mapFile >> spawn->spawnPosition.x;
		spawn->spawnPosition.prevX = spawn->spawnPosition.x;
		mapFile >> spawn->spawnPosition.y;
		spawn->spawnPosition.prevY = spawn->spawnPosition.y;
		mapFile >> spawn->angle;
		mapFile >> spawn->initialVelocity.vel;
		while ( ! mapFile.eof() )
		{
			int pX, pY, x, y, srOx, srOy, type;
			mapFile >> pX;
			mapFile >> pY;
			mapFile >> x;
			mapFile >> y;
			mapFile >> srOx;
			mapFile >> srOy;
			mapFile >> type;
			gCanvas->CreateLine( pX, pY, x, y, srOx, srOy, type );
		}
		mapFile.close();
	}
	else
		printf( "Oh crap, I failed to find or open the file!\n" );

}

void LoadMenu::InputEvents( SDL_Event *event )
{
	if ( event->type == SDL_MOUSEBUTTONDOWN )
	{
		if ( event->button.x > 10 && event->button.x < 50 && event->button.y > SCREEN_HEIGHT/2 - 25 && event->button.y < SCREEN_HEIGHT/2 + 25 )
		{
			if ( selection > 0 )
			{
				selection--;
				SDL_Color textColor = { 0, 0, 0 };
				filenameLabel.SetText( &fontSans20, TEXTALIGNCENTER, TEXTALIGNCENTER, mapFileNames[selection], textColor );
				filenameLabel.SetPosition( SCREEN_WIDTH/2, SCREEN_HEIGHT/2 );
				//if ( tImage )
				//	delete tImage;
				//tImage = new ImageObject( mapsList[selection].second );
			}
		}

		if ( event->button.x > 55 && event->button.x < SCREEN_WIDTH - 55 && event->button.y < SCREEN_HEIGHT - 80 )
		{
			if ( mapFileNames.size() > 0 )
			{
				//imageVisibility = false;
				LoadMap();
			}
		}

		if ( event->button.x >SCREEN_WIDTH - 50 && event->button.x < SCREEN_WIDTH - 10 && event->button.y > SCREEN_HEIGHT/2 - 25 && event->button.y <SCREEN_HEIGHT/2 + 25 )
		{
			if ( selection < mapFileNames.size() - 1 && mapFileNames.size() > 0 )
			{
				selection++;
				SDL_Color textColor = { 0, 0, 0 };
				filenameLabel.SetText( &fontSans20, TEXTALIGNCENTER, TEXTALIGNCENTER, mapFileNames[selection], textColor );
				filenameLabel.SetPosition( SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
				//if ( tImage )
				//	delete tImage;
				//tImage = new ImageObject( mapsList[selection].second );
			}
		}

		if (event->button.x > 80+64*8 && event->button.x < 80+64*9 && event->button.y > SCREEN_HEIGHT- 64 )
		{
			if ( mapFileNames.size() > 0 )
			{
				string command = "rm " + mapFileNames[selection];
				FILE* tPopenFile = popen( command.c_str(), "r" );
				pclose( tPopenFile );
				mapFileNames.erase(mapFileNames.begin()+selection);

				selection--;

				if ( selection < 0 )
					selection = 0;

				if ( mapFileNames.size() > 0 )
				{
					std::sort( mapFileNames.begin(), mapFileNames.end() );
					SDL_Color textColor = { 0, 0, 0 };
					filenameLabel.SetText( &fontSans20, TEXTALIGNCENTER, TEXTALIGNCENTER, mapFileNames[selection], textColor );
					filenameLabel.SetPosition( SCREEN_WIDTH/2,SCREEN_HEIGHT/2 );
				}
				else
				{
					std::sort( mapFileNames.begin(), mapFileNames.end() );
					SDL_Color textColor = { 0, 0, 0 };
					filenameLabel.SetText( &fontSans20, TEXTALIGNCENTER, TEXTALIGNCENTER, "No maps available.", textColor );
					filenameLabel.SetPosition( SCREEN_WIDTH/2, SCREEN_HEIGHT/2 );
				}
			}
		}
	}
}

void LoadMenu::RenderMenu( SDL_Surface *surface )
{
	if ( visibility )
	{
		if ( selection < 0 )
			selection = 0;
		if ( selection > mapFileNames.size() - 1 )
			selection = mapFileNames.size() - 1;

		Sint16 xVerts[3] = { 10, 50, 50 };
		Sint16 yVerts[3] = { SCREEN_HEIGHT/2, SCREEN_HEIGHT/2 + 25, SCREEN_HEIGHT/2 - 25 };
		filledPolygonRGBA( surface, xVerts, yVerts, 3, 0, 0, 0, 255 );

		Sint16 xVerts2[3] = { SCREEN_WIDTH - 10, SCREEN_WIDTH - 50, SCREEN_WIDTH - 50 };
		Sint16 yVerts2[3] = { SCREEN_HEIGHT/2,SCREEN_HEIGHT/2 + 25, SCREEN_HEIGHT/2- 25 };
		filledPolygonRGBA( surface, xVerts2, yVerts2, 3, 0, 0, 0, 255 );

		filenameLabel.Render( surface );
	}
}

void LoadMenu::SetVisible( bool in )
{
	visibility = in;
}

bool LoadMenu::isVisible()
{
	return visibility;
}

void LoadMenu::FindFiles()
{
	mapFileNames.clear();

	string path = getenv( "HOME" );
	path = path + "/.slysics/maps";
	ftw( path.c_str(), LoadMenu::FoundFile, 1 );

	if ( mapFileNames.size() > 0 )
	{
		std::sort( mapFileNames.begin(), mapFileNames.end() );
		SDL_Color textColor = { 0, 0, 0 };
		filenameLabel.SetText( &fontSans20, TEXTALIGNCENTER, TEXTALIGNCENTER, mapFileNames[selection], textColor );
		filenameLabel.SetPosition( SCREEN_WIDTH/2, SCREEN_HEIGHT/2 );
	}
	else
	{
		SDL_Color textColor = { 0, 0, 0 };
		filenameLabel.SetText( &fontSans20, TEXTALIGNCENTER, TEXTALIGNCENTER, "No maps available.", textColor );
		filenameLabel.SetPosition( SCREEN_WIDTH/2, SCREEN_HEIGHT/2 );
	}
}

int LoadMenu::FoundFile( const char *fpath, const struct stat *sb, int typeflag )
{
	if ( typeflag == FTW_F )
	{
		if ( fnmatch( "*.map", fpath, FNM_CASEFOLD ) == 0 )
		{
			loadMenu->mapFileNames.push_back( fpath );
		}
	}
	return 0;
}

