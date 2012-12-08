/*
 * src/Core/Rendering/UpdateRectManager.cpp
 *
 * Copyright (C) 2011 Wilson Tang.
 *
 * This file is part of Slysics and is free software, distributed,
 * and licensed under the GNU General Public License, version 3.
 *
 * You should have received a copy of the GNU General Public License.
 * If not, see <http://www.gnu.org/licenses/gpl-3.0.html>.
*/

#include "UpdateRectManager.h"
#include "RenderingCore.h"

UpdateRectManager::UpdateRectManager()
{
	onFirstList = false;
}

UpdateRectManager::~UpdateRectManager()
{

}

void UpdateRectManager::AddUpdateRect(SDL_Rect rect)
{
	if( rect.x + rect.w > 0 && rect.x < SCREEN_WIDTH && rect.y + rect.h > 0 && rect.y < SCREEN_HEIGHT)
	{
		if( rect.x < 0 )
		{
			rect.w = rect.x + rect.w;
			rect.x = 0;
		}

		if( rect.x + rect.w > SCREEN_WIDTH )
		{
			rect.w = SCREEN_WIDTH - rect.x;
		}

		if( rect.y < 0 )
		{
			rect.h = rect.y + rect.h;
			rect.y = 0;
		}

		if( rect.y + rect.h > SCREEN_HEIGHT)
		{
			rect.h = SCREEN_HEIGHT - rect.y;
		}

		//if( rect.x != prevUpdateRectList[updateRectList.size()].x && rect.y != prevUpdateRectList[updateRectList.size()].y && rect.w != prevUpdateRectList[updateRectList.size()].w && rect.h != prevUpdateRectList[updateRectList.size()].h && !onFirstList )
			updateRectList.push_back(rect);

		if(onFirstList)
			prevUpdateRectList.push_back(rect);
	}
}

SDL_Rect *UpdateRectManager::GetUpdateRectList()
{
	return &updateRectList[0];
}

int UpdateRectManager::GetUpdateRectListSize()
{
	return int(updateRectList.size());
}

SDL_Rect *UpdateRectManager::GetPrevUpdateRectList()
{
	return &prevUpdateRectList[0];
}

int UpdateRectManager::GetPrevUpdateRectListSize()
{
	return int(prevUpdateRectList.size());
}

void UpdateRectManager::PushUpdateRectListToPrev()
{
	prevUpdateRectList.clear();
	prevUpdateRectList = updateRectList;
	updateRectList.clear();
}

bool UpdateRectManager::CheckUnique()
{
	if( sizeof(updateRectList) == sizeof(prevUpdateRectList) )
	{
		prevUpdateRectList.clear();

		return false;
	}

	return true;
}
