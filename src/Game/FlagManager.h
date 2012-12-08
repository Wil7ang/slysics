/*
 * src/Game/FlagManager.h
 *
 * Copyright (C) 2011 Wilson Tang.
 *
 * This file is part of Slysics and is free software, distributed,
 * and licensed under the GNU General Public License, version 3.
 *
 * You should have received a copy of the GNU General Public License.
 * If not, see <http://www.gnu.org/licenses/gpl-3.0.html>.
*/

#ifndef FLAGMANAGER_H
#define FLAGMANAGER_H

#include "SDL/SDL.h"
#include "../Core/Rendering/RenderingCore.h"
#include "../Core/Rendering/ImageObject.h"
#include <Box2D/Box2D.h>
#include <vector>

using std::vector;

struct Flag
{
	float angle;
	b2Vec2 sledPosition;
	b2Vec2 sledVelocity;
};

class FlagManager
{
	public:
		FlagManager();
		~FlagManager();

		void Initialize();

		void AddFlag(float sledX, float sledY, float sledVelX, float sledVelY, float sledAngle);
		void DelFlag(float xLoc, float yLoc);
		void SelectFlagAt(float xLoc, float yLoc);
		void SelectFlag(int ID);
		Flag GetFlagAt(float xLoc, float yLoc);
		Flag GetFlag(int ID);
		int GetFlagCount();
		Flag GetCurrentFlag();

		void RenderFlags(RenderingCore *rCore, int srOx, int srOy);
		void RenderFlagMenu(SDL_Surface *screen);
		void InputEvents( SDL_Event *event );


	private:
		vector<Flag> flagsList;
		ImageObject flagImage;
		int selection;

};

#endif
