/*
 * src/Core/GUI/Widgets/RadioButton.h
 *
 * Copyright (C) 2011 Wilson Tang.
 *
 * This file is part of Slysics and is free software, distributed,
 * and licensed under the GNU General Public License, version 3.
 *
 * You should have received a copy of the GNU General Public License.
 * If not, see <http://www.gnu.org/licenses/gpl-3.0.html>.
*/

#ifndef RADIOBUTTON_H
#define RADIOBUTTON_H

#include "SDL/SDL.h"
#include "SDL/SDL_gfxPrimitives.h"

class RadioButton
{
	public:
		RadioButton();
		~RadioButton();

		void ProcessEvents(SDL_Event *event);
		void SetPosition(int x, int y);
		void SetSize(int w, int h);
		void Render(SDL_Surface *surface);
		void SetValue(bool val);
		bool GetValue();
	private:
		bool value;
		SDL_Rect position;
		SDL_Rect blitRect;
};

#endif
