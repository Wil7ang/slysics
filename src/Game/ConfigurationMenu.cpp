/*
 * src/Game/ConfigurationMenu.cpp
 *
 * Copyright (C) 2011 Wilson Tang.
 *
 * This file is part of Slysics and is free software, distributed,
 * and licensed under the GNU General Public License, version 3.
 *
 * You should have received a copy of the GNU General Public License.
 * If not, see <http://www.gnu.org/licenses/gpl-3.0.html>.
*/

#include "ConfigurationMenu.h"
#include "SDL/SDL_gfxPrimitives.h"

ConfigurationMenu::ConfigurationMenu()
{
	visibility = false;
	cCore = NULL;
}

ConfigurationMenu::~ConfigurationMenu()
{
	cCore = NULL;
}

void ConfigurationMenu::SetupMenu( ConfigurationCore *cCore_ )
{
	cCore = cCore_;

    fontSans18.LoadFont( FONT_FILE, 18 );
	fontSans20.LoadFont( FONT_FILE, 20 );
	fontSans32.LoadFont( FONT_FILE, 32 );

	SDL_Color textColor = { 255, 255, 255 };

	dialogTitleLabel.SetText( &fontSans32, TEXTALIGNCENTER, TEXTALIGNTOP, "Configuration", textColor );
	dialogTitleLabel.SetPosition( 400, 480 / 2 - 150 + 4 );

	lineSnapLabel.SetText( &fontSans20, TEXTALIGNLEFT, TEXTALIGNTOP, "Snap to line ends", textColor );
	lineSnapLabel.SetPosition( 400 - 225, 480 / 2 - 150 + 50 + 150 );

	traceLinesLabel.SetText( &fontSans20, TEXTALIGNLEFT, TEXTALIGNTOP, "Trace Lines", textColor );
	traceLinesLabel.SetPosition( 400 - 225, 480 / 2 - 150 + 50 );

	traceLineBodyLabel.SetText( &fontSans18, TEXTALIGNLEFT, TEXTALIGNTOP, "Body", textColor );
	traceLineBodyLabel.SetPosition( 400 - 225 + 20, 480 / 2 - 150 + 50 + 22 );

	traceLineSledLabel.SetText( &fontSans18, TEXTALIGNLEFT, TEXTALIGNTOP, "Sled", textColor );
	traceLineSledLabel.SetPosition( 400 - 225 + 20, 480 / 2 - 150 + 50 + 22 + 20 );

	traceLineHatLabel.SetText( &fontSans18, TEXTALIGNLEFT, TEXTALIGNTOP, "Hat", textColor );
	traceLineHatLabel.SetPosition( 400 - 225 + 20, 480 / 2 - 150 + 50 + 22 + 40 );

	traceLineHeadLabel.SetText( &fontSans18, TEXTALIGNLEFT, TEXTALIGNTOP, "Head", textColor );
	traceLineHeadLabel.SetPosition( 400 - 225 + 20, 480 / 2 - 150 + 50 + 22 + 60 );

	traceLineArmLabel.SetText( &fontSans18, TEXTALIGNLEFT, TEXTALIGNTOP, "Arm", textColor );
	traceLineArmLabel.SetPosition( 400 - 225 + 20, 480 / 2 - 150 + 50 + 22 + 80 );

	traceLineLegLabel.SetText( &fontSans18, TEXTALIGNLEFT, TEXTALIGNTOP, "Leg", textColor );
	traceLineLegLabel.SetPosition( 400 - 225 + 20, 480 / 2 - 150 + 50 + 22 + 100 );

	traceLineBodyRadio.SetPosition( 400 - 225 + 20 + 100, 480 / 2 - 150 + 50 + 22 + 1 );
	traceLineBodyRadio.SetSize( 16, 16 );
	traceLineBodyRadio.SetValue( cCore->GetVars().traceLine_body );

	traceLineSledRadio.SetPosition( 400 - 225 + 20 + 100, 480 / 2 - 150 + 50 + 22 + 3 + 20 );
	traceLineSledRadio.SetSize( 16, 16 );
	traceLineSledRadio.SetValue( cCore->GetVars().traceLine_sled );

	traceLineHatRadio.SetPosition( 400 - 225 + 20 + 100, 480 / 2 - 150 + 50 + 22 + 3 + 40 );
	traceLineHatRadio.SetSize( 16, 16 );
	traceLineHatRadio.SetValue( cCore->GetVars().traceLine_hat );

	traceLineHeadRadio.SetPosition( 400 - 225 + 20 + 100, 480 / 2 - 150 + 50 + 22 + 3 + 60 );
	traceLineHeadRadio.SetSize( 16, 16 );
	traceLineHeadRadio.SetValue( cCore->GetVars().traceLine_head );

	traceLineArmRadio.SetPosition( 400 - 225 + 20 + 100, 480 / 2 - 150 + 50 + 22 + 3 + 80 );
	traceLineArmRadio.SetSize( 16, 16 );
	traceLineArmRadio.SetValue( cCore->GetVars().traceLine_arm );

	traceLineLegRadio.SetPosition( 400 - 225 + 20 + 100, 480 / 2 - 150 + 50 + 22 + 3 + 100 );
	traceLineLegRadio.SetSize( 16, 16 );
	traceLineLegRadio.SetValue( cCore->GetVars().traceLine_leg );

	lineSnapRadio.SetPosition( 400 - 225 + 250, 480 / 2 - 150 + 50 + 150+2 );
	lineSnapRadio.SetSize( 16, 16 );
	lineSnapRadio.SetValue( cCore->GetVars().snapToPreviousLine );
}

