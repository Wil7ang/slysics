/*
 * src/Game/GameCanvas.cpp
 *
 * Copyright (C) 2011 Wilson Tang.
 *
 * This file is part of Slysics and is free software, distributed,
 * and licensed under the GNU General Public License, version 3.
 *
 * You should have received a copy of the GNU General Public License.
 * If not, see <http://www.gnu.org/licenses/gpl-3.0.html>.
*/

#include "GameCanvas.h"
#include <cmath>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <sys/stat.h>

using namespace std;

GameCanvas::GameCanvas()
{
	physicsCore = NULL;
	bodyDistanceTraveled = 0.0f;
}

GameCanvas::~GameCanvas()
{
	ClearCanvas();
	physicsCore = NULL;
}

int GameCanvas::GetClosestLineX( int x, int y, int srOx, int srOy )
{
	for ( unsigned int i = 0; i < linesList.size(); i++ )
	{
		if ( ( x > linesList[i].lineX1 - 20 + srOx && x < linesList[i].lineX1 + 20 + srOx ) && ( y > linesList[i].lineY1 - 20 + srOy && y < linesList[i].lineY1 + 20 + srOy ) )
		{
			x = linesList[i].lineX1 + srOx;
		}
		else if ( ( x > linesList[i].lineX2 - 20 + srOx && x < linesList[i].lineX2 + 20 + srOx ) && ( y > linesList[i].lineY2 - 20 + srOy && y < linesList[i].lineY2 + 20 + srOy ) )
		{
			x = linesList[i].lineX2 + srOx;
		}
	}

	return x;
}

int GameCanvas::GetClosestLineY( int x, int y, int srOx, int srOy )
{
	for ( unsigned int i = 0; i < linesList.size(); i++ )
	{
		if ( ( y > linesList[i].lineY1 - 20 + srOy && y < linesList[i].lineY1 + 20 + srOy ) && ( x > linesList[i].lineX1 - 20 + srOx && x < linesList[i].lineX1 + 20 + srOx ) )
		{
			y = linesList[i].lineY1 + srOy;
		}
		else if ( ( y > linesList[i].lineY2 - 20 + srOy && y < linesList[i].lineY2 + 20 + srOy ) && ( x > linesList[i].lineX2 - 20 + srOx && x < linesList[i].lineX2 + 20 + srOx ) )
		{
			y = linesList[i].lineY2 + srOy;
		}
	}

	return y;
}



