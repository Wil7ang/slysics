/*
 * src/Game/SlysicsCoreRender.cpp
 *
 * Copyright (C) 2011 Wilson Tang.
 *
 * This file is part of Slysics and is free software, distributed,
 * and licensed under the GNU General Public License, version 3.
 *
 * You should have received a copy of the GNU General Public License.
 * If not, see <http://www.gnu.org/licenses/gpl-3.0.html>.
*/

#include "SlysicsCore.h"
#include <sstream>

void SlysicsCore::Render()
{
	renderingCore.ClearScene();

	/*if ( guiKBoard.GetVisibility() )
	{
		guiKBoard.Render( screenSurface );
		renderingCore.AppendUpdateRect( 400 - 50, 80 - 16, 100, 32 );
		uiButtons[12].SetVisible( true );
		uiButtons[12].SetPosition( 40, 320 + 80 + 40 );
		uiButtons[12].Render( screenSurface );
		uiButtons[2].SetPosition( 40 + 80*8, 320 + 80 + 40 );
		uiButtons[2].Render( screenSurface );
		uiButtons[9].SetPosition( 40 + 80*9, 320 + 80 + 40 );
		uiButtons[9].Render( screenSurface );
	}*/
	//else
	{

		aalineRGBA( screenSurface, -50 + screenOffset.x, 0 + screenOffset.y, 50 + screenOffset.x, 0 + screenOffset.y, 0, 0, 0, 255 );
		aalineRGBA( screenSurface, 0 + screenOffset.x, -50 + screenOffset.y, 0 + screenOffset.x, 50 + screenOffset.y, 0, 0, 0, 255 );
		renderingCore.AppendUpdateRect( -51 + screenOffset.x, 0 + screenOffset.y, 102, 1 );
		renderingCore.AppendUpdateRect( 0 + screenOffset.x, -51 + screenOffset.y, 1, 102 );

		gameCanvas.RenderCanvas( &renderingCore, screenOffset.x, screenOffset.y );
		gameCanvas.RenderTraceLines( &renderingCore, screenOffset.x, screenOffset.y );
		flagManager.RenderFlags(&renderingCore, screenOffset.x, screenOffset.y);
		portalManager.RenderPortals(&renderingCore, screenOffset.x, screenOffset.y);

		if ( sledObject.created )
		{
			if ( sledObject.sledBody )
			{

				float centerX = sledObject.sledBody->GetPosition().x * 10.0f;
				float centerY = sledObject.sledBody->GetPosition().y * 10.0f;
				float angle = -sledObject.sledBody->GetAngle() * ( 180.0f / 3.14159f );

				if ( !sledObject.crumpled )
				{
					sledObject.sledImage.SetPosition( centerX + screenOffset.x, centerY + screenOffset.y );
					sledObject.sledImage.SetAngle( angle );
				}
				else
				{
					sledObject.sledCrumpledImage.SetPosition( centerX + screenOffset.x, centerY + screenOffset.y );
					sledObject.sledCrumpledImage.SetAngle( angle );
				}
			}

			{
				if ( sledderObject.sledderArmBody )
				{
					float armCenterX = sledderObject.sledderArmBody->GetPosition().x * 10.0f;
					float armCenterY = sledderObject.sledderArmBody->GetPosition().y * 10.0f;
					float armAngle = -sledderObject.sledderArmBody->GetAngle() * ( 180.0f / 3.14159f );
					sledderObject.armImage.SetPosition( armCenterX + screenOffset.x, armCenterY + screenOffset.y );
					sledderObject.armImage.SetAngle( armAngle );
				}
				if ( sledderObject.sledderLegBody )
				{
					float legCenterX = sledderObject.sledderLegBody->GetPosition().x * 10.0f;
					float legCenterY = sledderObject.sledderLegBody->GetPosition().y * 10.0f;
					float legAngle = -sledderObject.sledderLegBody->GetAngle() * ( 180.0f / 3.14159f );
					sledderObject.legImage.SetPosition( legCenterX + screenOffset.x, legCenterY + screenOffset.y );
					sledderObject.legImage.SetAngle( legAngle );
				}
				if ( sledderObject.sledderHeadBody )
				{
					float headCenterX = sledderObject.sledderHeadBody->GetPosition().x * 10.0f;
					float headCenterY = sledderObject.sledderHeadBody->GetPosition().y * 10.0f;
					float headAngle = -sledderObject.sledderHeadBody->GetAngle() * ( 180.0f / 3.14159f );
					sledderObject.headImage.SetPosition( headCenterX + screenOffset.x, headCenterY + screenOffset.y );
					sledderObject.headImage.SetAngle( headAngle );
				}
				if ( sledderObject.sledderHatBody )
				{
					float hatCenterX = sledderObject.sledderHatBody->GetPosition().x * 10.0f;
					float hatCenterY = sledderObject.sledderHatBody->GetPosition().y * 10.0f;
					float hatAngle = -sledderObject.sledderHatBody->GetAngle() * ( 180.0f / 3.14159f );
					sledderObject.hatImage.SetPosition( hatCenterX + screenOffset.x, hatCenterY + screenOffset.y );
					sledderObject.hatImage.SetAngle( hatAngle );
				}
				if ( sledderObject.sledderBodyBody )
				{
					float bodyCenterX = sledderObject.sledderBodyBody->GetPosition().x * 10.0f;
					float bodyCenterY = sledderObject.sledderBodyBody->GetPosition().y * 10.0f;
					float bodyAngle = -sledderObject.sledderBodyBody->GetAngle() * ( 180.0f / 3.14159f );
					sledderObject.bodyImage.SetPosition( bodyCenterX + screenOffset.x, bodyCenterY + screenOffset.y );
					sledderObject.bodyImage.SetAngle( bodyAngle );
				}
			}
		}

		if ( spawn.spawnImage.GetVisible() )
		{
			spawn.spawnImage.SetPosition( spawn.spawnPosition.x + screenOffset.x, spawn.spawnPosition.y + screenOffset.y );
			float spawnRotationIconX = ( ( 0.0f * cos( double( spawn.angle + b2_pi / 2.0f ) ) ) - ( -37.0f * sin( double( spawn.angle + b2_pi / 2.0f ) ) ) ) + spawn.spawnPosition.x + screenOffset.x;
			float spawnRotationIconY = ( ( 0.0f * sin( double( spawn.angle + b2_pi / 2.0f ) ) ) + ( -37.0f * cos( double( spawn.angle + b2_pi / 2.0f ) ) ) ) + spawn.spawnPosition.y + screenOffset.y;
			filledCircleRGBA( screenSurface, spawnRotationIconX, spawnRotationIconY, 14, 100, 100, 100, 255 );

			if ( setSpawnRotation )
			{
				filledCircleRGBA( screenSurface, spawnRotationIconX, spawnRotationIconY, 7, 255, 0, 0, 255 );
				filledCircleRGBA( screenSurface, spawn.spawnPosition.x + screenOffset.x, spawn.spawnPosition.y + screenOffset.y, 20, 255, 0, 0, 100 );
			}
			else
				filledCircleRGBA( screenSurface, spawnRotationIconX, spawnRotationIconY, 7, 255, 255, 255, 255 );

			renderingCore.AppendUpdateRect( spawn.spawnPosition.x + screenOffset.x - 40, spawn.spawnPosition.y + screenOffset.y - 40, 80, 80 );
			renderingCore.AppendUpdateRect( spawnRotationIconX - 15, spawnRotationIconY - 15, 30, 30 );
		}

		int roy = 0;
		int gee = 0;
		int bib = 0;

		if ( lineToolLineType == 0 )
		{
			roy = 34;
			gee = 99;
			bib = 27;
		}
		else if ( lineToolLineType == 1 )
		{
			roy = 162;
			gee = 152;
			bib = 105;
		}
		else if ( lineToolLineType == 2 )
		{
			roy = 255;
			gee = 114;
			bib = 0;
		}

		if ( mouseDown && (toolSelection == 1 || toolSelection == 10))
		{
			lineRGBA( screenSurface, mousePreviousX    , mousePreviousY    , inputEvents.motion.x    , inputEvents.motion.y    , roy, gee, bib, 255 );
			aalineRGBA( screenSurface, mousePreviousX + 1, mousePreviousY + 1, inputEvents.motion.x + 1, inputEvents.motion.y + 1, roy, gee, bib, 255 );
			aalineRGBA( screenSurface, mousePreviousX + 1, mousePreviousY - 1, inputEvents.motion.x + 1, inputEvents.motion.y - 1, roy, gee, bib, 255 );
			lineRGBA( screenSurface, mousePreviousX + 1, mousePreviousY    , inputEvents.motion.x + 1, inputEvents.motion.y    , roy, gee, bib, 255 );
			aalineRGBA( screenSurface, mousePreviousX - 1, mousePreviousY + 1, inputEvents.motion.x - 1, inputEvents.motion.y + 1, roy, gee, bib, 255 );
			aalineRGBA( screenSurface, mousePreviousX - 1, mousePreviousY - 1, inputEvents.motion.x - 1, inputEvents.motion.y - 1, roy, gee, bib, 255 );
			lineRGBA( screenSurface, mousePreviousX - 1, mousePreviousY    , inputEvents.motion.x - 1, inputEvents.motion.y    , roy, gee, bib, 255 );
			lineRGBA( screenSurface, mousePreviousX    , mousePreviousY + 1, inputEvents.motion.x    , inputEvents.motion.y + 1, roy, gee, bib, 255 );
			lineRGBA( screenSurface, mousePreviousX    , mousePreviousY - 1, inputEvents.motion.x    , inputEvents.motion.y - 1, roy, gee, bib, 255 );

			int tW = abs( inputEvents.motion.x - mousePreviousX ) + 3;
			int tH = abs( inputEvents.motion.y - mousePreviousY ) + 3;
			int tX = 0;
			int tY = 0;

			if ( mousePreviousX < inputEvents.motion.x )
			{
				tX = mousePreviousX - 1;
			}
			else
			{
				tX = inputEvents.motion.x - 1;
			}

			if ( mousePreviousY < inputEvents.motion.y )
			{
				tY = mousePreviousY - 1;
			}
			else
			{
				tY = inputEvents.motion.y - 1;
			}

			renderingCore.AppendUpdateRect( tX, tY, tW, tH );
		}

		renderingCore.Draw();

		if ( ( paused || stopped ) && !loadMenu.isVisible() && !flagMode )
		{

			//Render the UI buttons
			rectangleRGBA( screenSurface, 80 + toolSelection * 64, SCREEN_HEIGHT - 64, 80 + toolSelection * 64 + 64, (SCREEN_HEIGHT-1), 0, 0, 0, 255 );
			rectangleRGBA( screenSurface, 80 + toolSelection * 64 + 1, SCREEN_HEIGHT - 64 + 1, 80 + toolSelection * 64 + 64 - 1, (SCREEN_HEIGHT-1) - 1, 0, 0, 0, 255 );
			rectangleRGBA( screenSurface, 80 + toolSelection * 64 + 2, SCREEN_HEIGHT - 64 + 2, 80 + toolSelection * 64 + 64 - 2, (SCREEN_HEIGHT-1) - 2, 0, 0, 0, 255 );
			rectangleRGBA( screenSurface, 80 + toolSelection * 64 + 3, SCREEN_HEIGHT - 64 + 3, 80 + toolSelection * 64 + 64 - 3, (SCREEN_HEIGHT-1) - 3, 0, 0, 0, 255 );

			switch ( pencilLineType )
			{
				case 0:
					{
						Sint16 xArray[3] = { 80 + 4, 80 + 4 + 20, 80 + 4 };
						Sint16 yArray[3] = { SCREEN_HEIGHT - 60 + 20, SCREEN_HEIGHT - 60, SCREEN_HEIGHT - 60 };
						filledPolygonRGBA( screenSurface, xArray, yArray, 3, 34, 99, 27, 150 );
						break;
					}
				case 1:
					{
						Sint16 xArray[3] = { 80 + 4, 80 + 4 + 20, 80 + 4 };
						Sint16 yArray[3] = { SCREEN_HEIGHT - 60 + 20, SCREEN_HEIGHT - 60, SCREEN_HEIGHT - 60 };
						filledPolygonRGBA( screenSurface, xArray, yArray, 3, 162, 152, 105, 150 );
						break;
					}
				case 2:
					{
						Sint16 xArray[3] = { 80 + 4, 80 + 4 + 20, 80 + 4 };
						Sint16 yArray[3] = { SCREEN_HEIGHT - 60 + 20, SCREEN_HEIGHT - 60, SCREEN_HEIGHT - 60 };
						filledPolygonRGBA( screenSurface, xArray, yArray, 3, 255, 114, 0, 150 );
						break;
					}
			}

			switch ( lineToolLineType )
			{
				case 0:
					{
						Sint16 xArray[3] = { 80 + 4 + 64, 80 + 4 + 20 + 64, 80 + 4 + 64 };
						Sint16 yArray[3] = { SCREEN_HEIGHT - 60 + 20, SCREEN_HEIGHT - 60, SCREEN_HEIGHT - 60 };
						filledPolygonRGBA( screenSurface, xArray, yArray, 3, 34, 99, 27, 150 );
						break;
					}
				case 1:
					{
						Sint16 xArray[3] = { 80 + 4 + 64, 80 + 4 + 20 + 64, 80 + 4 + 64 };
						Sint16 yArray[3] = { SCREEN_HEIGHT - 60 + 20, SCREEN_HEIGHT - 60, SCREEN_HEIGHT - 60 };
						filledPolygonRGBA( screenSurface, xArray, yArray, 3, 162, 152, 105, 150 );
						break;
					}
				case 2:
					{
						Sint16 xArray[3] = { 80 + 4 + 64, 80 + 4 + 20 + 64, 80 + 4 + 64 };
						Sint16 yArray[3] = { SCREEN_HEIGHT - 60 + 20, SCREEN_HEIGHT - 60, SCREEN_HEIGHT - 60 };
						filledPolygonRGBA( screenSurface, xArray, yArray, 3, 255, 114, 0, 150 );
						break;
					}
			}


			if ( setSecondary == 0 )
			{
				lineRGBA( screenSurface, 4*64 + 80 + 32 - 5, SCREEN_HEIGHT - 64 + 10, 4*64 + 80 + 32, SCREEN_HEIGHT - 64 + 5, 0, 0, 0, 255 );
				lineRGBA( screenSurface, 4*64 + 80 + 32 - 4, SCREEN_HEIGHT - 64 + 10, 4*64 + 80 + 32, SCREEN_HEIGHT - 64 + 6, 0, 0, 0, 255 );
				lineRGBA( screenSurface, 4*64 + 80 + 32 - 3, SCREEN_HEIGHT - 64 + 10, 4*64 + 80 + 32, SCREEN_HEIGHT - 64 + 7, 0, 0, 0, 255 );
				lineRGBA( screenSurface, 4*64 + 80 + 32, SCREEN_HEIGHT - 64 + 5, 4*64 + 80 + 32 + 5, SCREEN_HEIGHT - 64 + 10, 0, 0, 0, 255 );
				lineRGBA( screenSurface, 4*64 + 80 + 32, SCREEN_HEIGHT - 64 + 6, 4*64 + 80 + 32 + 4, SCREEN_HEIGHT - 64 + 10, 0, 0, 0, 255 );
				lineRGBA( screenSurface, 4*64 + 80 + 32, SCREEN_HEIGHT - 64 + 7, 4*64 + 80 + 32 + 3, SCREEN_HEIGHT - 64 + 10, 0, 0, 0, 255 );
			}
			if ( setSecondary == 1 )
			{
				//Setting initial velocity
				boxRGBA( screenSurface, 80 + 4*64 + 32 - 2, SCREEN_HEIGHT - 64 - 10 - 200, 80 + 4*64 + 32 + 2, SCREEN_HEIGHT - 64 - 10, 255, 114, 0, 100 );
				renderingCore.AppendUpdateRect( 80 + 4 * 64 + 32 - 2, SCREEN_HEIGHT - 64 - 10 - 200, 5, 201 );
				boxRGBA( screenSurface, 80 + 4*64, SCREEN_HEIGHT - 64 - 10 - 100 - 1, 80 + 4*64 + 64, SCREEN_HEIGHT - 64 - 10 - 100 + 1, 255, 114, 0, 100 );
				renderingCore.AppendUpdateRect( 80 + 4 * 64, SCREEN_HEIGHT - 64 - 10 - 100 - 1, 64, 4 );

				filledCircleRGBA( screenSurface, 80 + 4*64 + 32, (SCREEN_HEIGHT-480)+306 - spawn.initialVelocity.prevVel, 6, 255, 114, 0, 200 );
				renderingCore.AppendUpdateRect( 80 + 4 * 64 + 32 - 7, (SCREEN_HEIGHT-480)+306 - spawn.initialVelocity.prevVel - 7, 14, 14 );

				filledCircleRGBA( screenSurface, 80 + 4*64 + 32, (SCREEN_HEIGHT-480)+306 - spawn.initialVelocity.vel, 22, 255, 114, 0, 200 );
				filledCircleRGBA( screenSurface, 80 + 4*64 + 32, (SCREEN_HEIGHT-480)+306 - spawn.initialVelocity.vel, 11, 255, 255, 255, 200 );
				renderingCore.AppendUpdateRect( 80 + 4 * 64 + 32 - 23, (SCREEN_HEIGHT-480)+306 - spawn.initialVelocity.vel - 23, 46, 46 );

				boxRGBA( screenSurface, 80 + 4*64 + 64 - 8, SCREEN_HEIGHT - 64 - 10 - 200 + 3, 80 + 4*64 + 64, SCREEN_HEIGHT - 64 - 10 - 200 + 5, 255, 114, 0, 100 );
				boxRGBA( screenSurface, 80 + 4*64 + 64 - 5, SCREEN_HEIGHT - 64 - 10 - 200, 80 + 4*64 + 64 - 3, SCREEN_HEIGHT - 64 - 10 - 200 + 8, 255, 114, 0, 100 );
				renderingCore.AppendUpdateRect( 80 + 4 * 64 + 64 - 8, SCREEN_HEIGHT - 64 - 10 - 200, 10, 10 );

				boxRGBA( screenSurface, 80 + 4*64 + 64 - 8, SCREEN_HEIGHT - 64 - 10 - 5, 80 + 4*64 + 64, SCREEN_HEIGHT - 64 - 10 - 3, 255, 114, 0, 100 );
				renderingCore.AppendUpdateRect( 80 + 4 * 64 + 64 - 8, SCREEN_HEIGHT - 64 - 10 - 5, 10, 4 );

				aalineRGBA( screenSurface, 68 + 80 + 4*64, SCREEN_HEIGHT - 64 - 10 - 200, 68 + 80 + 4*64, SCREEN_HEIGHT - 64 - 10, 0, 0, 0, 50 );
				renderingCore.AppendUpdateRect( 68 + 80 + 4 * 64, SCREEN_HEIGHT - 64 - 10 - 200, 1, 200 );
			}
			else if ( setSecondary == 2 )
			{
				if ( toolSelection == 0 )
				{
					lineRGBA( screenSurface, 80 + 32 - 5, SCREEN_HEIGHT - 64 + 10, 80 + 32, SCREEN_HEIGHT - 64 + 5, 0, 0, 0, 255 );
					lineRGBA( screenSurface, 80 + 32 - 4, SCREEN_HEIGHT - 64 + 10, 80 + 32, SCREEN_HEIGHT - 64 + 6, 0, 0, 0, 255 );
					lineRGBA( screenSurface, 80 + 32 - 3, SCREEN_HEIGHT - 64 + 10, 80 + 32, SCREEN_HEIGHT - 64 + 7, 0, 0, 0, 255 );
					lineRGBA( screenSurface, 80 + 32, SCREEN_HEIGHT - 64 + 5, 80 + 32 + 5, SCREEN_HEIGHT - 64 + 10, 0, 0, 0, 255 );
					lineRGBA( screenSurface, 80 + 32, SCREEN_HEIGHT - 64 + 6, 80 + 32 + 4, SCREEN_HEIGHT - 64 + 10, 0, 0, 0, 255 );
					lineRGBA( screenSurface, 80 + 32, SCREEN_HEIGHT - 64 + 7, 80 + 32 + 3, SCREEN_HEIGHT - 64 + 10, 0, 0, 0, 255 );
				}
				else if ( toolSelection == 1 )
				{
					lineRGBA( screenSurface, 64 + 80 + 32 - 5, SCREEN_HEIGHT - 64 + 10, 64 + 80 + 32, SCREEN_HEIGHT - 64 + 5, 0, 0, 0, 255 );
					lineRGBA( screenSurface, 64 + 80 + 32 - 4, SCREEN_HEIGHT - 64 + 10, 64 + 80 + 32, SCREEN_HEIGHT - 64 + 6, 0, 0, 0, 255 );
					lineRGBA( screenSurface, 64 + 80 + 32 - 3, SCREEN_HEIGHT - 64 + 10, 64 + 80 + 32, SCREEN_HEIGHT - 64 + 7, 0, 0, 0, 255 );
					lineRGBA( screenSurface, 64 + 80 + 32, SCREEN_HEIGHT - 64 + 5, 64 + 80 + 32 + 5, SCREEN_HEIGHT - 64 + 10, 0, 0, 0, 255 );
					lineRGBA( screenSurface, 64 + 80 + 32, SCREEN_HEIGHT - 64 + 6, 64 + 80 + 32 + 4, SCREEN_HEIGHT - 64 + 10, 0, 0, 0, 255 );
					lineRGBA( screenSurface, 64 + 80 + 32, SCREEN_HEIGHT - 64 + 7, 64 + 80 + 32 + 3, SCREEN_HEIGHT - 64 + 10, 0, 0, 0, 255 );
				}
				else if ( toolSelection == 3 )
				{
					lineRGBA( screenSurface, 20 + 64*3 + 80 + 32 - 5, SCREEN_HEIGHT - 64 + 10, 20 + 64*3 + 80 + 32, SCREEN_HEIGHT - 64 + 5, 0, 0, 0, 255 );
					lineRGBA( screenSurface, 20 + 64*3 + 80 + 32 - 4, SCREEN_HEIGHT - 64 + 10, 20 + 64*3 + 80 + 32, SCREEN_HEIGHT - 64 + 6, 0, 0, 0, 255 );
					lineRGBA( screenSurface, 20 + 64*3 + 80 + 32 - 3, SCREEN_HEIGHT - 64 + 10, 20 + 64*3 + 80 + 32, SCREEN_HEIGHT - 64 + 7, 0, 0, 0, 255 );
					lineRGBA( screenSurface, 20 + 64*3 + 80 + 32, SCREEN_HEIGHT - 64 + 5, 20 + 64*3 + 80 + 32 + 5, SCREEN_HEIGHT - 64 + 10, 0, 0, 0, 255 );
					lineRGBA( screenSurface, 20 + 64*3 + 80 + 32, SCREEN_HEIGHT - 64 + 6, 20 + 64*3 + 80 + 32 + 4, SCREEN_HEIGHT - 64 + 10, 0, 0, 0, 255 );
					lineRGBA( screenSurface, 20 + 64*3 + 80 + 32, SCREEN_HEIGHT - 64 + 7, 20 + 64*3 + 80 + 32 + 3, SCREEN_HEIGHT - 64 + 10, 0, 0, 0, 255 );
				}
			}
			else if ( setSecondary == 3 )
			{
				if ( toolSelection == 0 )
				{
					renderingCore.AppendUpdateRect( 80, SCREEN_HEIGHT - 64 - 64 - 10 + 0 - 64 - 4, 64 + 64 + 8, SCREEN_HEIGHT-64 );
					boxRGBA( screenSurface, 84, 346+(SCREEN_HEIGHT-480), 140, 402+(SCREEN_HEIGHT-480), 34, 99, 27, 150 );
					boxRGBA( screenSurface, 152, 346+(SCREEN_HEIGHT-480), 208, 402+(SCREEN_HEIGHT-480), 162, 152, 105, 150 );
					boxRGBA( screenSurface, 84, 278+(SCREEN_HEIGHT-480), 140, 334+(SCREEN_HEIGHT-480), 255, 114, 0, 150 );

					switch ( pencilLineType )
					{
						case 0:
							{
								rectangleRGBA( screenSurface, 80 + 0, SCREEN_HEIGHT - 64 - 64 - 10 + 0, 80 + 64 - 0, SCREEN_HEIGHT - 64 - 10 - 0, 0, 0, 0, 150 );
								rectangleRGBA( screenSurface, 80 + 1, SCREEN_HEIGHT - 64 - 64 - 10 + 1, 80 + 64 - 1, SCREEN_HEIGHT - 64 - 10 - 1, 0, 0, 0, 150 );
								rectangleRGBA( screenSurface, 80 + 2, SCREEN_HEIGHT - 64 - 64 - 10 + 2, 80 + 64 - 2, SCREEN_HEIGHT - 64 - 10 - 2, 0, 0, 0, 150 );
								rectangleRGBA( screenSurface, 80 + 3, SCREEN_HEIGHT - 64 - 64 - 10 + 3, 80 + 64 - 3, SCREEN_HEIGHT - 64 - 10 - 3, 0, 0, 0, 150 );
								break;
							}

						case 1:
							{
								rectangleRGBA( screenSurface, 80 + 0 + 64 + 4, SCREEN_HEIGHT - 64 - 64 - 10 + 0, 80 + 64 - 0 + 64 + 4, SCREEN_HEIGHT - 64 - 10 - 0, 0, 0, 0, 150 );
								rectangleRGBA( screenSurface, 80 + 1 + 64 + 4, SCREEN_HEIGHT - 64 - 64 - 10 + 1, 80 + 64 - 1 + 64 + 4, SCREEN_HEIGHT - 64 - 10 - 1, 0, 0, 0, 150 );
								rectangleRGBA( screenSurface, 80 + 2 + 64 + 4, SCREEN_HEIGHT - 64 - 64 - 10 + 2, 80 + 64 - 2 + 64 + 4, SCREEN_HEIGHT - 64 - 10 - 2, 0, 0, 0, 150 );
								rectangleRGBA( screenSurface, 80 + 3 + 64 + 4, SCREEN_HEIGHT - 64 - 64 - 10 + 3, 80 + 64 - 3 + 64 + 4, SCREEN_HEIGHT - 64 - 10 - 3, 0, 0, 0, 150 );
								break;
							}

						case 2:
							{
								rectangleRGBA( screenSurface, 80 + 0, SCREEN_HEIGHT - 64 - 64 - 10 + 0 - 64 - 4, 80 + 64 - 0, SCREEN_HEIGHT - 64 - 10 - 0 - 64 - 4, 0, 0, 0, 150 );
								rectangleRGBA( screenSurface, 80 + 1, SCREEN_HEIGHT - 64 - 64 - 10 + 1 - 64 - 4, 80 + 64 - 1, SCREEN_HEIGHT - 64 - 10 - 1 - 64 - 4, 0, 0, 0, 150 );
								rectangleRGBA( screenSurface, 80 + 2, SCREEN_HEIGHT - 64 - 64 - 10 + 2 - 64 - 4, 80 + 64 - 2, SCREEN_HEIGHT - 64 - 10 - 2 - 64 - 4, 0, 0, 0, 150 );
								rectangleRGBA( screenSurface, 80 + 3, SCREEN_HEIGHT - 64 - 64 - 10 + 3 - 64 - 4, 80 + 64 - 3, SCREEN_HEIGHT - 64 - 10 - 3 - 64 - 4, 0, 0, 0, 150 );
								break;
							}
					}

					switch ( pencilPrevLineType )
					{
						case 0:
							{
								rectangleRGBA( screenSurface, 80 + 0, SCREEN_HEIGHT - 64 - 64 - 10 + 0, 80 + 64 - 0, SCREEN_HEIGHT - 64 - 10 - 0, 0, 0, 0, 100 );
								rectangleRGBA( screenSurface, 80 + 1, SCREEN_HEIGHT - 64 - 64 - 10 + 1, 80 + 64 - 1, SCREEN_HEIGHT - 64 - 10 - 1, 0, 0, 0, 100 );
								rectangleRGBA( screenSurface, 80 + 2, SCREEN_HEIGHT - 64 - 64 - 10 + 2, 80 + 64 - 2, SCREEN_HEIGHT - 64 - 10 - 2, 0, 0, 0, 100 );
								rectangleRGBA( screenSurface, 80 + 3, SCREEN_HEIGHT - 64 - 64 - 10 + 3, 80 + 64 - 3, SCREEN_HEIGHT - 64 - 10 - 3, 0, 0, 0, 100 );
								break;
							}

						case 1:
							{
								rectangleRGBA( screenSurface, 80 + 0 + 64 + 4, SCREEN_HEIGHT - 64 - 64 - 10 + 0, 80 + 64 - 0 + 64 + 4, SCREEN_HEIGHT - 64 - 10 - 0, 0, 0, 0, 100 );
								rectangleRGBA( screenSurface, 80 + 1 + 64 + 4, SCREEN_HEIGHT - 64 - 64 - 10 + 1, 80 + 64 - 1 + 64 + 4, SCREEN_HEIGHT - 64 - 10 - 1, 0, 0, 0, 100 );
								rectangleRGBA( screenSurface, 80 + 2 + 64 + 4, SCREEN_HEIGHT - 64 - 64 - 10 + 2, 80 + 64 - 2 + 64 + 4, SCREEN_HEIGHT - 64 - 10 - 2, 0, 0, 0, 100 );
								rectangleRGBA( screenSurface, 80 + 3 + 64 + 4, SCREEN_HEIGHT - 64 - 64 - 10 + 3, 80 + 64 - 3 + 64 + 4, SCREEN_HEIGHT - 64 - 10 - 3, 0, 0, 0, 100 );
								break;
							}

						case 2:
							{
								rectangleRGBA( screenSurface, 80 + 0, SCREEN_HEIGHT - 64 - 64 - 10 + 0 - 64 - 4, 80 + 64 - 0, SCREEN_HEIGHT - 64 - 10 - 0 - 64 - 4, 0, 0, 0, 100 );
								rectangleRGBA( screenSurface, 80 + 1, SCREEN_HEIGHT - 64 - 64 - 10 + 1 - 64 - 4, 80 + 64 - 1, SCREEN_HEIGHT - 64 - 10 - 1 - 64 - 4, 0, 0, 0, 100 );
								rectangleRGBA( screenSurface, 80 + 2, SCREEN_HEIGHT - 64 - 64 - 10 + 2 - 64 - 4, 80 + 64 - 2, SCREEN_HEIGHT - 64 - 10 - 2 - 64 - 4, 0, 0, 0, 100 );
								rectangleRGBA( screenSurface, 80 + 3, SCREEN_HEIGHT - 64 - 64 - 10 + 3 - 64 - 4, 80 + 64 - 3, SCREEN_HEIGHT - 64 - 10 - 3 - 64 - 4, 0, 0, 0, 100 );
								break;
							}
					}
				}
				else if ( toolSelection == 1 )
				{
					renderingCore.AppendUpdateRect( 80, SCREEN_HEIGHT - 64 - 64 - 10 + 0 - 64 - 4, 64 + 64 + 8, 64 + 64 + 8 );
					boxRGBA( screenSurface, 84, 346+(SCREEN_HEIGHT-480), 140, 402+(SCREEN_HEIGHT-480), 162, 152, 105, 150 );
					boxRGBA( screenSurface, 152, 346+(SCREEN_HEIGHT-480), 208, 402+(SCREEN_HEIGHT-480), 34, 99, 27, 150 );
					boxRGBA( screenSurface, 152, 278+(SCREEN_HEIGHT-480), 208, 334+(SCREEN_HEIGHT-480), 255, 114, 0, 150 );

					switch ( lineToolLineType )
					{
						case 1:
							{
								rectangleRGBA( screenSurface, 80 + 0, SCREEN_HEIGHT - 64 - 64 - 10 + 0, 80 + 64 - 0, SCREEN_HEIGHT - 64 - 10 - 0, 0, 0, 0, 150 );
								rectangleRGBA( screenSurface, 80 + 1, SCREEN_HEIGHT - 64 - 64 - 10 + 1, 80 + 64 - 1, SCREEN_HEIGHT - 64 - 10 - 1, 0, 0, 0, 150 );
								rectangleRGBA( screenSurface, 80 + 2, SCREEN_HEIGHT - 64 - 64 - 10 + 2, 80 + 64 - 2, SCREEN_HEIGHT - 64 - 10 - 2, 0, 0, 0, 150 );
								rectangleRGBA( screenSurface, 80 + 3, SCREEN_HEIGHT - 64 - 64 - 10 + 3, 80 + 64 - 3, SCREEN_HEIGHT - 64 - 10 - 3, 0, 0, 0, 150 );
								break;
							}

						case 0:
							{
								rectangleRGBA( screenSurface, 80 + 0 + 64 + 4, SCREEN_HEIGHT - 64 - 64 - 10 + 0, 80 + 64 - 0 + 64 + 4, SCREEN_HEIGHT - 64 - 10 - 0, 0, 0, 0, 150 );
								rectangleRGBA( screenSurface, 80 + 1 + 64 + 4, SCREEN_HEIGHT - 64 - 64 - 10 + 1, 80 + 64 - 1 + 64 + 4, SCREEN_HEIGHT - 64 - 10 - 1, 0, 0, 0, 150 );
								rectangleRGBA( screenSurface, 80 + 2 + 64 + 4, SCREEN_HEIGHT - 64 - 64 - 10 + 2, 80 + 64 - 2 + 64 + 4, SCREEN_HEIGHT - 64 - 10 - 2, 0, 0, 0, 150 );
								rectangleRGBA( screenSurface, 80 + 3 + 64 + 4, SCREEN_HEIGHT - 64 - 64 - 10 + 3, 80 + 64 - 3 + 64 + 4, SCREEN_HEIGHT - 64 - 10 - 3, 0, 0, 0, 150 );
								break;
							}

						case 2:
							{
								rectangleRGBA( screenSurface, 80 + 0 + 64 + 4, SCREEN_HEIGHT - 64 - 64 - 10 + 0 - 64 - 4, 80 + 64 - 0 + 64 + 4, SCREEN_HEIGHT - 64 - 10 - 0 - 64 - 4, 0, 0, 0, 150 );
								rectangleRGBA( screenSurface, 80 + 1 + 64 + 4, SCREEN_HEIGHT - 64 - 64 - 10 + 1 - 64 - 4, 80 + 64 - 1 + 64 + 4, SCREEN_HEIGHT - 64 - 10 - 1 - 64 - 4, 0, 0, 0, 150 );
								rectangleRGBA( screenSurface, 80 + 2 + 64 + 4, SCREEN_HEIGHT - 64 - 64 - 10 + 2 - 64 - 4, 80 + 64 - 2 + 64 + 4, SCREEN_HEIGHT - 64 - 10 - 2 - 64 - 4, 0, 0, 0, 150 );
								rectangleRGBA( screenSurface, 80 + 3 + 64 + 4, SCREEN_HEIGHT - 64 - 64 - 10 + 3 - 64 - 4, 80 + 64 - 3 + 64 + 4, SCREEN_HEIGHT - 64 - 10 - 3 - 64 - 4, 0, 0, 0, 150 );
								break;
							}
					}

					switch ( lineToolPrevLineType )
					{
						case 1:
							{
								rectangleRGBA( screenSurface, 80 + 0, SCREEN_HEIGHT - 64 - 64 - 10 + 0, 80 + 64 - 0, SCREEN_HEIGHT - 64 - 10 - 0, 0, 0, 0, 100 );
								rectangleRGBA( screenSurface, 80 + 1, SCREEN_HEIGHT - 64 - 64 - 10 + 1, 80 + 64 - 1, SCREEN_HEIGHT - 64 - 10 - 1, 0, 0, 0, 100 );
								rectangleRGBA( screenSurface, 80 + 2, SCREEN_HEIGHT - 64 - 64 - 10 + 2, 80 + 64 - 2, SCREEN_HEIGHT - 64 - 10 - 2, 0, 0, 0, 100 );
								rectangleRGBA( screenSurface, 80 + 3, SCREEN_HEIGHT - 64 - 64 - 10 + 3, 80 + 64 - 3, SCREEN_HEIGHT - 64 - 10 - 3, 0, 0, 0, 100 );
								break;
							}

						case 0:
							{
								rectangleRGBA( screenSurface, 80 + 0 + 64 + 4, SCREEN_HEIGHT - 64 - 64 - 10 + 0, 80 + 64 - 0 + 64 + 4, SCREEN_HEIGHT - 64 - 10 - 0, 0, 0, 0, 100 );
								rectangleRGBA( screenSurface, 80 + 1 + 64 + 4, SCREEN_HEIGHT - 64 - 64 - 10 + 1, 80 + 64 - 1 + 64 + 4, SCREEN_HEIGHT - 64 - 10 - 1, 0, 0, 0, 100 );
								rectangleRGBA( screenSurface, 80 + 2 + 64 + 4, SCREEN_HEIGHT - 64 - 64 - 10 + 2, 80 + 64 - 2 + 64 + 4, SCREEN_HEIGHT - 64 - 10 - 2, 0, 0, 0, 100 );
								rectangleRGBA( screenSurface, 80 + 3 + 64 + 4, SCREEN_HEIGHT - 64 - 64 - 10 + 3, 80 + 64 - 3 + 64 + 4, SCREEN_HEIGHT - 64 - 10 - 3, 0, 0, 0, 100 );
								break;
							}

						case 2:
							{
								rectangleRGBA( screenSurface, 80 + 0 + 64 + 4, SCREEN_HEIGHT - 64 - 64 - 10 + 0 - 64 - 4, 80 + 64 - 0 + 64 + 4, SCREEN_HEIGHT - 64 - 10 - 0 - 64 - 4, 0, 0, 0, 100 );
								rectangleRGBA( screenSurface, 80 + 1 + 64 + 4, SCREEN_HEIGHT - 64 - 64 - 10 + 1 - 64 - 4, 80 + 64 - 1 + 64 + 4, SCREEN_HEIGHT - 64 - 10 - 1 - 64 - 4, 0, 0, 0, 100 );
								rectangleRGBA( screenSurface, 80 + 2 + 64 + 4, SCREEN_HEIGHT - 64 - 64 - 10 + 2 - 64 - 4, 80 + 64 - 2 + 64 + 4, SCREEN_HEIGHT - 64 - 10 - 2 - 64 - 4, 0, 0, 0, 100 );
								rectangleRGBA( screenSurface, 80 + 3 + 64 + 4, SCREEN_HEIGHT - 64 - 64 - 10 + 3 - 64 - 4, 80 + 64 - 3 + 64 + 4, SCREEN_HEIGHT - 64 - 10 - 3 - 64 - 4, 0, 0, 0, 100 );
								break;
							}
					}
				}
				else if ( toolSelection == 3 )
				{
					toSpawnIcon.SetVisible( true );
					toSpawnIcon.SetPosition( 64*3 + 80 + 32, SCREEN_HEIGHT - 64 - 10 - 32 );
				}
			}
		}

		//TODO, options for this
		if ( 1 )
		{
			circleRGBA( screenSurface, SCREEN_WIDTH - 40, 40, 20, 0, 0, 0, 255 );
			circleRGBA( screenSurface, SCREEN_WIDTH - 40, 40, 19, 0, 0, 0, 255 );
			circleRGBA( screenSurface, SCREEN_WIDTH - 40, 40, 18, 0, 0, 0, 255 );
			renderingCore.AppendUpdateRect( SCREEN_WIDTH - 40 - 30, 40 - 30, 60, 60 );

			float hypo = sqrt( pow( float( ( spawn.spawnPosition.x + screenOffset.x ) - ( SCREEN_WIDTH - 40 ) ), 2 ) + pow(  float( ( spawn.spawnPosition.y + screenOffset.y ) - 40 ), 2  ) );
			float ang = -asin( float( ( spawn.spawnPosition.y + screenOffset.y ) - 40 ) / hypo );
			if ( spawn.spawnPosition.x + screenOffset.x > SCREEN_WIDTH - 40 )
				ang = b2_pi - ang;

			float pointerX = ( ( 0.0f * cos( double( ang + b2_pi / 2.0f ) ) ) - ( 19.0f * sin( double( ang + b2_pi / 2.0f ) ) ) ) + SCREEN_WIDTH - 40;
			float pointerY = ( ( 0.0f * sin( double( ang + b2_pi / 2.0f ) ) ) + ( 19.0f * cos( double( ang + b2_pi / 2.0f ) ) ) ) + 40;
			filledCircleRGBA( screenSurface, pointerX, pointerY, 4, 0, 141, 0, 255 );
			filledCircleRGBA( screenSurface, pointerX, pointerY, 1, 255, 255, 255, 255 );
			{
				SDL_Color textColor = { 0, 0, 0 };
				stringstream sshypo;
				sshypo << int( hypo );
				string temp = "Distance to spawn: ";
				temp = temp + sshypo.str() + "px";
				distanceToSpawnLabel.SetText( &fontSans12, TEXTALIGNRIGHT, TEXTALIGNTOP, temp.c_str(), textColor );
				distanceToSpawnLabel.SetPosition( SCREEN_WIDTH - 10, 70 );
				distanceToSpawnLabel.Render( screenSurface );
				renderingCore.AppendUpdateRect( SCREEN_WIDTH - distanceToSpawnLabel.ReturnSDLRect().w - 10, 70, distanceToSpawnLabel.ReturnSDLRect().w, 13 );
			}
			{
				SDL_Color textColor = { 0, 0, 0 };
				stringstream sshypo;
				sshypo << int( gameCanvas.GetDistanceTraveled() );
				string temp = "Distance traveled: ";
				temp = temp + sshypo.str() + "px";
				distanceTraveledLabel.SetText( &fontSans12, TEXTALIGNRIGHT, TEXTALIGNTOP, temp.c_str(), textColor );
				distanceTraveledLabel.SetPosition( SCREEN_WIDTH - 10, 70 + 14 );
				distanceTraveledLabel.Render( screenSurface );
				renderingCore.AppendUpdateRect( SCREEN_WIDTH - distanceTraveledLabel.ReturnSDLRect().w - 10, 70 + 14, distanceTraveledLabel.ReturnSDLRect().w, 13 );
			}
		}

        //Draw all the pointers
		if ( !stopped )
		{
			if ( hatOff && sledderObject.sledderHatBody )
			{
				float centerX = sledderObject.sledderHatBody->GetPosition().x * 10.0f;
				float centerY = sledderObject.sledderHatBody->GetPosition().y * 10.0f;

				float hypo = sqrt( pow( float( ( centerX + screenOffset.x ) - ( SCREEN_WIDTH - 40 ) ), 2 ) + pow(  float( ( centerY + screenOffset.y ) - 40 ), 2  ) );
				float ang = -asin( float( ( centerY + screenOffset.y ) - 40 ) / hypo );
				if ( centerX + screenOffset.x > SCREEN_WIDTH - 40 )
					ang = b2_pi - ang;

				float pointerX = ( ( 0.0f * cos( double( ang + b2_pi / 2.0f ) ) ) - ( 19.0f * sin( double( ang + b2_pi / 2.0f ) ) ) ) + SCREEN_WIDTH - 40;
				float pointerY = ( ( 0.0f * sin( double( ang + b2_pi / 2.0f ) ) ) + ( 19.0f * cos( double( ang + b2_pi / 2.0f ) ) ) ) + 40;
				filledCircleRGBA( screenSurface, pointerX, pointerY, 4, 255, 100, 0, 255 );
				filledCircleRGBA( screenSurface, pointerX, pointerY, 1, 255, 255, 255, 255 );
			}

			if ( headOff && sledderObject.sledderHeadBody)
			{
				float centerX = sledderObject.sledderHeadBody->GetPosition().x * 10.0f;
				float centerY = sledderObject.sledderHeadBody->GetPosition().y * 10.0f;

				float hypo = sqrt( pow( float( ( centerX + screenOffset.x ) - ( SCREEN_WIDTH - 40 ) ), 2 ) + pow(  float( ( centerY + screenOffset.y ) - 40 ), 2  ) );
				float ang = -asin( ( float( centerY + screenOffset.y ) - 40 ) / hypo );
				if ( centerX + screenOffset.x > SCREEN_WIDTH - 40 )
					ang = b2_pi - ang;

				float pointerX = ( ( 0.0f * cos( double( ang + b2_pi / 2.0f ) ) ) - ( 19.0f * sin( double( ang + b2_pi / 2.0f ) ) ) ) + SCREEN_WIDTH - 40;
				float pointerY = ( ( 0.0f * sin( double( ang + b2_pi / 2.0f ) ) ) + ( 19.0f * cos( double( ang + b2_pi / 2.0f ) ) ) ) + 40;
				filledCircleRGBA( screenSurface, pointerX, pointerY, 4, 36, 255, 0, 255 );
				filledCircleRGBA( screenSurface, pointerX, pointerY, 1, 255, 255, 255, 255 );
			}

			if ( armOff && sledderObject.sledderArmBody)
			{
				float centerX = sledderObject.sledderArmBody->GetPosition().x * 10.0f;
				float centerY = sledderObject.sledderArmBody->GetPosition().y * 10.0f;

				float hypo = sqrt( pow( float( ( centerX + screenOffset.x ) - ( SCREEN_WIDTH - 40 ) ), 2 ) + pow( float( ( centerY + screenOffset.y ) - 40 ), 2  ) );
				float ang = -asin( float( ( centerY + screenOffset.y ) - 40 ) / hypo );
				if ( centerX + screenOffset.x > SCREEN_WIDTH - 40 )
					ang = b2_pi - ang;

				float pointerX = ( ( 0.0f * cos( double( ang + b2_pi / 2.0f ) ) ) - ( 19.0f * sin( double( ang + b2_pi / 2.0f ) ) ) ) + SCREEN_WIDTH - 40;
				float pointerY = ( ( 0.0f * sin( double( ang + b2_pi / 2.0f ) ) ) + ( 19.0f * cos( double( ang + b2_pi / 2.0f ) ) ) ) + 40;
				filledCircleRGBA( screenSurface, pointerX, pointerY, 4, 255, 0, 234, 255 );
				filledCircleRGBA( screenSurface, pointerX, pointerY, 1, 255, 255, 255, 255 );
			}

			if ( legOff && sledderObject.sledderLegBody)
			{
				float centerX = sledderObject.sledderLegBody->GetPosition().x * 10.0f;
				float centerY = sledderObject.sledderLegBody->GetPosition().y * 10.0f;

				float hypo = sqrt( pow( float( ( centerX + screenOffset.x ) - ( SCREEN_WIDTH - 40 ) ), 2 ) + pow(  float( ( centerY + screenOffset.y ) - 40 ), 2  ) );
				float ang = -asin( float( ( centerY + screenOffset.y ) - 40 ) / hypo );
				if ( centerX + screenOffset.x > SCREEN_WIDTH - 40 )
					ang = b2_pi - ang;

				float pointerX = ( ( 0.0f * cos( double( ang + b2_pi / 2.0f ) ) ) - ( 19.0f * sin( double( ang + b2_pi / 2.0f ) ) ) ) + SCREEN_WIDTH - 40;
				float pointerY = ( ( 0.0f * sin( double( ang + b2_pi / 2.0f ) ) ) + ( 19.0f * cos( double( ang + b2_pi / 2.0f ) ) ) ) + 40;
				filledCircleRGBA( screenSurface, pointerX, pointerY, 4, 255, 204, 0, 255 );
				filledCircleRGBA( screenSurface, pointerX, pointerY, 1, 255, 255, 255, 255 );
			}

			if ( fallenOff && sledObject.sledBody)
			{
				float centerX = sledObject.sledBody->GetPosition().x * 10.0f;
				float centerY = sledObject.sledBody->GetPosition().y * 10.0f;

				float hypo = sqrt( pow( float( ( centerX + screenOffset.x ) - ( SCREEN_WIDTH - 40 ) ), 2 ) + pow(  float( ( centerY + screenOffset.y ) - 40 ), 2  ) );
				float ang = -asin( float( ( centerY + screenOffset.y ) - 40 ) / hypo );
				if ( centerX + screenOffset.x > SCREEN_WIDTH - 40 )
					ang = b2_pi - ang;

				float pointerX = ( ( 0.0f * cos( double( ang + b2_pi / 2.0f ) ) ) - ( 19.0f * sin( double( ang + b2_pi / 2.0f ) ) ) ) + SCREEN_WIDTH - 40;
				float pointerY = ( ( 0.0f * sin( double( ang + b2_pi / 2.0f ) ) ) + ( 19.0f * cos( double( ang + b2_pi / 2.0f ) ) ) ) + 40;
				filledCircleRGBA( screenSurface, pointerX, pointerY, 4, 0, 0, 0, 255 );
				filledCircleRGBA( screenSurface, pointerX, pointerY, 1, 255, 255, 255, 255 );
			}
		}

#ifdef DEBUGINFO
		if ( !stopped )
		{
			float sledVelX = ( ( sledObject.sledBody->GetLinearVelocity().y ) );
			std::stringstream str;
			str << sledVelX;
			string sledVelXstr = str.str() + " Sled Velocity X";
			stringRGBA( screenSurface, 2, 24, sledVelXstr.c_str(), 0, 0, 0, 255 );
			renderingCore.AppendUpdateRect( 2, 24, 210, 10 );

			if ( hatOff )
			{
				float averageHatVel = ( sledderObject.sledderHatBody->GetLinearVelocity().x + sledderObject.sledderHatBody->GetLinearVelocity().y );
				std::stringstream str;
				str << averageHatVel;
				string averageHatVelstr = str.str() + " Avg. Hat Velocity";
				stringRGBA( screenSurface, 2, 36, averageHatVelstr.c_str(), 0, 0, 0, 255 );
				renderingCore.AppendUpdateRect( 2, 36, 200, 10 );
			}

			if ( fallenOff )
			{
				float averageBodyVel = ( sledderObject.sledderBodyBody->GetLinearVelocity().x + sledderObject.sledderBodyBody->GetLinearVelocity().y );
				std::stringstream str;
				str << averageBodyVel;
				string averageBodyVelstr = str.str() + " Avg. Body Velocity";
				stringRGBA( screenSurface, 2, 48, averageBodyVelstr.c_str(), 0, 0, 0, 255 );
				renderingCore.AppendUpdateRect( 2, 48, 210, 10 );
			}
		}
		std::stringstream str;
		str << gameCanvas.GetNumberOfLines();
		string canvasLines = str.str() + " Canvas Lines";
		stringRGBA( screenSurface, 2, 2, canvasLines.c_str(), 0, 0, 0, 255 );
		renderingCore.AppendUpdateRect( 2, 2, 200, 10 );

		str.str( "" );
		str << gameCanvas.GetNumberOfTraceLines();
		string traceLines = str.str() + " Trace Lines";
		stringRGBA( screenSurface, 2, 12, traceLines.c_str(), 0, 0, 0, 255 );
		renderingCore.AppendUpdateRect( 2, 12, 200, 10 );
#endif

		//Mess cleanups
		renderingCore.AppendUpdateRect( SCREEN_WIDTH - 80, SCREEN_HEIGHT - 64, 1, 64 );

		if ( configMenu.isVisible() )
		{
			configMenu.RenderMenu( screenSurface );
			renderingCore.AppendUpdateRect( SCREEN_WIDTH / 2 - 250, SCREEN_HEIGHT / 2 - 150, 501, 301 );
		}

		if ( loadMenu.isVisible() )
		{
			loadMenu.RenderMenu( screenSurface );
			renderingCore.AppendUpdateRect( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
		}

		if(flagMode)
		{
		    flagManager.RenderFlagMenu(screenSurface);
		    renderingCore.AppendUpdateRect( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
		}



		uiButtons[12].SetVisible( false );
		uiButtons[12].SetPosition( 32 + 80 + 7 * 64 - 6, SCREEN_HEIGHT - 32 - 64 - 10 );
		uiButtons[2].SetPosition( 32 + 80 + 2 * 64, SCREEN_HEIGHT - 32 );
		uiButtons[9].SetPosition( 32 + 80 + 9 * 64, SCREEN_HEIGHT - 32 );
	}

	renderingCore.Render();
}