void ConfigurationMenu::InputEvents( SDL_Event *event )
{
	traceLineBodyRadio.ProcessEvents( event );
	traceLineSledRadio.ProcessEvents( event );
	traceLineHatRadio.ProcessEvents( event );
	traceLineHeadRadio.ProcessEvents( event );
	traceLineArmRadio.ProcessEvents( event );
	traceLineLegRadio.ProcessEvents( event );
	lineSnapRadio.ProcessEvents( event );
}

void ConfigurationMenu::RenderMenu( SDL_Surface *surface )
{
	if ( visibility )
	{
		boxRGBA( surface, 800 / 2 - 250, 480 / 2 - 150, 800 / 2 + 250, 480 / 2 + 150, 0, 0, 0, 255 );
		rectangleRGBA( surface, 800 / 2 - 250, 480 / 2 - 150, 800 / 2 + 250, 480 / 2 + 150, 255, 255, 255, 255 );
		rectangleRGBA( surface, 800 / 2 - 250 + 1, 480 / 2 - 150 + 1, 800 / 2 + 250 - 1, 480 / 2 + 150 - 1, 255, 255, 255, 255 );
		aalineRGBA( surface, 800 / 2 - 225, 480 / 2 - 100, 800 / 2 + 225, 480 / 2 - 100, 255, 255, 255, 200 );
		dialogTitleLabel.Render( surface );
		traceLinesLabel.Render( surface );
		traceLineBodyLabel.Render( surface );
		traceLineSledLabel.Render( surface );
		traceLineHatLabel.Render( surface );
		traceLineHeadLabel.Render( surface );
		traceLineArmLabel.Render( surface );
		traceLineLegLabel.Render( surface );

		traceLineBodyRadio.Render( surface );
		traceLineSledRadio.Render( surface );
		traceLineHatRadio.Render( surface );
		traceLineHeadRadio.Render( surface );
		traceLineArmRadio.Render( surface );
		traceLineLegRadio.Render( surface );

		lineSnapLabel.Render( surface );
		lineSnapRadio.Render( surface );
	}
}

void ConfigurationMenu::SetVisible( bool in )
{
	visibility = in;
	if ( in == false )
	{
		cCore->SetVariable( "traceLine_body", traceLineBodyRadio.GetValue() );
		cCore->SetVariable( "traceLine_sled", traceLineSledRadio.GetValue() );
		cCore->SetVariable( "traceLine_hat", traceLineHatRadio.GetValue() );
		cCore->SetVariable( "traceLine_head", traceLineHeadRadio.GetValue() );
		cCore->SetVariable( "traceLine_arm", traceLineArmRadio.GetValue() );
		cCore->SetVariable( "traceLine_leg", traceLineLegRadio.GetValue() );
		cCore->SetVariable( "snapToPreviousLine", lineSnapRadio.GetValue() );
		cCore->WriteConfigurationFile();
		cCore->UpdateVars();
	}
}

bool ConfigurationMenu::isVisible()
{
	return visibility;
}