bool GameCanvas::CreateLine( int pX, int pY, int x, int y, int srOx, int srOy, int type )
{
	if ( ( pX + srOx < 49900 && pX + srOx > -49900 && pY + srOy < 49900 && pY + srOy > -49900 ) && ( x + srOx < 49900 && x + srOx > -49900 && y + srOy < 49900 && y + srOy > -49900 ) )
	{
		float length = sqrt( pow( float(x - pX), 2 ) + pow( float(y - pY), 2 ) );

		if ( length >= 5.0f )
		{
			Line temp;
			linesList.push_back( temp );

			linesList[linesList.size()-1].lineSaveData.Set( pX, pY, x, y, srOx, srOy, type );

			linesList[linesList.size()-1].lineX1 = pX - srOx;
			linesList[linesList.size()-1].lineX2 = x - srOx;
			linesList[linesList.size()-1].lineY1 = pY - srOy;
			linesList[linesList.size()-1].lineY2 = y - srOy;

			float cx1 = pX / 10.0f - srOx / 10.0f;
			float cy1 = pY / 10.0f - srOy / 10.0f;
			float cx2 = x / 10.0f - srOx / 10.0f;
			float cy2 = y / 10.0f - srOy / 10.0f;

			float length = sqrt( pow( float(cx2 - cx1), 2 ) + pow( float(cy2 - cy1), 2 ) );
			float centerX = ( cx1 + cx2 ) / 2;
			float centerY = ( cy1 + cy2 ) / 2;
			//printf("%f, %f\n", centerX*10.0f, centerY*10.0f);
			float angle = atan( ( cy2 - cy1 ) / ( cx2 - cx1 ) );

			linesList[linesList.size()-1].lineBodyDef.position.Set( centerX, centerY );
			linesList[linesList.size()-1].lineBodyDef.angle = angle;
			linesList[linesList.size()-1].lineShape.SetAsBox( length / 2.0f, 0.15f );
			linesList[linesList.size()-1].lineFixtureDef.shape = &linesList[linesList.size()-1].lineShape;
			linesList[linesList.size()-1].lineFixtureDef.density = 1.0f;
			linesList[linesList.size()-1].lineFixtureDef.friction = 0.0f;
			linesList[linesList.size()-1].type = type;

			linesList[linesList.size()-1].lineFixtureDef.userData = ( void* )linesList[linesList.size()-1].type;

			physicsCore->CreateLine();



			int x1 = pX - 1;
			int y1 = pY - 1;
			int x2 = x - 1;
			int y2 = y - 1;

			linesList[linesList.size()-1].lineBox.w = abs( x2 - x1 ) + 3;
			linesList[linesList.size()-1].lineBox.h = abs( y2 - y1 ) + 3;
			linesList[linesList.size()-1].lineSurface = SDL_CreateRGBSurface( SDL_SWSURFACE, abs( x2 - x1 ) + 3, abs( y2 - y1 ) + 3, 16, 0, 0, 0, 0 );
			SDL_FillRect( linesList[linesList.size()-1].lineSurface , &linesList[linesList.size()-1].lineSurface ->clip_rect, SDL_MapRGB( linesList[linesList.size()-1].lineSurface ->format, 220, 220, 220 ) );
			Uint32 colorkey = SDL_MapRGB( linesList[linesList.size()-1].lineSurface->format, 220, 220, 220 );
			SDL_SetColorKey( linesList[linesList.size()-1].lineSurface, SDL_SRCCOLORKEY, colorkey );

			int localX1 = 0;
			int localY1 = 0;
			int localX2 = 0;
			int localY2 = 0;

			if ( x1 < x2 )
			{
				linesList[linesList.size()-1].lineBox.x = x1 - srOx;
				localX1 = 1;
				localX2 = abs( x2 - x1 ) + 1;
			}
			else
			{
				linesList[linesList.size()-1].lineBox.x = x2 - srOx;
				localX1 = abs( x2 - x1 ) + 1;
				localX2 = 1;
			}

			if ( y1 < y2 )
			{
				linesList[linesList.size()-1].lineBox.y = y1 - srOy;
				localY1 = 1;
				localY2 = abs( y2 - y1 ) + 1;
			}
			else
			{
				linesList[linesList.size()-1].lineBox.y = y2 - srOy;
				localY1 = abs( y2 - y1 ) + 1;
				localY2 = 1;
			}

			int roy = 0;
			int gee = 0;
			int bib = 0;

			if ( type == 0 )
			{
				roy = 34;
				gee = 99;
				bib = 27;
			}
			else if ( type == 1 )
			{
				roy = 162;
				gee = 152;
				bib = 105;
			}
			else if ( type == 2 )
			{
				roy = 255;
				gee = 114;
				bib = 0;
			}

			lineRGBA( linesList[linesList.size()-1].lineSurface, localX1    , localY1    , localX2    , localY2    , roy, gee, bib, 255 );
			aalineRGBA( linesList[linesList.size()-1].lineSurface, localX1 + 1, localY1 + 1, localX2 + 1, localY2 + 1, roy, gee, bib, 255 );
			aalineRGBA( linesList[linesList.size()-1].lineSurface, localX1 + 1, localY1 - 1, localX2 + 1, localY2 - 1, roy, gee, bib, 255 );
			lineRGBA( linesList[linesList.size()-1].lineSurface, localX1 + 1, localY1    , localX2 + 1, localY2    , roy, gee, bib, 255 );
			aalineRGBA( linesList[linesList.size()-1].lineSurface, localX1 - 1, localY1 + 1, localX2 - 1, localY2 + 1, roy, gee, bib, 255 );
			aalineRGBA( linesList[linesList.size()-1].lineSurface, localX1 - 1, localY1 - 1, localX2 - 1, localY2 - 1, roy, gee, bib, 255 );
			lineRGBA( linesList[linesList.size()-1].lineSurface, localX1 - 1, localY1    , localX2 - 1, localY2    , roy, gee, bib, 255 );
			lineRGBA( linesList[linesList.size()-1].lineSurface, localX1    , localY1 + 1, localX2    , localY2 + 1, roy, gee, bib, 255 );
			lineRGBA( linesList[linesList.size()-1].lineSurface, localX1    , localY1 - 1, localX2    , localY2 - 1, roy, gee, bib, 255 );

			return true;
		}
		else
			return false;
	}
	return false;
}

void GameCanvas::DestroyLine( int mX, int mY, int srOx, int srOy )
{
	for ( unsigned int i = 0; i < linesList.size(); i++ )
	{
		float centerX = linesList[i].lineBody->GetPosition().x * 10.0f + float( srOx );
		float centerY = linesList[i].lineBody->GetPosition().y * 10.0f + float( srOy );

		if ( centerX > mX - 10 && centerX < mX + 10 && centerY > mY - 10 && centerY < mY + 10 )
		{
			physicsCore->DeleteLine( i );
			SDL_FreeSurface( linesList[i].lineSurface );
			linesList[i].lineSurface = NULL;
			linesList.erase( linesList.begin() + i );
			break;
		}
	}
}

