/*
 * src/Core/Rendering/TextLabel.h
 *
 * Copyright (C) 2011 Wilson Tang.
 *
 * This file is part of Slysics and is free software, distributed,
 * and licensed under the GNU General Public License, version 3.
 *
 * You should have received a copy of the GNU General Public License.
 * If not, see <http://www.gnu.org/licenses/gpl-3.0.html>.
*/

#ifndef TEXTLABEL_H
#define TEXTLABEL_H

#include <string>
#include "RenderObject.h"
#include "TTFFont.h"

using namespace std;

enum
{
	TEXTALIGNLEFT = 0,
	TEXTALIGNRIGHT,
	TEXTALIGNCENTER,
	TEXTALIGNTOP,
	TEXTALIGNBOTTOM
};

class TextLabel : public RenderObject
{
	public:
		TextLabel();
		~TextLabel();

		//Inherited from RenderObject
		void Render(SDL_Surface *screen);
		void SetPosition( int xPos, int yPos );

		void SetText( TTFFont *font, int hAlign, int vAlign, string text, SDL_Color color );
	private:
		SDL_Surface *textSurface;
		string stringText;
		SDL_Color textColor;

		int horizontalAlignment;
		int verticalAlignment;
};

#endif
