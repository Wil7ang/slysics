/*
 * src/Game/Line.h
 *
 * Copyright (C) 2011 Wilson Tang.
 *
 * This file is part of Slysics and is free software, distributed,
 * and licensed under the GNU General Public License, version 3.
 *
 * You should have received a copy of the GNU General Public License.
 * If not, see <http://www.gnu.org/licenses/gpl-3.0.html>.
*/

#ifndef LINE_H
#define LINE_H

#include <Box2D/Box2D.h>
#include "SDL/SDL.h"

struct SaveData
{
	void Set( int pX_, int pY_, int x_, int y_, int srOx_, int srOy_, int type_ )
	{
		pX = pX_;
		pY = pY_;
		x = x_;
		y = y_;
		srOx = srOx_;
		srOy = srOy_;
		type = type_;
	}
	int pX;
	int pY;
	int x;
	int y;
	int srOx;
	int srOy;
	int type;
};

struct Line
{
	Line();
	~Line();

	SDL_Rect lineBox;

	SDL_Surface *lineSurface;

	b2PolygonShape lineShape;
	b2FixtureDef lineFixtureDef;
	b2Fixture *lineFixture;
	b2Body *lineBody;
	b2BodyDef lineBodyDef;

	int type;

	SaveData lineSaveData;

	int lineX1;
	int lineX2;
	int lineY1;
	int lineY2;
};

struct TraceLine
{
	TraceLine();
	~TraceLine();

	SDL_Rect lineBox;

	SDL_Surface *lineSurface;
};

#endif
