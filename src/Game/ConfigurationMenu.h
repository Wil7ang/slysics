/*
 * src/Game/ConfigurationMenu.h
 *
 * Copyright (C) 2011 Wilson Tang.
 *
 * This file is part of Slysics and is free software, distributed,
 * and licensed under the GNU General Public License, version 3.
 *
 * You should have received a copy of the GNU General Public License.
 * If not, see <http://www.gnu.org/licenses/gpl-3.0.html>.
*/

#ifndef CONFIGURATIONMENU_H
#define CONFIGURATIONMENU_H

#include "SDL/SDL.h"
#include "../Core/GUI/Widgets/RadioButton.h"
#include "../Core/Rendering/RenderingCore.h"
#include "../Core/Rendering/TTFFont.h"
#include "../Core/Rendering/TextLabel.h"
#include "../Core/System/ConfigurationCore.h"


class ConfigurationMenu
{
	public:
		ConfigurationMenu();
		~ConfigurationMenu();

		void SetupMenu(ConfigurationCore *cCore_);

		void InputEvents(SDL_Event *event);
		void RenderMenu(SDL_Surface *screen);
		void SetVisible(bool in);
		bool isVisible();
	private:
		bool visibility;

		TTFFont fontSans18;
		TTFFont fontSans20;
		TTFFont fontSans32;

		TextLabel dialogTitleLabel;
		TextLabel traceLinesLabel;
		TextLabel traceLineBodyLabel;
		TextLabel traceLineSledLabel;
		TextLabel traceLineHatLabel;
		TextLabel traceLineHeadLabel;
		TextLabel traceLineArmLabel;
		TextLabel traceLineLegLabel;

		RadioButton traceLineBodyRadio;
		RadioButton traceLineSledRadio;
		RadioButton traceLineHatRadio;
		RadioButton traceLineHeadRadio;
		RadioButton traceLineArmRadio;
		RadioButton traceLineLegRadio;

		TextLabel lineSnapLabel;
		RadioButton lineSnapRadio;

		ConfigurationCore *cCore;
};

#endif
