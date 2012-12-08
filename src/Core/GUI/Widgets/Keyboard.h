/*
 * src/Core/GUI/Widgets/Keyboard.h
 *
 * Copyright (C) 2011 Wilson Tang.
 *
 * This file is part of Slysics and is free software, distributed,
 * and licensed under the GNU General Public License, version 3.
 *
 * You should have received a copy of the GNU General Public License.
 * If not, see <http://www.gnu.org/licenses/gpl-3.0.html>.
*/

#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "SDL/SDL.h"
#include "SDL/SDL_gfxPrimitives.h"
#include "../../Rendering/TTFFont.h"
#include "../../Rendering/TextLabel.h"

class Keyboard
{
	public:
		Keyboard();
		~Keyboard();

		void InitKeyboard();

		string ProcessEvents(SDL_Event *event);
		void Render(SDL_Surface *surface);

		void SetVisibility(bool in);
		bool GetVisibility();
		string GetText();

		void ClearText();

	private:
		bool visibility;
		TTFFont fontSans32;
		TextLabel keys[37];
		TextLabel typedText;
		int mouseX;
		int mouseY;
		int mCurX;
		int mCurY;

		string text;
};

#endif
