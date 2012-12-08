/*
 * src/Core/GUI/Widgets/Keyboard.cpp
 *
 * Copyright (C) 2011 Wilson Tang.
 *
 * This file is part of Slysics and is free software, distributed,
 * and licensed under the GNU General Public License, version 3.
 *
 * You should have received a copy of the GNU General Public License.
 * If not, see <http://www.gnu.org/licenses/gpl-3.0.html>.
*/

#include "Keyboard.h"
#include <string>

std::string charArray[] =
{
	"1", "2", "3", "4", "5", "6", "7", "8", "9", "0",
	"Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P",
	"A", "S", "D", "F", "G", "H", "J", "K", "L", "-",
	"Z", "X", "C", "V", "B", "N", "M",
	"q", "w", "e", "r", "t", "y", "u", "i", "o", "p",
	"a", "s", "d", "f", "g", "h", "j", "k", "l", "-",
	"z", "x", "c", "v", "b", "n", "m"
};

Keyboard::Keyboard()
{
	visibility = false;
	mouseX = -1;
	mouseY = -1;
	mCurX = -1;
	mCurY = -1;
	text = "";
}

Keyboard::~Keyboard()
{

}

void Keyboard::InitKeyboard()
{
#ifndef MAEMO
	fontSans32.LoadFont( "data/DejaVuSans.ttf", 42 );
#else
	fontSans32.LoadFont( "/usr/share/fonts/nokia/nosnr.ttf", 32 );
#endif

	SDL_Color textColor = { 255, 255, 255 };
	for ( int i = 0; i < 37; i++ )
	{
		keys[i].SetText( &fontSans32, TEXTALIGNCENTER, TEXTALIGNCENTER, charArray[i], textColor );
	}
}

void Keyboard::SetVisibility( bool in )
{
	visibility = in;
}

bool Keyboard::GetVisibility()
{
	return visibility;
}

void Keyboard::ClearText()
{
	text = "";
	SDL_Color textColor = { 255, 255, 255 };
	typedText.SetText( &fontSans32, TEXTALIGNCENTER, TEXTALIGNCENTER, " ", textColor );
}

void Keyboard::Render( SDL_Surface *screen )
{
	boxRGBA( screen, 0, 0, 800, 480, 0, 0, 0, 255 );
	int i = 0;
	for ( int h = 0; h < 800; h += 80 )
	{

		boxRGBA( screen, h + 2, 80 + 80 + 2, h + 80 - 2, 80 + 80 + 80 - 2, 50, 50, 50, 255 );
		rectangleRGBA( screen, h + 2, 80 + 80 + 2, h + 80 - 2, 80 + 80 + 80 - 2, 100, 100, 100, 255 );
		rectangleRGBA( screen, h + 3, 80 + 80 + 3, h + 80 - 3, 80 + 80 + 80 - 3, 100, 100, 100, 255 );
		boxRGBA( screen, h + 2, 80 + 160 + 2, h + 80 - 2, 80 + 160 + 80 - 2, 50, 50, 50, 255 );
		rectangleRGBA( screen, h + 2, 80 + 160 + 2, h + 80 - 2, 80 + 160 + 80 - 2, 100, 100, 100, 255 );
		rectangleRGBA( screen, h + 3, 80 + 160 + 3, h + 80 - 3, 80 + 160 + 80 - 3, 100, 100, 100, 255 );
		keys[i].SetPosition( h + 40, 80 + 80 + 40 );
		keys[i].Render( screen );
		keys[i+10].SetPosition( h + 40, 80 + 160 + 40 );
		keys[i+10].Render( screen );
		i++;
	}
	for ( int h = 0; h < 800; h += 80 )
	{
		boxRGBA( screen, h + 2, 80 + 240 + 2, h + 80 - 2, 80 + 240 + 80 - 2, 50, 50, 50, 255 );
		rectangleRGBA( screen, h + 2, 80 + 240 + 2, h + 80 - 2, 80 + 240 + 80 - 2, 100, 100, 100, 255 );
		rectangleRGBA( screen, h + 3, 80 + 240 + 3, h + 80 - 3, 80 + 240 + 80 - 3, 100, 100, 100, 255 );
		keys[i+10].SetPosition( h + 40, 80 + 240 + 40 );
		keys[i+10].Render( screen );
		i++;
	}
	for ( int h = 0; h < 800; h += 80 )
	{
		boxRGBA( screen, h + 2, 80 + 320 + 2, h + 80 - 2, 80 + 320 + 80 - 2, 50, 50, 50, 255 );
		rectangleRGBA( screen, h + 2, 80 + 320 + 2, h + 80 - 2, 80 + 320 + 80 - 2, 100, 100, 100, 255 );
		rectangleRGBA( screen, h + 3, 80 + 320 + 3, h + 80 - 3, 80 + 320 + 80 - 3, 100, 100, 100, 255 );
	}

	for ( int h = 80; h < 800 - 160; h += 80 )
	{
		keys[i+10].SetPosition( h + 40, 80 + 320 + 40 );
		keys[i+10].Render( screen );
		i++;
	}
	typedText.SetPosition( 400, 80 );
	typedText.Render( screen );
}

