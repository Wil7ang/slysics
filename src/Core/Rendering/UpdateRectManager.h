/*
 * src/Core/Rendering/UpdateRectManager.h
 *
 * Copyright (C) 2011 Wilson Tang.
 *
 * This file is part of Slysics and is free software, distributed,
 * and licensed under the GNU General Public License, version 3.
 *
 * You should have received a copy of the GNU General Public License.
 * If not, see <http://www.gnu.org/licenses/gpl-3.0.html>.
*/

#ifndef UPDATERECTMANAGER_H
#define UPDATERECTMANAGER_H

#include "SDL/SDL.h"
#include <vector>

using std::vector;

class UpdateRectManager
{
	public:
		UpdateRectManager();
		~UpdateRectManager();

		void AddUpdateRect( SDL_Rect rct );
		SDL_Rect *GetUpdateRectList();
		int GetUpdateRectListSize();
		SDL_Rect *GetPrevUpdateRectList();
		int GetPrevUpdateRectListSize();

		void PushUpdateRectListToPrev();

		bool CheckUnique();
	private:
		vector<SDL_Rect> updateRectList;
		vector<SDL_Rect> prevUpdateRectList;

		bool onFirstList;
};

#endif
