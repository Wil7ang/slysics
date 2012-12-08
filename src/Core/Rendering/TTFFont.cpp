/*
 * src/Core/Rendering/TTFFont.cpp
 *
 * Copyright (C) 2011 Wilson Tang.
 *
 * This file is part of Slysics and is free software, distributed,
 * and licensed under the GNU General Public License, version 3.
 *
 * You should have received a copy of the GNU General Public License.
 * If not, see <http://www.gnu.org/licenses/gpl-3.0.html>.
*/

#include "TTFFont.h"

TTFFont::TTFFont()
{
	font = NULL;
	fontSize = 12;
}

TTFFont::TTFFont( string FILENAME, int size )
{
	font = NULL;
	fontSize = 12;

	LoadFont( FILENAME, size );
}

TTFFont::~TTFFont()
{
	if(font != NULL)
		TTF_CloseFont( font );

	font = NULL;
}

int TTFFont::LoadFont( string FILENAME, int size )
{
	fontSize = size;
	font = TTF_OpenFont( FILENAME.c_str(), fontSize );
	if(!font)
		return -1;

	return 0;
}

int TTFFont::GetFontSize()
{
	return fontSize;
}

SDL_Surface *TTFFont::BuildText( string text, SDL_Color textColor )
{
	if(font)
		return TTF_RenderText_Blended( font, text.c_str(), textColor );

	return NULL;
}

void TTFFont::GetStringSurfaceSize( string text, int *w, int *h )
{
	if(font != NULL)
		TTF_SizeText(font, text.c_str(), w, h);
}
