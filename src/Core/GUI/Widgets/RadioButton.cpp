/*
 * src/Core/GUI/Widgets/RadioButton.cpp
 *
 * Copyright (C) 2011 Wilson Tang.
 *
 * This file is part of Slysics and is free software, distributed,
 * and licensed under the GNU General Public License, version 3.
 *
 * You should have received a copy of the GNU General Public License.
 * If not, see <http://www.gnu.org/licenses/gpl-3.0.html>.
*/

#include "RadioButton.h"

RadioButton::RadioButton()
{
	value = false;
}

RadioButton::~RadioButton()
{

}

void RadioButton::SetPosition(int x, int y)
{
	position.x = x;
	position.y = y;
}

void RadioButton::SetSize(int w, int h)
{
	position.w = w;
	position.h = h;
}

void RadioButton::Render(SDL_Surface *screen)
{
	rectangleRGBA( screen, position.x, position.y, position.x + position.w, position.y + position.h, 255, 255, 255, 225);
	rectangleRGBA( screen, position.x+1, position.y+1, position.x + position.w -1, position.y + position.h -1, 255, 255, 255, 225);

	if(value)
	{
		boxRGBA( screen, position.x+3, position.y+3, position.x + position.w -3, position.y + position.h -3, 255, 255, 255, 225);
	}
}

void RadioButton::ProcessEvents(SDL_Event *event)
{
	if(event->button.x > position.x && event->button.x < position.x + position.w && event->button.y > position.y && event->button.y < position.y + position.h && event->type == SDL_MOUSEBUTTONDOWN)
	{
		if(value)
			value = false;
		else
			value = true;
	}
}

void RadioButton::SetValue(bool val)
{
	value = val;
}

bool RadioButton::GetValue()
{
	return value;
}