float GameCanvas::GetDistanceTraveled()
{
	return bodyDistanceTraveled;
}

void GameCanvas::CreateTraceLine( int pX, int pY, int x, int y, int roy, int gee, int bib, int alp )
{
	if ( ( pX < 49900 && pX > -49900 && pY < 49900 && pY > -49900 ) && ( x < 49900 && x > -49900 && y < 49900 && y > -49900 ) )
	{
		float length = sqrt( pow( float(x - pX), 2 ) + pow( float(y - pY), 2 ) );

		if(roy == 0, gee == 200, bib == 255)
			bodyDistanceTraveled += abs(length);

		if ( length >= MIN_TRACE_LINE_LENGTH && traceLinesList.size() < MAX_TRACE_LINES )
		{
			TraceLine temp;
			traceLinesList.push_back( temp );

			int x1 = pX;
			int y1 = pY;
			int x2 = x;
			int y2 = y;

			traceLinesList[traceLinesList.size()-1].lineBox.w = abs( x2 - x1 ) + 3;
			traceLinesList[traceLinesList.size()-1].lineBox.h = abs( y2 - y1 ) + 3;
			traceLinesList[traceLinesList.size()-1].lineSurface = SDL_CreateRGBSurface( SDL_SWSURFACE, abs( x2 - x1 ) + 3, abs( y2 - y1 ) + 3, 16, 0, 0, 0, 0 );
			SDL_FillRect( traceLinesList[traceLinesList.size()-1].lineSurface , &traceLinesList[traceLinesList.size()-1].lineSurface ->clip_rect, SDL_MapRGB( traceLinesList[traceLinesList.size()-1].lineSurface ->format, 220, 220, 220 ) );
			Uint32 colorkey = SDL_MapRGB( traceLinesList[traceLinesList.size()-1].lineSurface->format, 220, 220, 220 );
			SDL_SetColorKey( traceLinesList[traceLinesList.size()-1].lineSurface, SDL_SRCCOLORKEY, colorkey );

			int localX1 = 0;
			int localY1 = 0;
			int localX2 = 0;
			int localY2 = 0;

			if ( x1 < x2 )
			{
				traceLinesList[traceLinesList.size()-1].lineBox.x = x1;
				localX1 = 1;
				localX2 = abs( x2 - x1 ) + 1;
			}
			else
			{
				traceLinesList[traceLinesList.size()-1].lineBox.x = x2;
				localX1 = abs( x2 - x1 ) + 1;
				localX2 = 1;
			}

			if ( y1 < y2 )
			{
				traceLinesList[traceLinesList.size()-1].lineBox.y = y1;
				localY1 = 1;
				localY2 = abs( y2 - y1 ) + 1;
			}
			else
			{
				traceLinesList[traceLinesList.size()-1].lineBox.y = y2;
				localY1 = abs( y2 - y1 ) + 1;
				localY2 = 1;
			}


			aalineRGBA( traceLinesList[traceLinesList.size()-1].lineSurface, localX1    , localY1    , localX2    , localY2    , roy, gee, bib, alp );


		}
	}
}


void GameCanvas::ClearCanvas()
{
	for ( unsigned int i = 0; i < linesList.size(); i++ )
	{
		if ( linesList[i].lineSurface != NULL )
		{
			SDL_FreeSurface( linesList[i].lineSurface );
			linesList[i].lineSurface = NULL;
		}
		if ( linesList[i].lineBody != NULL )
		{
			physicsCore->DeleteLine( i );
		}
	}
	linesList.clear();
}

void GameCanvas::ClearTraceLines()
{
	for ( unsigned int i = 0; i < traceLinesList.size(); i++ )
	{
		if ( traceLinesList[i].lineSurface != NULL )
		{
			SDL_FreeSurface( traceLinesList[i].lineSurface );
			traceLinesList[i].lineSurface = NULL;
		}
	}
	traceLinesList.clear();
	bodyDistanceTraveled = 0.0f;
}

void GameCanvas::SetPhysicsCore( PhysicsCore *pCore )
{
	physicsCore = pCore;
	physicsCore->AddLineList( &linesList );
}

void GameCanvas::RenderCanvas( RenderingCore *rCore, int srOx, int srOy )
{
	for ( unsigned int i = 0; i < linesList.size(); i ++ )
	{
		SDL_Rect tRect = linesList[i].lineBox;
		tRect.x = tRect.x + srOx;
		tRect.y = tRect.y + srOy;

		if ( tRect.x + tRect.w > 0 && tRect.x < SCREEN_WIDTH && tRect.y + tRect.h > 0 && tRect.y < SCREEN_HEIGHT )
		{
			SDL_BlitSurface( linesList[i].lineSurface, NULL, rCore->ReturnScreenPointer(), &tRect );
			rCore->AppendUpdateRect( tRect );
		}
	}
}

