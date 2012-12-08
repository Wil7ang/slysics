/*
 * src/Slysics.cpp
 *
 * Copyright (C) 2011 Wilson Tang.
 *
 * This file is part of Slysics and is free software, distributed,
 * and licensed under the GNU General Public License, version 3.
 *
 * You should have received a copy of the GNU General Public License.
 * If not, see <http://www.gnu.org/licenses/gpl-3.0.html>.
*/

#include "Core/SlysicsCore.h"

int main()
{
	putenv("SDL_VIDEO_X11_WMCLASS=slysics");
	SlysicsCore lCore;
	if(lCore.InitializeSlysicsCore() == -1)
	{
		printf("Slysics failed to start!\n");
		return -1;
	}

	lCore.SlysicsMainLoop();
}