string Keyboard::ProcessEvents( SDL_Event *event )
{
	int i = 0;
	if ( event->type == SDL_MOUSEBUTTONDOWN )
	{
		mouseX = event->button.x;
		mouseY = event->button.y;
	}

	if ( event->type == SDL_MOUSEMOTION )
	{
		mCurX = event->motion.x;
		mCurY = event->motion.y;
	}

	if ( event->type == SDL_MOUSEBUTTONUP )
	{
		if ( text.length() < 25 )
		{
			for ( int h = 0; h < 800; h += 80 )
			{
				if ( mouseX > h + 2 && mouseX < h + 80 - 2 && mouseY > 80 + 80 + 2 && mouseY < 80 + 80 + 80 - 2 )
					text += charArray[i];
				i++;
			}

			for ( int h = 0; h < 800; h += 80 )
			{
				if ( mouseX > h + 2 && mouseX < h + 80 - 2 && mouseY > 80 + 80 + 80 + 2 && mouseY < 80 + 80 + 80 + 80 - 2 && mCurY >= mouseY - 10 )
				{
					text += charArray[i+27];
				}
				else if ( mouseX > h + 2 && mouseX < h + 80 - 2 && mouseY > 80 + 80 + 80 + 2 && mouseY < 80 + 80 + 80 + 80 - 2 && mCurY <= mouseY - 10 )
				{
					text += charArray[i];
				}
				i++;
			}

			for ( int h = 0; h < 800; h += 80 )
			{
				if ( mouseX > h + 2 && mouseX < h + 80 - 2 && mouseY > 80 + 80 + 80 + 80 + 2 && mouseY < 80 + 80 + 80 + 80 + 80 - 2 && mCurY >= mouseY - 10 )
				{
					text += charArray[i+27];
				}
				else if ( mouseX > h + 2 && mouseX < h + 80 - 2 && mouseY > 80 + 80 + 80 + 80 + 2 && mouseY < 80 + 80 + 80 + 80 + 80 - 2 && mCurY <= mouseY - 10 )
				{
					text += charArray[i];
				}
				i++;
			}

			for ( int h = 80; h < 800 - 160; h += 80 )
			{
				if ( mouseX > h + 2 && mouseX < h + 80 - 2 && mouseY > 80 + 80 + 80 + 80 + 80 + 2 && mouseY < 80 + 80 + 80 + 80 + 80 + 80 - 2 && mCurY >= mouseY - 10 )
				{
					text += charArray[i+27];
				}
				else if ( mouseX > h + 2 && mouseX < h + 80 - 2 && mouseY > 80 + 80 + 80 + 80 + 80 + 2 && mouseY < 80 + 80 + 80 + 80 + 80 + 80 - 2 && mCurY <= mouseY - 10 )
				{
					text += charArray[i];
				}
				i++;
			}





		}
		if ( mouseX > 2 + 80*9 && mouseX < 80 + 80*9 - 2 && mouseY > 80 + 80 + 80 + 80 + 80 + 2 && mouseY < 80 + 80 + 80 + 80 + 80 + 80 - 2 && mCurY >= mouseY - 10 )
		{
			text = "";
			SetVisibility( false );
		}

		if ( text.length() > 0 )
		{
			if ( mouseX > 2 && mouseX < 80 - 2 && mouseY > 80 + 80 + 80 + 80 + 80 + 2 && mouseY < 80 + 80 + 80 + 80 + 80 + 80 - 2 && mCurY >= mouseY - 10 )
			{
				SetVisibility( false );
				return text;
			}
			if ( mouseX > 2 + 80*8 && mouseX < 80 + 80*8 - 2 && mouseY > 80 + 80 + 80 + 80 + 80 + 2 && mouseY < 80 + 80 + 80 + 80 + 80 + 80 - 2 && mCurY >= mouseY - 10 )
			{
				text.erase( text.length() - 1, 1 );
			}

			if ( text.length() > 0 )
			{
				SDL_Color textColor = { 255, 255, 255 };
				typedText.SetText( &fontSans32, TEXTALIGNCENTER, TEXTALIGNCENTER, text, textColor );
			}
			else
			{
				SDL_Color textColor = { 255, 255, 255 };
				typedText.SetText( &fontSans32, TEXTALIGNCENTER, TEXTALIGNCENTER, " ", textColor );
			}
		}
	}
	return "";
}

string Keyboard::GetText()
{
	return text;
}
