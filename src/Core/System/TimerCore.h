/*
 * src/Core/System/TimerCore.h
 *
 * Copyright (C) 2011 Wilson Tang.
 *
 * This file is part of Slysics and is free software, distributed,
 * and licensed under the GNU General Public License, version 3.
 *
 * You should have received a copy of the GNU General Public License.
 * If not, see <http://www.gnu.org/licenses/gpl-3.0.html>.
*/

#ifndef TIMERCORE_H
#define TIMERCORE_H

#include "SDL/SDL.h"
#include <vector>

using std::vector;

struct Timer
{
	Timer()
	{
		startTime = -1.0f;
		finished = false;
	}
	~Timer() { }

	float GetETA()
	{
		return length - ( SDL_GetTicks() - startTime );
	}

	float GetElapsed()
	{
		return SDL_GetTicks() - startTime;
	}

	void SetTimer( float len )
	{
		length = len;
		finished = false;
		startTime = -1.0f;
	}

	bool GetStatus()
	{
		if(startTime != -1.0f)
			return finished;
		else
			return false;
	}

	void SnoozeTimer()
	{
		finished = false;
		startTime = -1.0f;
	}

	float startTime;
	float length;
	bool finished;
};

class TimerCore
{
	public:
		TimerCore();
		~TimerCore();

		void UpdateTimers();

		void AddTimer(Timer *tmr);
		void DelTimer();
	private:
		vector<Timer*> timersList;
};

#endif
