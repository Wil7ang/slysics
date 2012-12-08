/*
 * src/Game/LoadMenu.h
 *
 * Copyright (C) 2011 Wilson Tang.
 *
 * This file is part of Slysics and is free software, distributed,
 * and licensed under the GNU General Public License, version 3.
 *
 * You should have received a copy of the GNU General Public License.
 * If not, see <http://www.gnu.org/licenses/gpl-3.0.html>.
*/

#ifndef LOADMENU_H
#define LOADMENU_H

#include "SDL/SDL.h"
#include "../Core/Rendering/RenderingCore.h"
#include "../Core/Rendering/TTFFont.h"
#include "../Core/Rendering/TextLabel.h"
#include "GameCanvas.h"

#include <vector>

using namespace std;

class LoadMenu
{
	public:
		LoadMenu();
		~LoadMenu();

		void SetupMenu(GameCanvas *gCanv, Spawn *spwn);
		void InputEvents(SDL_Event *event);
		void RenderMenu(SDL_Surface *screen);
		void SetVisible(bool in);
		bool isVisible();

		void LoadMap();

		void FindFiles();
		static int FoundFile( const char *fpath, const struct stat *sb, int typeflag );

		//vector<pair<string, string> > mapFileNames;
		//vector<pair<string, string> > scrFileNames;
		//vector<pair<string, string> > mapsList;
		vector<string> mapFileNames;
	private:
		bool visibility;
		GameCanvas *gCanvas;
		Spawn *spawn;

		int selection;

		//bool imageVisibility;

		TTFFont fontSans20;
		TextLabel filenameLabel;

		//ImageObject *tImage;
};

#endif
