/*
 * src/Core/System/ConfigurationCore.h
 *
 * Copyright (C) 2011 Wilson Tang.
 *
 * This file is part of Slysics and is free software, distributed,
 * and licensed under the GNU General Public License, version 3.
 *
 * You should have received a copy of the GNU General Public License.
 * If not, see <http://www.gnu.org/licenses/gpl-3.0.html>.
*/

#ifndef CONFIGURATIONCORE_H
#define CONFIGURATIONCORE_H

#include <vector>
#include <string>
#include <sstream>
#include <stdlib.h>

using namespace std;

template <class inClass> string xToString ( inClass input )
{
	stringstream tSStream;
	tSStream << input;
	return tSStream.str();
}

struct Vars
{
	bool traceLine_sled;
	bool traceLine_body;
	bool traceLine_head;
	bool traceLine_arm;
	bool traceLine_leg;
	bool traceLine_hat;
	bool snapToPreviousLine;
	float snapThreshold;
};

class ConfigurationCore
{
	public:
		ConfigurationCore();
		~ConfigurationCore();

		void FillConfigurationList();
		int LoadConfigurationFile( string FILENAME = "" );
		void WriteConfigurationFile();

		float GetFloatVariable( string varName );
		bool GetBoolVariable( string varName );
		string GetStringVariable( string varName );
		int GetIntegerVariable( string varName );

		template <class inClass> void SetVariable ( string varName, inClass value )
		{
			for ( unsigned int i = 0; i < configurationList.size(); i++ )
			{
				if ( configurationList[i].first == varName )
				{
					configurationList[i].second = xToString( value );
				}
			}
		}

		Vars GetVars();
		void UpdateVars();
	private:
		vector<pair< string, string> > configurationList;
		string configurationFilename;

		Vars configVars;
};

#endif
