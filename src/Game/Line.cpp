/*
 * src/Game/Line.cpp
 *
 * Copyright (C) 2011 Wilson Tang.
 *
 * This file is part of Slysics and is free software, distributed,
 * and licensed under the GNU General Public License, version 3.
 *
 * You should have received a copy of the GNU General Public License.
 * If not, see <http://www.gnu.org/licenses/gpl-3.0.html>.
*/

#include "Line.h"

Line::Line()
{
	lineBox.x = 0;
	lineBox.y = 0;
	lineBox.w = 0;
	lineBox.h = 0;
	lineSurface = NULL;

	lineBody = NULL;

	type = 0;
}

Line::~Line()
{

}

TraceLine::TraceLine()
{
	lineBox.x = 0;
	lineBox.y = 0;
	lineBox.w = 0;
	lineBox.h = 0;
	lineSurface = NULL;
}

TraceLine::~TraceLine()
{

}
