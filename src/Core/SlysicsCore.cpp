/*
 * src/Game/SlysicsCore.cpp
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
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

SlysicsCore::SlysicsCore()
{
	stopped = true;
	paused = false;
	hatOff = false;
	headOff = false;
	armOff = false;
	legOff = false;
	fallenOff = false;
	exploded = false;
	lineToolPressed = false;
	portalToolPressed = false;
	mouseDown = false;
	moveSpawn = false;
	setSpawnRotation = false;
	quit = false;
	flagged = false;

	scrollDown = false;
	scrollLeft = false;
	scrollRight = false;
	scrollUp = false;

	flagMode = false;


	spawn.spawnPosition.prevX = 0;
	spawn.spawnPosition.prevY = 0;
	spawn.spawnPosition.x = 0;
	spawn.spawnPosition.y = 0;
	spawn.initialVelocity.vel = 0;
	spawn.initialVelocity.prevVel = 0;
	spawn.angle = 0.0f;

	screenOffset.prevX = SCREEN_WIDTH/2;
	screenOffset.prevY = SCREEN_HEIGHT/2;
	screenOffset.x = SCREEN_WIDTH/2;
	screenOffset.y = SCREEN_HEIGHT/2;

	toolSelection = 0;
	setSecondary = -1;
	pencilLineType = 0;
	pencilPrevLineType = 0;
	lineToolLineType = 0;
	lineToolPrevLineType = 0;
	mousePreviousX = -1;
	mousePreviousY = -1;


}

SlysicsCore::~SlysicsCore()
{

}

int SlysicsCore::InitializeSlysicsCore()
{
	renderingCore.InitializeScreen();

	sledObject.InitializeSled();
	sledderObject.InitializeSledder();

	uiButtons[0].LoadImage( "data/icon_pencil.png" );
	uiButtons[1].LoadImage( "data/icon_lineTool.png" );
	uiButtons[2].LoadImage( "data/icon_eraser.png" );
	uiButtons[3].LoadImage( "data/icon_move.png" );
	uiButtons[4].LoadImage( "data/icon_play.png" );
	uiButtons[10].LoadImage( "data/icon_pause.png" );
	uiButtons[5].LoadImage( "data/icon_stop.png" );
	uiButtons[6].LoadImage( "data/icon_flag.png" );
	uiButtons[7].LoadImage( "data/icon_saveMain.png" );
	uiButtons[8].LoadImage( "data/icon_delete.png" );
	uiButtons[9].LoadImage( "data/icon_quit.png" );
	uiButtons[11].LoadImage( "data/icon_config.png" );
	uiButtons[12].LoadImage( "data/icon_save.png" );
	uiButtons[13].LoadImage( "data/icon_load.png" );
	uiButtons[14].LoadImage( "data/icon_portal.png" );
	spawn.spawnImage.LoadImage( "data/spawn.png" );
	toSpawnIcon.LoadImage( "data/toSpawn.png" );
	toSpawnIcon.SetVisible( false );

	portalManager.Initialize();

	screenSurface = renderingCore.ReturnScreenPointer();

	renderingCore.AddRenderObject( &spawn.spawnImage );
	renderingCore.AddRenderObject( &sledObject.sledImage );
	renderingCore.AddRenderObject( &sledObject.sledCrumpledImage );
	renderingCore.AddRenderObject( &sledderObject.headImage );
	renderingCore.AddRenderObject( &sledderObject.legImage );
	renderingCore.AddRenderObject( &sledderObject.hatImage );
	renderingCore.AddRenderObject( &sledderObject.bodyImage );
	renderingCore.AddRenderObject( &sledderObject.armImage );

	for ( int i = 0; i < 10; i++ )
	{
		uiButtons[i].SetPosition( 32 + 80 + i * 64, SCREEN_HEIGHT - 32 );
		renderingCore.AddRenderObject( &uiButtons[i] );
	}
	uiButtons[14].SetPosition( 32+8+11*64, SCREEN_HEIGHT - 32);
	renderingCore.AddRenderObject(&uiButtons[14]);

	uiButtons[11].SetPosition( SCREEN_WIDTH - 32, SCREEN_HEIGHT - 32 );
	renderingCore.AddRenderObject( &uiButtons[11] );

	uiButtons[12].SetPosition( 32 + 80 + 7 * 64 - 6, SCREEN_HEIGHT - 32 - 64 - 10 );
	renderingCore.AddRenderObject( &uiButtons[12] );
	uiButtons[13].SetPosition( 32 + 80 + 7 * 64 + 4, SCREEN_HEIGHT - 32 - 64 - 10 - 64 - 4 );
	renderingCore.AddRenderObject( &uiButtons[13] );

	uiButtons[12].SetVisible( false );
	uiButtons[13].SetVisible( false );

	renderingCore.AddRenderObject( &toSpawnIcon );

	uiButtons[10].SetPosition( 32 + 80 + 4 * 64, SCREEN_HEIGHT - 32 );
	renderingCore.AddRenderObject( &uiButtons[10] );
	uiButtons[10].SetVisible( false );

	sledObject.sledImage.SetVisible( false );
	sledObject.sledCrumpledImage.SetVisible( false );
	sledderObject.bodyImage.SetVisible( false  );
	sledderObject.headImage.SetVisible( false  );
	sledderObject.armImage.SetVisible( false  );
	sledderObject.legImage.SetVisible( false  );
	sledderObject.hatImage.SetVisible( false );

	gameCanvas.SetPhysicsCore( &physicsCore );

	string path = getenv( "HOME" );
	path += "/.slysics";
	mkdir( path.c_str(), 0775 );
	path = getenv( "HOME" );
	path += "/.slysics/maps";
	mkdir( path.c_str(), 0775 );

	//Config stuff
	configCore.FillConfigurationList();
	printf( "Loading Configuration...\n" );
	if ( configCore.LoadConfigurationFile() == -1 )
		configCore.WriteConfigurationFile();

	configCore.UpdateVars();


	configMenu.SetupMenu( &configCore );
	loadMenu.SetupMenu( &gameCanvas, &spawn );

	fontSans12.LoadFont( FONT_FILE, 12 );

	flagManager.Initialize();

	//guiKBoard.InitKeyboard();
}

void SlysicsCore::ProcessUIClick( int x, int y )
{
	for ( int i = 0; i < 13; i++ )
	{
		if ( ( x > 80 + i * 64 ) &&
				( x < 80 + i * 64 + 64 ) &&
				( y > SCREEN_HEIGHT - 64 ) )
		{
			if ( i <= 3 && stopped || i <= 3 && paused )
			{
				if ( i == 1 )
					lineToolPressed = true;

				if ( toolSelection == i && ( toolSelection == 0 || toolSelection == 1 || toolSelection == 3 ) )
					setSecondary = 2;

				toolSelection = i;
				break;
			}

			if(i == 10 && stopped)
			{
			    portalToolPressed = true;
			    toolSelection = 10;
			    break;
			}

			if ( i == 6 )
			{
				if(!fallenOff && !stopped)
				{
				    flagManager.AddFlag(sledderObject.sledderBodyBody->GetPosition().x, sledderObject.sledderBodyBody->GetPosition().y, sledderObject.sledderBodyBody->GetLinearVelocity().x, sledderObject.sledderBodyBody->GetLinearVelocity().y, sledderObject.sledderBodyBody->GetAngle());
				    //printf("%f, %f, %f, %f, %f\n", sledderObject.sledderBodyBody->GetPosition().x, sledderObject.sledderBodyBody->GetPosition().y, sledderObject.sledderBodyBody->GetLinearVelocity().x, sledderObject.sledderBodyBody->GetLinearVelocity().y, sledderObject.sledderBodyBody->GetAngle());
				}
				else if(stopped && flagManager.GetFlagCount() > 0)
				{
				    if(!flagMode)
				    {
                        flagMode = true;
                        for ( int i = 0; i < 11; i++ )
                        {
                            uiButtons[i].SetVisible( false );
                        }
                        uiButtons[4].SetVisible( true );
                        uiButtons[8].SetVisible( true );
                        uiButtons[9].SetVisible( true );
				    }
				}
				break;
			}

			if ( i == 7 )
			{
				setSecondary = 4;
				break;
			}

			if ( i == 8 && stopped )
			{
				gameCanvas.ClearCanvas();
				gameCanvas.ClearTraceLines();
				portalManager.ClearPortals();
				break;
			}

			if ( i == 9 && stopped )
			{
				quit = true;
				break;
			}

			if ( i == 4 )
			{
				if ( stopped )
				{


					tOrigX = screenOffset.prevX;
					tOrigY = screenOffset.prevY;
					stopped = false;

					if ( !sledderObject.created )
					{
						float rotatedVelX = ( ( spawn.initialVelocity.vel*INITIAL_VEL_FACTOR * cos( double( spawn.angle ) ) ) - ( sin( double( spawn.angle ) ) ) );
						float rotatedVelY = ( ( spawn.initialVelocity.vel*INITIAL_VEL_FACTOR * sin( double( spawn.angle ) ) ) + ( cos( double( spawn.angle ) ) ) );


						if(!flagMode)
						{
						    physicsCore.CreateSled( &sledObject, &sledderObject, ( spawn.spawnPosition.x + 12 ) / 10, ( spawn.spawnPosition.y + 12 ) / 10, spawn.angle );

                            sledObject.SetVelocity( b2Vec2( rotatedVelX, rotatedVelY ), 0 );
                            sledderObject.SetVelocity( b2Vec2( rotatedVelX, rotatedVelY ), 0 );
                            sledVelocity.prevVel = spawn.initialVelocity.vel;
						}
						else
						{
                            physicsCore.CreateSled( &sledObject, &sledderObject, flagManager.GetCurrentFlag().sledPosition.x, flagManager.GetCurrentFlag().sledPosition.y, flagManager.GetCurrentFlag().angle );

                            sledObject.SetVelocity( b2Vec2( flagManager.GetCurrentFlag().sledVelocity.x, flagManager.GetCurrentFlag().sledVelocity.y ), flagManager.GetCurrentFlag().angle );
                            sledderObject.SetVelocity( b2Vec2( flagManager.GetCurrentFlag().sledVelocity.x, flagManager.GetCurrentFlag().sledVelocity.y ), flagManager.GetCurrentFlag().angle );
                            if(flagMode)
                            {
                                flagMode = false;
                                flagged = true;
                                for ( int i = 0; i < 8; i++ )
                                {
                                    uiButtons[i].SetVisible( true );
                                }
                                uiButtons[11].SetVisible( true );
                            }
                            sledVelocity.prevVel = sledObject.sledBody->GetLinearVelocity().x;
						}

						headOff = false;
						armOff = false;
						legOff = false;
					}

					uiButtons[10].SetVisible( true );
					uiButtons[4].SetVisible( false );
					spawn.spawnImage.SetVisible( false );

					sledObject.sledImage.SetVisible( true );
					sledObject.sledCrumpledImage.SetVisible( false );
					sledderObject.bodyImage.SetVisible( true );
					sledderObject.headImage.SetVisible( true );
					sledderObject.armImage.SetVisible( true );
					sledderObject.legImage.SetVisible( true );
					sledderObject.hatImage.SetVisible( true );

					sledderBodyVectors.body.prevX = ( spawn.spawnPosition.x + 12 );
					sledderBodyVectors.body.prevY = ( spawn.spawnPosition.y + 12 );

					sledPosition.prevX = ( spawn.spawnPosition.x + 12 );
					sledPosition.prevY = ( spawn.spawnPosition.y + 12 );

					sledderBodyVectors.hat.prevX = ( spawn.spawnPosition.x + 12 );
					sledderBodyVectors.hat.prevY = ( spawn.spawnPosition.y + 12 );

					gameCanvas.ClearTraceLines();

					hatOff = false;
					fallenOff = false;

					for ( int i = 0; i < 4; i++ )
					{
						uiButtons[i].SetVisible( false );
					}
					for ( int i = 7; i < 10; i++ )
					{
						uiButtons[i].SetVisible( false );
					}

					uiButtons[11].SetVisible( false );
				}
				else
				{
					if ( paused )
					{
						paused = false;
						uiButtons[10].SetVisible( true );
						uiButtons[4].SetVisible( false );

						for ( int i = 0; i < 4; i++ )
						{
							uiButtons[i].SetVisible( false );
						}
						for ( int i = 9; i < 10; i++ )
						{
							uiButtons[i].SetVisible( false );
						}
					}
					else
					{
						paused = true;
						uiButtons[10].SetVisible( false );
						uiButtons[4].SetVisible( true );
						screenOffset.prevX = screenOffset.x;
						screenOffset.prevY = screenOffset.y;

						for ( int i = 0; i < 4; i++ )
						{
							uiButtons[i].SetVisible( true );
						}
					}
				}

				break;
			}

			if ( i == 5 && !stopped )
			{
				stopped = true;

				if ( sledderObject.created )
					physicsCore.DestroySled( &sledObject, &sledderObject );

                lastPortal = Portal();

				screenOffset.prevX = tOrigX;
				screenOffset.prevY = tOrigY;
				screenOffset.x = screenOffset.prevX;
				screenOffset.y = screenOffset.prevY;

				uiButtons[10].SetVisible( false );
				uiButtons[4].SetVisible( true );
				spawn.spawnImage.SetVisible( true );
				sledObject.sledImage.SetVisible( false );
				sledObject.sledCrumpledImage.SetVisible( false );
				sledderObject.bodyImage.SetVisible( false  );
				sledderObject.headImage.SetVisible( false  );
				sledderObject.armImage.SetVisible( false  );
				sledderObject.legImage.SetVisible( false  );
				sledderObject.hatImage.SetVisible( false );
				sledObject.crumpled = false;
				headOff = false;
				armOff = false;
				hatOff = false;
				legOff = false;

				paused = false;

				for ( int i = 0; i < 10; i++ )
				{
					uiButtons[i].SetVisible( true );
				}

				uiButtons[11].SetVisible( true );

				break;
			}
		}
	}
}

void SlysicsCore::Events()
{
	//Poll inputs
	while ( SDL_PollEvent( &inputEvents ) )
	{
		if ( !configMenu.isVisible() && !loadMenu.isVisible() )
        {
            if ( inputEvents.type == SDL_KEYDOWN )
            {
                if ( inputEvents.key.keysym.sym == SDLK_LEFT )
                {
                    scrollLeft = true;
                }
                if ( inputEvents.key.keysym.sym == SDLK_RIGHT )
                {
                    scrollRight = true;
                }
                if ( inputEvents.key.keysym.sym == SDLK_UP )
                {
                    scrollUp = true;
                }
                if ( inputEvents.key.keysym.sym == SDLK_DOWN )
                {
                    scrollDown = true;
                }
            }
            if ( inputEvents.type == SDL_KEYUP )
            {
                if ( inputEvents.key.keysym.sym == SDLK_LEFT )
                {
                    scrollLeft = false;
                }
                if ( inputEvents.key.keysym.sym == SDLK_RIGHT )
                {
                    scrollRight = false;
                }
                if ( inputEvents.key.keysym.sym == SDLK_UP )
                {
                    scrollUp = false;
                }
                if ( inputEvents.key.keysym.sym == SDLK_DOWN )
                {
                    scrollDown = false;
                }
            }
        }

        if ( !scrollDown && !scrollLeft && !scrollRight && !scrollUp )
        {
            if ( inputEvents.type == SDL_MOUSEBUTTONDOWN )
            {
                if ( inputEvents.button.x > SCREEN_WIDTH - 64 && inputEvents.button.y > SCREEN_HEIGHT - 64 && stopped )
                {
                    if ( !configMenu.isVisible() )
                        configMenu.SetVisible( true );
                    else
                        configMenu.SetVisible( false );
                }

                if ( !configMenu.isVisible() && !loadMenu.isVisible() && !flagMode)
                {
                    int spawnRotationIconX = int( ( 0.0f * cos( double( spawn.angle + b2_pi / 2.0f ) ) ) - ( -37.0f * sin( double( spawn.angle + b2_pi / 2.0f ) ) ) ) + spawn.spawnPosition.x + screenOffset.x;
                    int spawnRotationIconY = int( ( 0.0f * sin( double( spawn.angle + b2_pi / 2.0f ) ) ) + ( -37.0f * cos( double( spawn.angle + b2_pi / 2.0f ) ) ) ) + spawn.spawnPosition.y + screenOffset.y;
                    int mouseX = inputEvents.button.x;
                    int mouseY = inputEvents.button.y;
                    if ( ( mouseX >= spawnRotationIconX - 14 &&  mouseX <= spawnRotationIconX + 14 && mouseY >= spawnRotationIconY - 14 && mouseY <= spawnRotationIconY + 14 && stopped ) )
                    {
                        moveSpawn = false;
                        setSpawnRotation = true;
                    }
                    else if ( ( ( inputEvents.button.x > 80 && inputEvents.button.x < SCREEN_WIDTH-(SCREEN_WIDTH-800) - 80 - 6*64 ) ||
                                ( inputEvents.button.x > 80 + 6*64 && inputEvents.button.x < SCREEN_WIDTH-(SCREEN_WIDTH-800) - 80 - 3*64 ) ||
                                ( inputEvents.button.x > 80 + 4*64 && inputEvents.button.x < SCREEN_WIDTH-(SCREEN_WIDTH-800) - 80 - 5*64 && !stopped ) ||
                                ( stopped && inputEvents.button.x > 80 + 7*64 && inputEvents.button.x < 80 + 11*64 ) ) &&
                                inputEvents.button.y > SCREEN_HEIGHT - 64 )
                    {
                        ProcessUIClick( inputEvents.button.x, inputEvents.button.y );
                    }
                    else if ( ( inputEvents.button.x > 80 + 64*4 && inputEvents.button.x < SCREEN_WIDTH-(SCREEN_WIDTH-800) - 80 - 5*64 ) && stopped && !paused && inputEvents.button.y > SCREEN_HEIGHT - 64 )
                    {
                        setSecondary = 0;
                    }
                    else if ( inputEvents.button.y < SCREEN_HEIGHT - 64 && ( stopped || paused ) )
                    {
                        if ( stopped && inputEvents.button.x > spawn.spawnPosition.x + screenOffset.x - 40 && inputEvents.button.x < spawn.spawnPosition.x + screenOffset.x + 40 && inputEvents.button.y > spawn.spawnPosition.y + screenOffset.y - 40 && inputEvents.button.y < spawn.spawnPosition.y + screenOffset.y + 40 )
                        {
                            moveSpawn = true;
                            mousePreviousX = inputEvents.button.x;
                            mousePreviousY = inputEvents.button.y;
                        }
                        else if ( stopped || paused )
                        {
                            mousePreviousX = inputEvents.button.x;
                            mousePreviousY = inputEvents.button.y;
                            mouseDown = true;
                            if ( toolSelection == 1 && configCore.GetVars().snapToPreviousLine )
                            {
                                mousePreviousX = gameCanvas.GetClosestLineX( mousePreviousX, mousePreviousY, screenOffset.x, screenOffset.y );
                                mousePreviousY = gameCanvas.GetClosestLineY( mousePreviousX, mousePreviousY, screenOffset.x, screenOffset.y );
                            }
                        }
                    }
                }
            }

            if ( inputEvents.type == SDL_MOUSEBUTTONUP )
            {
                if ( !configMenu.isVisible() && !loadMenu.isVisible() )
                {
                    if ( !flagged &&
      ( setSecondary == 0 || setSecondary == -1 ) &&
      !moveSpawn &&
      !setSpawnRotation &&
      !mouseDown &&
      ( ( inputEvents.button.x > 80 + 4*64 && inputEvents.button.x < SCREEN_WIDTH-(SCREEN_WIDTH-800) - 80 - 5*64 && stopped ) || ( inputEvents.button.x > 80 + 5*64 && inputEvents.button.x < SCREEN_WIDTH-(SCREEN_WIDTH-800) - 80 - 4*64 ) || ( inputEvents.button.x > 80 + 8*64 && inputEvents.button.x < SCREEN_WIDTH-(SCREEN_WIDTH-800) - 80 ) ) && inputEvents.button.y > SCREEN_HEIGHT - 64 )
                    {
                        ProcessUIClick( inputEvents.button.x, inputEvents.button.y );
                    }
                    else if ( inputEvents.button.y < SCREEN_HEIGHT - 64 )
                    {
                        if ( mouseDown && ( ( !moveSpawn && !setSpawnRotation && toolSelection == 1 && stopped ) || ( toolSelection == 1 && paused ) ) && setSecondary == -1 && !lineToolPressed && !portalToolPressed)
                        {
                            gameCanvas.CreateLine( mousePreviousX, mousePreviousY, inputEvents.button.x, inputEvents.button.y, screenOffset.x, screenOffset.y, lineToolLineType );
                        }
                        if ( mouseDown && ( ( !moveSpawn && !setSpawnRotation && toolSelection == 10 && stopped )  ) && setSecondary == -1 && !lineToolPressed && !portalToolPressed)
                        {
                            float yD = float(mousePreviousY)-float(inputEvents.button.y);
                            float xD = float(mousePreviousX)-float(inputEvents.button.x);

                            float angle = 0.0f;

                            if(xD == 0 && yD > 0)
                            {
                                angle = 90.0f;
                            }
                            else if(xD == 0 && yD < 0)
                            {
                                angle = 270.0f;
                            }
                            else if(xD > 0 && yD > 0)
                            {
                                angle = atan(-yD/xD) * 180/b2_pi + 180;
                            }
                            else if(xD > 0 && yD < 0)
                                angle = atan(-yD/xD) * 180/b2_pi + 180;
                            else if(xD < 0 && yD > 0)
                                angle = atan(-yD/xD) * 180/b2_pi;
                            else if(xD < 0 && yD < 0)
                                angle = atan(-yD/xD) * 180/b2_pi;
                            else if(xD > 0 && yD == 0)
                                angle = 180;


                            portalManager.AddPortal(mousePreviousX-screenOffset.x,mousePreviousY-screenOffset.y,angle);
                            //gameCanvas.CreateLine( mousePreviousX, mousePreviousY, inputEvents.button.x, inputEvents.button.y, screenOffset.x, screenOffset.y, lineToolLineType );
                        }

                    }
                    else
                        flagged = false;

                    if ( ( toolSelection == 3 && stopped || toolSelection == 3 && paused ) )
                    {
                        screenOffset.prevX = screenOffset.x;
                        screenOffset.prevY = screenOffset.y;

                        if ( toolSelection == 3 && setSecondary == 3 && inputEvents.motion.y < SCREEN_HEIGHT - 64 && inputEvents.motion.x > 80 + 3*64 && inputEvents.motion.x < 80 + 4*64 )
                        {
                            toSpawnIcon.SetVisible( false );
                            screenOffset.x = ( screenOffset.x - ( screenOffset.x - ( -spawn.spawnPosition.x ) ) ) + SCREEN_WIDTH/2 - 12;
                            screenOffset.y = ( screenOffset.y - ( screenOffset.y - ( -spawn.spawnPosition.y ) ) ) + SCREEN_HEIGHT/2 - 12;

                            screenOffset.prevX = screenOffset.x;
                            screenOffset.prevY = screenOffset.y;
                        }
                    }

                    if ( setSecondary == 4 )
                    {
                        uiButtons[12].SetVisible( false );
                        uiButtons[13].SetVisible( false );

                        if ( inputEvents.motion.x > SCREEN_WIDTH-(SCREEN_WIDTH-800)  - 80 - 3*64 && inputEvents.motion.x < SCREEN_WIDTH-(SCREEN_WIDTH-800)  - 80 - 2*64 )
                        {
                            if ( gameCanvas.GetNumberOfLines() > 0 && inputEvents.motion.y < SCREEN_HEIGHT - 64 - 10 && inputEvents.motion.y > SCREEN_HEIGHT - 64 - 10 - 64 )
                            {
                                time_t rawtime;
                                struct tm * timeinfo;
                                char buffer [80];

                                time ( &rawtime );
                                timeinfo = localtime ( &rawtime );

                                strftime (buffer,80,"%m%d%Y-%H%M%S",timeinfo);
                                gameCanvas.SaveMap( buffer, spawn.spawnPosition.x, spawn.spawnPosition.y, spawn.angle, spawn.initialVelocity.vel );
                            }
                            else if ( inputEvents.motion.y < SCREEN_HEIGHT - 64 - 10 - 64 && inputEvents.motion.y > SCREEN_HEIGHT - 64 - 10 - 64 - 64 )
                            {
                                loadMenu.FindFiles();
                                loadMenu.SetVisible( true );
                                for ( int i = 0; i < 8; i++ )
                                {
                                    uiButtons[i].SetVisible( false );
                                }
                                uiButtons[11].SetVisible( false );

                            }
                        }
                    }
                }

                spawn.spawnPosition.prevX = spawn.spawnPosition.x;
                spawn.spawnPosition.prevY = spawn.spawnPosition.y;

                mousePreviousX = -1;
                mousePreviousY = -1;
                mouseDown = false;
                moveSpawn = false;
                setSpawnRotation = false;
                lineToolPressed = false;
                portalToolPressed = false;
                setSecondary = -1;
                toSpawnIcon.SetVisible( false );
            }

            configMenu.InputEvents( &inputEvents );
            if ( loadMenu.isVisible() )
            {
                if ( inputEvents.type == SDL_MOUSEBUTTONDOWN )
                {
                    if ( inputEvents.button.x > 80+64*9 && inputEvents.button.x < 80+64*10 && inputEvents.button.y > SCREEN_HEIGHT - 64 )
                    {
                        loadMenu.SetVisible( false );
                        flagged = true;
                        for ( int i = 0; i < 8; i++ )
                        {
                            uiButtons[i].SetVisible( true );
                        }
                        uiButtons[11].SetVisible( true );
                    }
                    else
                        loadMenu.InputEvents( &inputEvents );
                }
            }
            else if (flagMode)
            {
                if ( inputEvents.type == SDL_MOUSEBUTTONDOWN )
                {
                    if ( inputEvents.button.x > 80+64*9 && inputEvents.button.x < 80+64*10 && inputEvents.button.y > SCREEN_HEIGHT - 64 )
                    {
                        flagMode = false;
                        flagged = true;
                        for ( int i = 0; i < 8; i++ )
                        {
                            uiButtons[i].SetVisible( true );
                        }
                        uiButtons[11].SetVisible( true );
                    }
                    else
                    {
                        flagManager.InputEvents(&inputEvents);
                        ProcessUIClick( inputEvents.button.x, inputEvents.button.y );
                    }
                }
            }
        }
        else
        {
            spawn.spawnPosition.prevX = spawn.spawnPosition.x;
            spawn.spawnPosition.prevY = spawn.spawnPosition.y;

            mousePreviousX = -1;
            mousePreviousY = -1;
            mouseDown = false;
            moveSpawn = false;
            setSpawnRotation = false;
            lineToolPressed = false;
            portalToolPressed = false;
            setSecondary = -1;
            toSpawnIcon.SetVisible( false );
        }
	}

	if(flagMode)
	{
        float ultXoff = ( screenOffset.x - ( screenOffset.x - ( -flagManager.GetCurrentFlag().sledPosition.x*10 ) ) ) + SCREEN_WIDTH/2 - 12;
        float ultYoff = ( screenOffset.y - ( screenOffset.y - ( -flagManager.GetCurrentFlag().sledPosition.y*10 ) ) ) + SCREEN_HEIGHT/2 - 12;

        bool moveX = true;
        bool moveY = true;

        if(screenOffset.x > ultXoff - 10 && screenOffset.x < ultXoff + 10)
            moveX = false;

        if(screenOffset.y > ultYoff - 10 && screenOffset.y < ultYoff + 10)
            moveY = false;

        if(screenOffset.x > ultXoff && moveX)
            screenOffset.x -= (screenOffset.x-ultXoff)/3;
        else if(screenOffset.x < ultXoff && moveX)
            screenOffset.x += (ultXoff-screenOffset.x)/3;

        if(screenOffset.y > ultYoff && moveY)
            screenOffset.y -= (screenOffset.y-ultYoff)/3;
        else if(screenOffset.y < ultYoff && moveY)
            screenOffset.y += (ultYoff-screenOffset.y)/3;

        screenOffset.prevX = screenOffset.x;
        screenOffset.prevY = screenOffset.y;
	}

	if ( scrollLeft )
	{
		screenOffset.x += 20;
		screenOffset.prevX += 20;
	}
	if ( scrollRight )
	{
		screenOffset.x -= 20;
		screenOffset.prevX -= 20;
	}
	if ( scrollUp )
	{
		screenOffset.y += 20;
		screenOffset.prevY += 20;
	}
	if ( scrollDown )
	{
		screenOffset.y -= 20;
		screenOffset.prevY -= 20;
	}

	if ( setSpawnRotation )
	{
		if ( inputEvents.motion.x > ( spawn.spawnPosition.x + screenOffset.x ) - 20 && inputEvents.motion.x < ( spawn.spawnPosition.x + screenOffset.x ) + 20 && inputEvents.motion.y > ( spawn.spawnPosition.y + screenOffset.y ) - 20 && inputEvents.motion.y < ( spawn.spawnPosition.y + screenOffset.y ) + 20 )
		{
			spawn.angle = 0.0f;
		}
		else
		{
			if ( inputEvents.motion.x > ( spawn.spawnPosition.x + screenOffset.x ) )
			{
				float hypo = sqrt( pow( float( inputEvents.motion.x - ( spawn.spawnPosition.x + screenOffset.x ) ), 2 ) + pow( float( inputEvents.motion.y - ( spawn.spawnPosition.y + screenOffset.y ) ), 2 ) );
				spawn.angle = asin( float( inputEvents.motion.y - ( spawn.spawnPosition.y + screenOffset.y ) ) / hypo );
			}
			else
			{
				if ( inputEvents.motion.y > ( spawn.spawnPosition.y + screenOffset.y ) )
				{
					spawn.angle = -atan( ( float( ( spawn.spawnPosition.x + screenOffset.x ) ) - float( inputEvents.motion.x ) ) / ( float( ( spawn.spawnPosition.y + screenOffset.y ) ) - float( inputEvents.motion.y ) ) ) + b2_pi / 2.0f;
				}
				else
				{
					spawn.angle = atan( ( float( ( spawn.spawnPosition.y + screenOffset.y ) ) - float( inputEvents.motion.y ) ) / ( float( ( spawn.spawnPosition.x + screenOffset.x ) ) - float( inputEvents.motion.x ) ) ) + b2_pi;
				}
			}
		}
	}

	if ( setSecondary == 0 )
	{
		if ( inputEvents.motion.y < SCREEN_HEIGHT - 64 )
		{
			setSecondary = 1;
			spawn.initialVelocity.prevVel = spawn.initialVelocity.vel;
		}
	}

	if ( setSecondary == 1 )
	{
		if ( inputEvents.motion.x < 68 + 80 + 4*64 )
		{
			spawn.initialVelocity.vel = float( 406+(SCREEN_HEIGHT-480) - inputEvents.motion.y - 100 );

			if ( spawn.initialVelocity.vel > 100.0f )
				spawn.initialVelocity.vel = 100.0f;

			if ( spawn.initialVelocity.vel < -100.0f )
				spawn.initialVelocity.vel = -100.0f;

			if ( spawn.initialVelocity.vel <= 4.0f && spawn.initialVelocity.vel >= -4.0f )
				spawn.initialVelocity.vel = 0.0f;

			if ( spawn.initialVelocity.vel <= spawn.initialVelocity.prevVel + 4.0f && spawn.initialVelocity.vel >= spawn.initialVelocity.prevVel - 4.0f )
				spawn.initialVelocity.vel = spawn.initialVelocity.prevVel;
		}
	}

	if ( setSecondary == 2 )
	{
		if ( inputEvents.motion.y < SCREEN_HEIGHT - 64 )
		{
			setSecondary = 3;
			if ( toolSelection == 0 )
				pencilPrevLineType = pencilLineType;
			else
				lineToolPrevLineType = lineToolLineType;
		}
	}

	if ( setSecondary == 3 )
	{
		int mouseXPosition = inputEvents.motion.x;
		int mouseYPosition = inputEvents.motion.y;
		if ( toolSelection == 0 )
		{
			if ( mouseXPosition > 84 && mouseXPosition < 140 && mouseYPosition > 346+(SCREEN_HEIGHT-480) && mouseYPosition < 402+(SCREEN_HEIGHT-480) )
				pencilLineType = 0;
			else if ( mouseXPosition > 152 && mouseXPosition < 208 && mouseYPosition > 346+(SCREEN_HEIGHT-480) && mouseYPosition < 402+(SCREEN_HEIGHT-480) )
				pencilLineType = 1;
			else if ( mouseXPosition > 84 && mouseXPosition < 140 && mouseYPosition > 278+(SCREEN_HEIGHT-480) && mouseYPosition < 334+(SCREEN_HEIGHT-480) )
				pencilLineType = 2;
		}
		else if ( toolSelection == 1 )
		{
			if ( mouseXPosition > 84 && mouseXPosition < 140 && mouseYPosition > 346 && mouseYPosition < 402+(SCREEN_HEIGHT-480) )
				lineToolLineType = 1;
			else if ( mouseXPosition > 152 && mouseXPosition < 208 && mouseYPosition > 346+(SCREEN_HEIGHT-480) && mouseYPosition < 402+(SCREEN_HEIGHT-480) )
				lineToolLineType = 0;
			else if ( mouseXPosition > 152 && mouseXPosition < 208 && mouseYPosition > 278+(SCREEN_HEIGHT-480) && mouseYPosition < 334+(SCREEN_HEIGHT-480) )
				lineToolLineType = 2;
		}
		else if ( toolSelection == 3 )
		{

		}
	}

	if ( setSecondary == 4 )
	{
		uiButtons[12].SetVisible( true );
		uiButtons[13].SetVisible( true );
	}

	if ( moveSpawn )
	{
		spawn.spawnPosition.x = spawn.spawnPosition.prevX + inputEvents.motion.x - mousePreviousX;
		spawn.spawnPosition.y = spawn.spawnPosition.prevY + inputEvents.motion.y - mousePreviousY;
	}

	if ( mouseDown )
	{
		if ( toolSelection == 0 )
		{
			if ( gameCanvas.CreateLine( mousePreviousX, mousePreviousY, inputEvents.motion.x, inputEvents.motion.y, screenOffset.x, screenOffset.y, pencilLineType ) )
			{
				mousePreviousX = inputEvents.motion.x;
				mousePreviousY = inputEvents.motion.y;
			}
		}
		else if ( toolSelection == 1 )
		{

		}
		else if ( toolSelection == 2 )
		{
			gameCanvas.DestroyLine( inputEvents.motion.x, inputEvents.motion.y, screenOffset.x, screenOffset.y );
			portalManager.DelPortalAt( inputEvents.motion.x, inputEvents.motion.y, screenOffset.x, screenOffset.y );
		}
		else if ( toolSelection == 3 )
		{
			screenOffset.x = screenOffset.prevX + inputEvents.motion.x - mousePreviousX;
			screenOffset.y = screenOffset.prevY + inputEvents.motion.y - mousePreviousY;
		}
	}
}

void SlysicsCore::ProcessPortals()
{
    Portal curPortal = portalManager.GetPortalAt(int( sledderObject.sledderBodyBody->GetPosition().x * 10.0f) ,int( sledderObject.sledderBodyBody->GetPosition().y * 10.0f ));
    if(!fallenOff && lastPortal.portalPosition.x != curPortal.portalPosition.x && lastPortal.portalPosition.y != curPortal.portalPosition.y && curPortal.ident != -1)
    {
        Portal exit = portalManager.GetExitPortal(portalManager.GetPortalAt(int( sledderObject.sledderBodyBody->GetPosition().x * 10.0f) ,int( sledderObject.sledderBodyBody->GetPosition().y * 10.0f )));
        if(exit.ident != -1)
        {
            lastPortal = exit;
            float curAng = sledObject.sledBody->GetAngle();
            float bCurAng = sledderObject.sledderBodyBody->GetAngle();
            b2Vec2 curVel = sledObject.sledBody->GetLinearVelocity();
            float curAngV = sledObject.sledBody->GetAngularVelocity();
            physicsCore.DestroySled( &sledObject, &sledderObject );
            physicsCore.CreateSled( &sledObject, &sledderObject, exit.portalPosition.x / 10, exit.portalPosition.y / 10, curAng+curPortal.portalAngle*b2_pi/180-exit.portalAngle*b2_pi/180 );

            float linVel = sqrtf(curVel.x * curVel.x + curVel.y * curVel.y);
            float xVel = cos(curAng+curPortal.portalAngle*b2_pi/180-exit.portalAngle*b2_pi/180)*linVel;
            float yVel = sin(curAng+curPortal.portalAngle*b2_pi/180-exit.portalAngle*b2_pi/180)*linVel;
            sledObject.SetVelocity( b2Vec2(xVel, yVel), curAngV);
            sledderObject.SetVelocity( b2Vec2(xVel, yVel), curAngV);

        }
    }
}

void SlysicsCore::SlysicsMainLoop()
{
	while ( !quit )
	{
		Events();

		if ( !stopped && sledObject.created && !paused && sledderObject.sledderBodyBody)
		{
		    ProcessPortals();
			screenOffset.x = ( screenOffset.x - ( screenOffset.x - ( int( -sledderObject.sledderBodyBody->GetPosition().x * 10.0f ) ) ) ) + SCREEN_WIDTH/2;
			screenOffset.y = ( screenOffset.y - ( screenOffset.y - ( int( -sledderObject.sledderBodyBody->GetPosition().y * 10.0f ) ) ) ) + SCREEN_HEIGHT/2;
		}

		Trace();

		if ( !paused )
			physicsCore.StepTime();

		timerCore.UpdateTimers();

		ProcessTimers();
		ProcessLines();

		SledderCrashProcess();
		Render();
	}
}

void SlysicsCore::Trace()
{
	if ( !stopped && !paused )
	{
		if ( configCore.GetVars().traceLine_body && sledderObject.sledderBodyBody )
		{
			sledderBodyVectors.body.x = ( int( sledderObject.sledderBodyBody->GetPosition().x * 10.0f ) );
			sledderBodyVectors.body.y = ( int( sledderObject.sledderBodyBody->GetPosition().y * 10.0f ) );
			float length = sqrt( pow( float( sledderBodyVectors.body.x - sledderBodyVectors.body.prevX ), 2 ) + pow( float( sledderBodyVectors.body.y - sledderBodyVectors.body.prevY ), 2 ) );
			if ( length >= MIN_TRACE_LINE_LENGTH )
			{
				gameCanvas.CreateTraceLine( sledderBodyVectors.body.prevX, sledderBodyVectors.body.prevY, sledderBodyVectors.body.x, sledderBodyVectors.body.y, 0, 200, 255, 255 );
				sledderBodyVectors.body.prevX = sledderBodyVectors.body.x;
				sledderBodyVectors.body.prevY = sledderBodyVectors.body.y;
			}
		}

		if ( configCore.GetVars().traceLine_sled && sledObject.sledBody )
		{
			sledPosition.x = ( int( sledObject.sledBody->GetPosition().x * 10.0f ) );
			sledPosition.y = ( int( sledObject.sledBody->GetPosition().y * 10.0f ) );
			float length = sqrt( pow( float( sledPosition.x - sledPosition.prevX ), 2 ) + pow( float( sledPosition.y - sledPosition.prevY ), 2 ) );
			if ( fallenOff && length >= MIN_TRACE_LINE_LENGTH )
			{
				gameCanvas.CreateTraceLine( sledPosition.prevX, sledPosition.prevY, sledPosition.x, sledPosition.y, 0, 0, 0, 255 );
				sledPosition.prevX = sledPosition.x;
				sledPosition.prevY = sledPosition.y;
			}
		}

		if ( configCore.GetVars().traceLine_hat && sledderObject.sledderHatBody )
		{
			sledderBodyVectors.hat.x = ( int( sledderObject.sledderHatBody->GetPosition().x * 10.0f ) );
			sledderBodyVectors.hat.y = ( int( sledderObject.sledderHatBody->GetPosition().y * 10.0f ) );
			float length = sqrt( pow( float( sledderBodyVectors.hat.x - sledderBodyVectors.hat.prevX ), 2 ) + pow( float( sledderBodyVectors.hat.y - sledderBodyVectors.hat.prevY ), 2 ) );
			if ( hatOff && length >= MIN_TRACE_LINE_LENGTH )
			{
				gameCanvas.CreateTraceLine( sledderBodyVectors.hat.prevX, sledderBodyVectors.hat.prevY, sledderBodyVectors.hat.x, sledderBodyVectors.hat.y, 255, 100, 0, 255 );
				sledderBodyVectors.hat.prevX = sledderBodyVectors.hat.x;
				sledderBodyVectors.hat.prevY = sledderBodyVectors.hat.y;
			}
		}

		if ( headOff && configCore.GetVars().traceLine_head && sledderObject.sledderHeadBody )
		{
			sledderBodyVectors.head.x = ( int( sledderObject.sledderHeadBody->GetPosition().x * 10.0f ) );
			sledderBodyVectors.head.y = ( int( sledderObject.sledderHeadBody->GetPosition().y * 10.0f ) );
			float length = sqrt( pow( float( sledderBodyVectors.head.x - sledderBodyVectors.head.prevX ), 2 ) + pow( float( sledderBodyVectors.head.y - sledderBodyVectors.head.prevY ), 2 ) );
			if ( length >= MIN_TRACE_LINE_LENGTH )
			{
				gameCanvas.CreateTraceLine( sledderBodyVectors.head.prevX, sledderBodyVectors.head.prevY, sledderBodyVectors.head.x, sledderBodyVectors.head.y, 36, 255, 0, 255 );
				sledderBodyVectors.head.prevX = sledderBodyVectors.head.x;
				sledderBodyVectors.head.prevY = sledderBodyVectors.head.y;
			}
		}

		if ( armOff && configCore.GetVars().traceLine_arm && sledderObject.sledderArmBody )
		{
			sledderBodyVectors.arm.x = ( int( sledderObject.sledderArmBody->GetPosition().x * 10.0f ) );
			sledderBodyVectors.arm.y = ( int( sledderObject.sledderArmBody->GetPosition().y * 10.0f ) );
			float length = sqrt( pow( float( sledderBodyVectors.arm.x - sledderBodyVectors.arm.prevX ), 2 ) + pow( float( sledderBodyVectors.arm.y - sledderBodyVectors.arm.prevY ), 2 ) );
			if ( length >= MIN_TRACE_LINE_LENGTH )
			{
				gameCanvas.CreateTraceLine( sledderBodyVectors.arm.prevX, sledderBodyVectors.arm.prevY, sledderBodyVectors.arm.x, sledderBodyVectors.arm.y, 255, 0, 234, 255 );
				sledderBodyVectors.arm.prevX = sledderBodyVectors.arm.x;
				sledderBodyVectors.arm.prevY = sledderBodyVectors.arm.y;
			}
		}

		if ( legOff && configCore.GetVars().traceLine_leg && sledderObject.sledderLegBody )
		{
			sledderBodyVectors.leg.x = ( int( sledderObject.sledderLegBody->GetPosition().x * 10.0f ) );
			sledderBodyVectors.leg.y = ( int( sledderObject.sledderLegBody->GetPosition().y * 10.0f ) );
			float length = sqrt( pow( float( sledderBodyVectors.leg.x - sledderBodyVectors.leg.prevX ), 2 ) + pow( float( sledderBodyVectors.leg.y - sledderBodyVectors.leg.prevY ), 2 ) );
			if ( length >= MIN_TRACE_LINE_LENGTH )
			{
				gameCanvas.CreateTraceLine( sledderBodyVectors.leg.prevX, sledderBodyVectors.leg.prevY, sledderBodyVectors.leg.x, sledderBodyVectors.leg.y, 255, 204, 0, 255 );
				sledderBodyVectors.leg.prevX = sledderBodyVectors.leg.x;
				sledderBodyVectors.leg.prevY = sledderBodyVectors.leg.y;
			}
		}
	}
}

void SlysicsCore::ProcessTimers()
{

}

void SlysicsCore::SledderCrashProcess()
{

	if ( sledObject.sledBody )
		sledVelocity.vel = ( sledObject.sledBody->GetLinearVelocity().x + sledObject.sledBody->GetLinearVelocity().y );
	if ( sledderObject.armToSledJoint != NULL )
	{
		float bodyForce = ( sledderObject.bodyToSledJoint->GetReactionForce( 10.0f ).x + sledderObject.bodyToSledJoint->GetReactionForce( 10.0f ).y ) / 2.0f;
		float armForce = ( sledderObject.armToSledJoint->GetReactionForce( 10.0f ).x + sledderObject.armToSledJoint->GetReactionForce( 10.0f ).y ) / 2.0f;
		float legForce = ( sledderObject.legToSledJoint->GetReactionForce( 10.0f ).x + sledderObject.legToSledJoint->GetReactionForce( 10.0f ).y ) / 2.0f;
		if ( armForce >= FALL_OFF_FORCE || armForce <= -FALL_OFF_FORCE || legForce >= FALL_OFF_FORCE || legForce <= -FALL_OFF_FORCE || bodyForce >= 120.0f || bodyForce <= -120.0f )
		{
			physicsCore.DeleteJoint( sledderObject.armToSledJoint );
			physicsCore.DeleteJoint( sledderObject.legToSledJoint );
			physicsCore.DeleteJoint( sledderObject.bodyToSledJoint );

			sledderObject.bodyToSledJoint = NULL;
			sledderObject.armToSledJoint = NULL;
			sledderObject.legToSledJoint = NULL;

			fallenOff = true;
			sledPosition.prevX = sledObject.sledBody->GetPosition().x * 10.0f;
			sledPosition.prevY = sledObject.sledBody->GetPosition().y * 10.0f;
		}
	}

	if ( sledObject.sledBody != NULL && ( sledVelocity.vel - sledVelocity.prevVel > MAX_SLEDCRUSH_VELOCITY_CHANGE || sledVelocity.vel - sledVelocity.prevVel < -MAX_SLEDCRUSH_VELOCITY_CHANGE ) )
		sledObject.SetCrumpled( true );

	if ( sledderObject.hatToHeadJoint != NULL )
	{
		float force = ( sledderObject.hatToHeadJoint->GetReactionForce( 10.0f ).x + sledderObject.hatToHeadJoint->GetReactionForce( 10.0f ).y ) / 2.0f;
		if ( force >= HAT_FALL_OFF_FORCE || force <= -HAT_FALL_OFF_FORCE )
		{
			physicsCore.DeleteJoint( sledderObject.hatToHeadJoint );
			sledderObject.hatToHeadJoint = NULL;
			hatOff = true;
			sledderBodyVectors.hat.prevX = sledderObject.sledderHatBody->GetPosition().x * 10.0f;
			sledderBodyVectors.hat.prevY = sledderObject.sledderHatBody->GetPosition().y * 10.0f;
		}
	}

	if ( fallenOff && !headOff && sledderObject.headToBodyJoint != NULL )
	{
		float force = ( sledderObject.headToBodyJoint->GetReactionForce( 10.0f ).x + sledderObject.headToBodyJoint->GetReactionForce( 10.0f ).y ) / 2.0f;

		if ( force >= 90.0f || force <= -90.0f )
		{
			physicsCore.DeleteJoint( sledderObject.headToBodyJoint );

			sledderObject.headToBodyJoint = NULL;
			headOff = true;

			sledderBodyVectors.head.prevX = sledderObject.sledderHeadBody->GetPosition().x * 10.0f;
			sledderBodyVectors.head.prevY = sledderObject.sledderHeadBody->GetPosition().y * 10.0f;
		}
	}

	if ( fallenOff && !armOff && sledderObject.armToBodyJoint != NULL )
	{
		float force = ( sledderObject.armToBodyJoint->GetReactionForce( 10.0f ).x + sledderObject.armToBodyJoint->GetReactionForce( 10.0f ).y ) / 2.0f;

		if ( force >= 90.0f || force <= -90.0f )
		{
			physicsCore.DeleteJoint( sledderObject.armToBodyJoint );

			sledderObject.armToBodyJoint = NULL;
			armOff = true;

			sledderBodyVectors.arm.prevX = sledderObject.sledderArmBody->GetPosition().x * 10.0f;
			sledderBodyVectors.arm.prevY = sledderObject.sledderArmBody->GetPosition().y * 10.0f;
		}
	}

	if ( fallenOff && !legOff && sledderObject.legToBodyJoint != NULL )
	{
		float force = ( sledderObject.legToBodyJoint->GetReactionForce( 10.0f ).x + sledderObject.legToBodyJoint->GetReactionForce( 10.0f ).y ) / 2.0f;

		if ( force >= 90.0f || force <= -90.0f )
		{
			physicsCore.DeleteJoint( sledderObject.legToBodyJoint );

			sledderObject.legToBodyJoint = NULL;
			legOff = true;

			sledderBodyVectors.leg.prevX = sledderObject.sledderLegBody->GetPosition().x * 10.0f;
			sledderBodyVectors.leg.prevY = sledderObject.sledderLegBody->GetPosition().y * 10.0f;
		}
	}


	if ( sledderObject.sledderBodyBody )
	{
		float centerX = sledderObject.sledderBodyBody->GetPosition().x * 10.0f;
		float centerY = sledderObject.sledderBodyBody->GetPosition().y * 10.0f;
		if(centerX > 49800.0f || centerX < -49800.0f || centerY > 49800.0f || centerY < -49800.0f)
		{
			physicsCore.DeleteJoint( sledderObject.armToBodyJoint );
			sledderObject.armToBodyJoint = NULL;
			physicsCore.DeleteJoint( sledderObject.headToBodyJoint );
			sledderObject.headToBodyJoint = NULL;
			physicsCore.DeleteJoint( sledderObject.legToBodyJoint );
			sledderObject.legToBodyJoint = NULL;
			physicsCore.DeleteJoint( sledderObject.bodyToSledJoint );
			sledderObject.bodyToSledJoint = NULL;
			physicsCore.DestroyBody( sledderObject.sledderBodyBody );
			sledderObject.sledderBodyBody = NULL;

			sledderObject.bodyImage.SetVisible(false);
		}
	}

	if ( sledObject.sledBody )
	{
		float centerX = sledObject.sledBody->GetPosition().x * 10.0f;
		float centerY = sledObject.sledBody->GetPosition().y * 10.0f;
		if(centerX > 49800.0f || centerX < -49800.0f || centerY > 49800.0f || centerY < -49800.0f)
		{
			physicsCore.DeleteJoint( sledderObject.armToSledJoint );
			physicsCore.DeleteJoint( sledderObject.legToSledJoint );
			physicsCore.DeleteJoint( sledderObject.bodyToSledJoint );

			sledderObject.bodyToSledJoint = NULL;
			sledderObject.armToSledJoint = NULL;
			sledderObject.legToSledJoint = NULL;
			physicsCore.DestroyBody( sledObject.sledBody );
			sledObject.sledBody = NULL;
			sledObject.sledImage.SetVisible(false);
			sledObject.sledCrumpledImage.SetVisible(false);
		}
	}

	if ( sledderObject.sledderHatBody )
	{
		float centerX = sledderObject.sledderHatBody->GetPosition().x * 10.0f;
		float centerY = sledderObject.sledderHatBody->GetPosition().y * 10.0f;
		if(centerX > 49800.0f || centerX < -49800.0f || centerY > 49800.0f || centerY < -49800.0f)
		{
			physicsCore.DeleteJoint( sledderObject.hatToHeadJoint );
			sledderObject.hatToHeadJoint = NULL;
			physicsCore.DestroyBody( sledderObject.sledderHatBody );
			sledderObject.sledderHatBody  = NULL;
			sledderObject.hatImage.SetVisible(false);
		}
	}

	if ( sledderObject.sledderHeadBody )
	{
		float centerX = sledderObject.sledderHeadBody->GetPosition().x * 10.0f;
		float centerY = sledderObject.sledderHeadBody->GetPosition().y * 10.0f;
		if(centerX > 49800.0f || centerX < -49800.0f || centerY > 49800.0f || centerY < -49800.0f)
		{
			physicsCore.DeleteJoint( sledderObject.headToBodyJoint );
			sledderObject.headToBodyJoint = NULL;
			physicsCore.DeleteJoint( sledderObject.hatToHeadJoint );
			sledderObject.hatToHeadJoint = NULL;
			physicsCore.DestroyBody( sledderObject.sledderHeadBody );
			sledderObject.sledderHeadBody = NULL;
			sledderObject.headImage.SetVisible(false);
		}
	}

	if ( sledderObject.sledderArmBody )
	{
		float centerX = sledderObject.sledderArmBody->GetPosition().x * 10.0f;
		float centerY = sledderObject.sledderArmBody->GetPosition().y * 10.0f;
		if(centerX > 49800.0f || centerX < -49800.0f || centerY > 49800.0f || centerY < -49800.0f)
		{
			physicsCore.DeleteJoint( sledderObject.armToBodyJoint );
			sledderObject.armToBodyJoint = NULL;
			physicsCore.DeleteJoint( sledderObject.armToSledJoint );
			sledderObject.armToSledJoint = NULL;
			physicsCore.DestroyBody( sledderObject.sledderArmBody );
			sledderObject.sledderArmBody = NULL;
			sledderObject.armImage.SetVisible(false);
		}
	}

	if ( sledderObject.sledderLegBody )
	{
		float centerX = sledderObject.sledderLegBody->GetPosition().x * 10.0f;
		float centerY = sledderObject.sledderLegBody->GetPosition().y * 10.0f;
		if(centerX > 49800.0f || centerX < -49800.0f || centerY > 49800.0f || centerY < -49800.0f)
		{
			physicsCore.DeleteJoint( sledderObject.legToBodyJoint );
			sledderObject.legToBodyJoint = NULL;
			physicsCore.DeleteJoint( sledderObject.legToSledJoint );
			sledderObject.legToSledJoint = NULL;
			physicsCore.DestroyBody( sledderObject.sledderLegBody );
			sledderObject.sledderLegBody = NULL;
			sledderObject.legImage.SetVisible(false);
		}
	}
}

void SlysicsCore::ProcessLines()
{
	if ( !stopped && !paused )
	{
		if ( physicsCore.GetIfAccelerate( 0 ) )
		{
			float rotatedLinearVel = ( ( sledObject.sledBody->GetLinearVelocity().x * cos( double( sledObject.sledBody->GetAngle() ) ) ) - ( sin( double( sledObject.sledBody->GetAngle() ) ) ) );
			if ( rotatedLinearVel < RED_LINE_MAX_AVERAGE_LINEAR_VELOCITY && rotatedLinearVel > -RED_LINE_MAX_AVERAGE_LINEAR_VELOCITY )
			{
				if ( rotatedLinearVel > 0.0f )
				{
					//float rotatedVelX = ( ( RED_LINE_ACCELERATION_IMPULSE * cos( double( sledObject.sledBody->GetAngle() ) ) ) - ( sin( double( sledObject.sledBody->GetAngle() ) ) ) );
					//float rotatedVelY = ( ( RED_LINE_ACCELERATION_IMPULSE * sin( double( sledObject.sledBody->GetAngle() ) ) ) + ( cos( double( sledObject.sledBody->GetAngle() ) ) ) );
					sledObject.ApplyImpulse( b2Vec2( RED_LINE_ACCELERATION_IMPULSE,0 ) );
				}
				else if ( rotatedLinearVel < 0.0f )
				{
					//float rotatedVelX = ( ( -RED_LINE_ACCELERATION_IMPULSE * cos( double( sledObject.sledBody->GetAngle() ) ) ) - ( sin( double( sledObject.sledBody->GetAngle() ) ) ) );
					//float rotatedVelY = ( ( -RED_LINE_ACCELERATION_IMPULSE * sin( double( sledObject.sledBody->GetAngle() ) ) ) + ( cos( double( sledObject.sledBody->GetAngle() ) ) ) );
					//sledObject.SetVelocity(b2Vec2(sledObject.sledBody->GetLinearVelocity().x - 10, 0), sledObject.sledBody->GetAngle());
					sledObject.ApplyImpulse( b2Vec2( -RED_LINE_ACCELERATION_IMPULSE,0 ) );
				}
			}

		}
		else if ( physicsCore.GetIfDecelerate( 0 ) )
		{
			float rotatedLinearVel = ( ( sledObject.sledBody->GetLinearVelocity().x * cos( double( sledObject.sledBody->GetAngle() ) ) ) - ( sin( double( sledObject.sledBody->GetAngle() ) ) ) );
			if ( rotatedLinearVel >= TAN_LINE_MIN_AVERAGE_LINEAR_VELOCITY || rotatedLinearVel <= -TAN_LINE_MIN_AVERAGE_LINEAR_VELOCITY )
			{
				rotatedLinearVel *= TAN_LINE_DECELERATION_FACTOR;

				sledObject.ApplyImpulse( b2Vec2( sledObject.sledBody->GetLinearVelocity().x*-TAN_LINE_DECELERATION_FACTOR,0 ) );
			}
		}
	}
}
