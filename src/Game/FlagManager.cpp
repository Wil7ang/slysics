/*
 * src/Game/FlagManager.cpp
 *
 * Copyright (C) 2011 Wilson Tang.
 *
 * This file is part of Slysics and is free software, distributed,
 * and licensed under the GNU General Public License, version 3.
 *
 * You should have received a copy of the GNU General Public License.
 * If not, see <http://www.gnu.org/licenses/gpl-3.0.html>.
*/

#include "FlagManager.h"

FlagManager::FlagManager()
{
    selection = 0;
}

FlagManager::~FlagManager()
{

}

void FlagManager::Initialize()
{
    flagImage.LoadImage("data/icon_flag.png");
}

void FlagManager::RenderFlags(RenderingCore *rCore, int srOx, int srOy)
{
    for ( unsigned int i = 0; i < flagsList.size(); i ++ )
	{
	    SDL_Rect imageBox;
	    imageBox.w = 64;
	    imageBox.h = 64;
	    imageBox.x = flagsList[i].sledPosition.x*10.0f-64/2+srOx;
	    imageBox.y = flagsList[i].sledPosition.y*10.0f-64/2+srOy;
		flagImage.SetPosition(flagsList[i].sledPosition.x*10.0f + srOx, flagsList[i].sledPosition.y*10.0f + srOy);

		//if ( flagsList[i].sledPosition.x + srOx + 64 > 0 && flagsList[i].sledPosition.x + srOx < SCREEN_WIDTH && flagsList[i].sledPosition.y + srOy + 64 > 0 && flagsList[i].sledPosition.y + srOy < SCREEN_HEIGHT )
		{
			flagImage.Render(rCore->ReturnScreenPointer());
			rCore->AppendUpdateRect(imageBox);
		}
	}
}

void FlagManager::RenderFlagMenu( SDL_Surface *surface )
{
    if ( selection < 0 )
        selection = 0;
    if ( selection > flagsList.size() - 1 )
        selection = flagsList.size() - 1;

    Sint16 xVerts[3] = { 10, 50, 50 };
    Sint16 yVerts[3] = { SCREEN_HEIGHT/2, SCREEN_HEIGHT/2 + 25, SCREEN_HEIGHT/2 - 25 };
    filledPolygonRGBA( surface, xVerts, yVerts, 3, 0, 0, 0, 255 );

    Sint16 xVerts2[3] = { SCREEN_WIDTH - 10, SCREEN_WIDTH - 50, SCREEN_WIDTH - 50 };
    Sint16 yVerts2[3] = { SCREEN_HEIGHT/2,SCREEN_HEIGHT/2 + 25, SCREEN_HEIGHT/2- 25 };
    filledPolygonRGBA( surface, xVerts2, yVerts2, 3, 0, 0, 0, 255 );
}

int FlagManager::GetFlagCount()
{
    return flagsList.size();
}

void FlagManager::AddFlag(float sledX, float sledY, float sledVelX, float sledVelY, float sledAngle)
{
	Flag temp;
	temp.angle = sledAngle;
	temp.sledPosition.Set(sledX, sledY);
	temp.sledVelocity.Set(sledVelX, sledVelY);

	flagsList.push_back(temp);
}

Flag FlagManager::GetCurrentFlag()
{
    return flagsList[selection];
}

void FlagManager::InputEvents( SDL_Event *event )
{
	if ( event->type == SDL_MOUSEBUTTONDOWN )
	{
		if ( event->button.x > 10 && event->button.x < 50 && event->button.y > SCREEN_HEIGHT/2 - 25 && event->button.y < SCREEN_HEIGHT/2 + 25 )
		{
			if ( selection > 0 )
			{
				selection--;

			}
		}

		if ( event->button.x >SCREEN_WIDTH - 50 && event->button.x < SCREEN_WIDTH - 10 && event->button.y > SCREEN_HEIGHT/2 - 25 && event->button.y <SCREEN_HEIGHT/2 + 25 )
		{
			if ( selection < flagsList.size() - 1 && flagsList.size() > 0 )
			{
				selection++;
				//if ( tImage )
				//	delete tImage;
				//tImage = new ImageObject( mapsList[selection].second );
			}
		}

		if ( event->button.x > 80+64*8 && event->button.x < 80+64*9 && event->button.y > SCREEN_HEIGHT- 64 )
		{
		    flagsList.clear();
		}
	}
}

void FlagManager::DelFlag(float xLoc, float yLoc)
{

}
