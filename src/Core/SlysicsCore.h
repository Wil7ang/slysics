/*
 * src/Game/SlysicsCore.h
 *
 * Copyright (C) 2011 Wilson Tang.
 *
 * This file is part of Slysics and is free software, distributed,
 * and licensed under the GNU General Public License, version 3.
 *
 * You should have received a copy of the GNU General Public License.
 * If not, see <http://www.gnu.org/licenses/gpl-3.0.html>.
*/

#ifndef SLYSICSCORE_H
#define SLYSICSCORE_H

#include "Rendering/RenderingCore.h"
#include "Rendering/ImageObject.h"
#include "Rendering/TTFFont.h"
#include "Rendering/TextLabel.h"
#include "Physics/PhysicsCore.h"
#include "System/TimerCore.h"
#include "System/ConfigurationCore.h"
#include "../Game/FlagManager.h"
#include "../Game/GameCanvas.h"
#include "../Game/ConfigurationMenu.h"
#include "../Game/LoadMenu.h"
#include "../Game/Portal.h"

#define FALL_OFF_FORCE 120.0f
#define HAT_FALL_OFF_FORCE 10.0f
#define RED_LINE_ACCELERATION_IMPULSE 15.0f
#define RED_LINE_MAX_AVERAGE_LINEAR_VELOCITY 1000.0f
#define TAN_LINE_DECELERATION_FACTOR 2.0f
#define TAN_LINE_MIN_AVERAGE_LINEAR_VELOCITY 0.5f
#define MAX_SLEDCRUSH_VELOCITY_CHANGE 100.0f
#define ALLOW_SIM_TIME_CHANGE 0
#define INITIAL_VEL_FACTOR 1.0f

struct SledderBodyVectors
{
	VectorPosFloat body;
	VectorPosFloat head;
	VectorPosFloat hat;
	VectorPosFloat arm;
	VectorPosFloat leg;
	VectorVelFloat bodyVel;
	VectorVelFloat headVel;
	VectorVelFloat hatVel;
	VectorVelFloat armVel;
	VectorVelFloat legVel;
};

class SlysicsCore
{
	public:
		SlysicsCore();
		~SlysicsCore();

		int InitializeSlysicsCore();

		void SlysicsMainLoop();
	private:
		void Events();
		void Trace();
		void ProcessUIClick( int x, int y );
		void Render();
		void SledderCrashProcess();
		void ProcessOutsideWorld();
		void ProcessTimers();
		void ProcessLines();
		void UpdateVariables();

		void ProcessPortals();

		Portal lastPortal;


		RenderingCore renderingCore;
		PhysicsCore physicsCore;
		TimerCore timerCore;
		ConfigurationCore configCore;
		GameCanvas gameCanvas;
		FlagManager flagManager;
		PortalManager portalManager;


		Sled sledObject;
		Sledder sledderObject;
		Spawn spawn;
		SledderBodyVectors sledderBodyVectors;

		//Bools
		bool stopped;
		bool paused;
		bool mouseDown;
		bool moveSpawn;
		bool setSpawnRotation;
		bool quit;
		bool fallenOff;
		bool hatOff;
		bool headOff;
		bool armOff;
		bool legOff;
		bool exploded;
		bool lineToolPressed;
		bool flagged;

		bool portalToolPressed;

		bool scrollLeft;
		bool scrollRight;
		bool scrollUp;
		bool scrollDown;

		bool flagMode;

		//Ints
		int toolSelection;
		int mousePreviousX;
		int mousePreviousY;
		int tOrigX;
		int tOrigY;
		int pencilLineType;
		int pencilPrevLineType;
		int lineToolLineType;
		int lineToolPrevLineType;
		int setSecondary;

		//Images for the 11 buttons in the UI
		ImageObject uiButtons[15];
		ImageObject toSpawnIcon;

		//SDL_Surface
		SDL_Surface *screenSurface;

		//SDL_Event
		SDL_Event inputEvents;

		//Timers
		Timer spawnRotationTimer;

		//VectorVelFloat
		VectorVelFloat sledVelocity;

		//VectorPosFloat
		VectorPosFloat sledPosition;

		//VectorPosInt
		VectorPosInt screenOffset;

		ConfigurationMenu configMenu;
		LoadMenu loadMenu;

		TTFFont fontSans12;
		TextLabel distanceToSpawnLabel;
		TextLabel distanceTraveledLabel;
};

#endif
