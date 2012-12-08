/*
 * src/Core/Rendering/TextLabel.cpp
 *
 * Copyright (C) 2011 Wilson Tang.
 *
 * This file is part of Slysics and is free software, distributed,
 * and licensed under the GNU General Public License, version 3.
 *
 * You should have received a copy of the GNU General Public License.
 * If not, see <http://www.gnu.org/licenses/gpl-3.0.html>.
*/

#include "TextLabel.h"

TextLabel::TextLabel()
{
	textSurface = NULL;

}

TextLabel::~TextLabel()
{
	if ( textSurface )
		SDL_FreeSurface( textSurface );

	textSurface = NULL;
}

void TextLabel::Render( SDL_Surface *screen )
{
	if ( visibility )
	{
		blitRect = position;
		SDL_BlitSurface( textSurface, NULL, screen, &blitRect );
	}
}

void TextLabel::SetPosition( int xPos, int yPos )
{
	switch ( horizontalAlignment )
	{
		case TEXTALIGNLEFT:
			{
				position.x = xPos;
				break;
			}
		case TEXTALIGNRIGHT:
			{
				position.x = xPos - position.w;
				break;
			}
		case TEXTALIGNCENTER:
			{
				position.x = xPos - position.w / 2;
				break;
			}
	}
	switch ( verticalAlignment )
	{
		case TEXTALIGNTOP:
			{
				position.y = yPos;
				break;
			}
		case TEXTALIGNCENTER:
			{
				position.y = yPos - position.h/2;
				break;
			}
		case TEXTALIGNBOTTOM:
			{
				position.y = yPos - position.h;
				break;
			}
	}
}

void TextLabel::SetText( TTFFont *font, int hAlign, int vAlign, string text, SDL_Color color )
{
	if(textSurface)
		SDL_FreeSurface(textSurface);
	textSurface = font->BuildText( text, color );
	position.w = textSurface->w;
	position.h = textSurface->h;

	horizontalAlignment = hAlign;
	verticalAlignment = vAlign;
}