void GameCanvas::RenderTraceLines( RenderingCore *rCore, int srOx, int srOy )
{
	for ( unsigned int i = 0; i < traceLinesList.size(); i ++ )
	{
		SDL_Rect tRect = traceLinesList[i].lineBox;
		tRect.x = tRect.x + srOx;
		tRect.y = tRect.y + srOy;

		if ( tRect.x + tRect.w > 0 && tRect.x < SCREEN_WIDTH && tRect.y + tRect.h > 0 && tRect.y < SCREEN_HEIGHT )
		{
			SDL_BlitSurface( traceLinesList[i].lineSurface, NULL, rCore->ReturnScreenPointer(), &tRect );
			rCore->AppendUpdateRect( tRect );
		}
	}
}

void GameCanvas::SaveMap( string fileName, int spawnX, int spawnY, float spawnAngle, float initialVelocity )
{
	if ( linesList.size() > 0 && fileName.length() > 0)
	{
		int minX = linesList[0].lineBox.x;
		int minY = linesList[0].lineBox.y;
		int maxX = linesList[0].lineBox.x + linesList[0].lineBox.w;
		int maxY = linesList[0].lineBox.y + linesList[0].lineBox.h;

		for ( unsigned int i = 0; i < linesList.size(); i++ )
		{
			if ( linesList[i].lineBox.x < minX )
				minX = linesList[i].lineBox.x;
			if ( linesList[i].lineBox.y < minY )
				minY = linesList[i].lineBox.y;

			if ( linesList[i].lineBox.x + linesList[i].lineBox.w > maxX )
				maxX = linesList[i].lineBox.x + linesList[i].lineBox.w;
			if ( linesList[i].lineBox.y + linesList[i].lineBox.h > maxY )
				maxY = linesList[i].lineBox.y + linesList[i].lineBox.h;
		}

		//SDL_Surface *screenshotSurface = SDL_CreateRGBSurface( SDL_SWSURFACE, maxX - minX + 100, maxY - minY + 100, 16, 0, 0, 0, 0 );
		//SDL_FillRect( screenshotSurface, &screenshotSurface->clip_rect, SDL_MapRGB( screenshotSurface->format, 220, 220, 220 ) );
		std::ofstream mapFile;

		string filename = getenv( "HOME" );
		filename = filename + "/.slysics/maps/" + fileName+".map";
		mapFile.open( filename.c_str() );

		mapFile << spawnX << " " << spawnY << " " << spawnAngle << " " << initialVelocity << endl;

		for ( unsigned int i = 0; i < linesList.size(); i++ )
		{
			//SDL_Rect tRect = linesList[i].lineBox;
			//tRect.x = tRect.x - minX + 50;
			//tRect.y = tRect.y - minY + 50;

			//SDL_BlitSurface( linesList[i].lineSurface, NULL, screenshotSurface, &tRect );

			mapFile << linesList[i].lineSaveData.pX << " " << linesList[i].lineSaveData.pY << " " << linesList[i].lineSaveData.x << " " << linesList[i].lineSaveData.y << " " << linesList[i].lineSaveData.srOx << " " << linesList[i].lineSaveData.srOy << " " << linesList[i].lineSaveData.type << endl;
		}
		mapFile.close();
/*
		filename = getenv( "HOME" );
		filename = filename + "/.slysics/scrs/" + filename + ".png";
		IMG_SavePNG(filename.c_str(),  screenshotSurface, 9);

		float scaleFactor = 0.0f;

		if( screenshotSurface->w > 500 && screenshotSurface->h < 300)
			scaleFactor = 500.0f/float(screenshotSurface->w);
		else if ( screenshotSurface->w < 500 && screenshotSurface->h > 300)
			scaleFactor = 300.0f/float(screenshotSurface->h);
		else if ( screenshotSurface->w > screenshotSurface->h)
			scaleFactor = 500.0f/float(screenshotSurface->w);
		else if ( screenshotSurface->w < screenshotSurface->h)
			scaleFactor = 300.0f/float(screenshotSurface->h);

		ImageObject tempMapScreen;
		tempMapScreen.LoadImage(filename, false);
		tempMapScreen.SetScale(scaleFactor);
		IMG_SavePNG(filename.c_str(), tempMapScreen.GetProcessedImageSurface(), 9);

		SDL_FreeSurface( screenshotSurface );
		screenshotSurface = NULL;*/
	}
}

int GameCanvas::GetNumberOfLines()
{
	return linesList.size();
}

int GameCanvas::GetNumberOfTraceLines()
{
	return traceLinesList.size();
}
