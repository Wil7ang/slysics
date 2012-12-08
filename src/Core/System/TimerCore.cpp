/*
 * src/Core/System/TimerCore.cpp
 *
 * Copyright (C) 2011 Wilson Tang.
 *
 * This file is part of Slysics and is free software, distributed,
 * and licensed under the GNU General Public License, version 3.
 *
 * You should have received a copy of the GNU General Public License.
 * If not, see <http://www.gnu.org/licenses/gpl-3.0.html>.
*/

#include "TimerCore.h"

TimerCore::TimerCore()
{

}

TimerCore::~TimerCore()
{

}

void TimerCore::UpdateTimers()
{
	for( unsigned int i = 0; i < timersList.size(); i++ )
	{
		if( (SDL_GetTicks() - timersList[i]->startTime) >= timersList[i]->length )
		{
			timersList[i]->finished = true;
			timersList.erase(timersList.begin() + i);
		}
	}
}

void TimerCore::AddTimer(Timer *tmr)
{
	timersList.push_back(tmr);
	tmr->startTime = SDL_GetTicks();
}
