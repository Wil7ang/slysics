/*
 * src/Core/Rendering/TTFFont.h
 *
 * Copyright (C) 2011 Wilson Tang.
 *
 * This file is part of Slysics and is free software, distributed,
 * and licensed under the GNU General Public License, version 3.
 *
 * You should have received a copy of the GNU General Public License.
 * If not, see <http://www.gnu.org/licenses/gpl-3.0.html>.
*/

#ifndef TTFFONT_H
#define TTFFONT_H

#include "SDL/SDL_ttf.h"
#include <string>

#define FONT_FILE "/usr/share/fonts/truetype/freefont/FreeSans.ttf"


using namespace std;

class TTFFont
{
	public:
		TTFFont();
		TTFFont( string FILENAME, int size );
		~TTFFont();

		int LoadFont( string FILENAME, int size );
		int GetFontSize();
		SDL_Surface *BuildText( string text, SDL_Color textColor );
		void GetStringSurfaceSize( string text, int *w, int *h );
	private:
		TTF_Font *font;
		int fontSize;
};

#endif
