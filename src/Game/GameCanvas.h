/*
 * src/Game/GameCanvas.h
 *
 * Copyright (C) 2011 Wilson Tang.
 *
 * This file is part of Slysics and is free software, distributed,
 * and licensed under the GNU General Public License, version 3.
 *
 * You should have received a copy of the GNU General Public License.
 * If not, see <http://www.gnu.org/licenses/gpl-3.0.html>.
*/

#ifndef GAMECANVAS_H
#define GAMECANVAS_H

#include "Line.h"
#include "../Core/Physics/PhysicsCore.h"

#include "../Core/Rendering/RenderingCore.h"

#include "SDL/SDL.h"
#include "SDL/SDL_gfxPrimitives.h"

#define MAX_TRACE_LINES 100000
#define MIN_TRACE_LINE_LENGTH 30.0f

struct VectorPosInt
{
	VectorPosInt()
	{
		x = y = prevX = prevY = 0;
	}
	int x;
	int y;
	int prevX;
	int prevY;
};

struct VectorPosFloat
{
	VectorPosFloat()
	{
		x = y = prevX = prevY = 0.0f;
	}
	float x;
	float y;
	float prevX;
	float prevY;
};

struct VectorVelFloat
{
	VectorVelFloat()
	{
		vel = prevVel = 0.0f;
	}
	float vel;
	float prevVel;
};

struct Spawn
{
	VectorPosInt spawnPosition;
	ImageObject spawnImage;
	VectorVelFloat initialVelocity;
	float angle;
};

class GameCanvas
{
	public:
		GameCanvas();
		~GameCanvas();

		bool CreateLine( int pX, int pY, int x, int y, int srOx, int srOy, int type );
		void DestroyLine( int mX, int mY, int srOx, int srOy );

		void CreateTraceLine( int pX, int pY, int x, int y, int roy, int gee, int bib, int alp);

		void ClearCanvas();
		void ClearTraceLines();

		void SetPhysicsCore( PhysicsCore *pCore );
		void RenderCanvas( RenderingCore *rCore, int srOx, int srOy );
		void RenderTraceLines( RenderingCore *rCore, int srOx, int srOy );

		void SaveMap(string filename, int spawnX, int spawnY, float spawnAngle, float spawnVelocity);

		int GetClosestLineX(int x, int y, int srOx, int srOy);
		int GetClosestLineY(int x, int y, int srOx, int srOy);

		int GetNumberOfLines();
		int GetNumberOfTraceLines();

		float GetDistanceTraveled();
	private:
		PhysicsCore *physicsCore;
		vector<Line> linesList;
		vector<TraceLine> traceLinesList;

		float bodyDistanceTraveled;

};

#endif
