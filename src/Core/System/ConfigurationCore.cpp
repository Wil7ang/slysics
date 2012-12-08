/*
 * src/Core/System/ConfigurationCore.cpp
 *
 * Copyright (C) 2011 Wilson Tang.
 *
 * This file is part of Slysics and is free software, distributed,
 * and licensed under the GNU General Public License, version 3.
 *
 * You should have received a copy of the GNU General Public License.
 * If not, see <http://www.gnu.org/licenses/gpl-3.0.html>.
*/

#include "ConfigurationCore.h"
#include <stdlib.h>
#include <sys/stat.h>
#include <fstream>


using namespace std;



ConfigurationCore::ConfigurationCore()
{

}

ConfigurationCore::~ConfigurationCore()
{

}

void ConfigurationCore::FillConfigurationList()
{
	configurationList.push_back( pair<string, string>( "screenWidth", "800" ) );
	configurationList.push_back( pair<string, string>( "screenHeight", "480" ) );
	//configurationList.push_back( pair<string, string>( "useGL", "0" ) );
	configurationList.push_back( pair<string, string>( "screenBits", "16" ) );
	configurationList.push_back( pair<string, string>( "traceLine_sled", "1" ) );
	configurationList.push_back( pair<string, string>( "traceLine_body", "1" ) );
	configurationList.push_back( pair<string, string>( "traceLine_head", "1" ) );
	configurationList.push_back( pair<string, string>( "traceLine_arm", "1" ) );
	configurationList.push_back( pair<string, string>( "traceLine_leg", "1" ) );
	configurationList.push_back( pair<string, string>( "traceLine_hat", "1" ) );
	configurationList.push_back( pair<string, string>( "snapToPreviousLine", "1" ) );
	configurationList.push_back( pair<string, string>( "figure", "bobl" ) );
	configurationList.push_back( pair<string, string>( "snapThreshold", "20.0" ) );
}

void ConfigurationCore::WriteConfigurationFile()
{
	ofstream configFileOut;

	string path = getenv( "HOME" );
	path += "/.slysics/slysics.cfg";

	configFileOut.open( path.c_str() );

	for ( unsigned int i = 0; i < configurationList.size(); i++ )
	{
		configFileOut << configurationList[i].first << " " << configurationList[i].second << endl;
	}

	configFileOut.close();
}

/*template <class inClass> void ConfigurationCore::SetVariable( string varName, inClass value )
{
	for ( unsigned int i = 0; i < configurationList.size(); i++ )
	{
		if ( configurationList[i].first == varName )
		{
			configurationList[i].second = xToString( value );
		}
	}
}*/

int ConfigurationCore::LoadConfigurationFile( string FILE )
{
	string path = getenv( "HOME" );
	path += "/.slysics/slysics.cfg";

	ifstream configFileIn( path.c_str() );

	if ( configFileIn.is_open() )
	{

		while ( !configFileIn.eof() )
		{
			string varName;
			string value;
			configFileIn >> varName;
			configFileIn >> value;
			if ( varName.length() > 0 )
			{
				SetVariable( varName, value );
			}
		}

		configFileIn.close();
		return 0;
	}

	return -1;
}

float ConfigurationCore::GetFloatVariable(string varName)
{
	for ( unsigned int i = 0; i < configurationList.size(); i++ )
	{
		if ( configurationList[i].first == varName )
		{
			return atof(configurationList[i].second.c_str());
		}
	}
}

int ConfigurationCore::GetIntegerVariable(string varName)
{
	for ( unsigned int i = 0; i < configurationList.size(); i++ )
	{
		if ( configurationList[i].first == varName )
		{
			return atoi(configurationList[i].second.c_str());
		}
	}
}

bool ConfigurationCore::GetBoolVariable(string varName)
{
	for ( unsigned int i = 0; i < configurationList.size(); i++ )
	{
		if ( configurationList[i].first == varName )
		{
			return atoi(configurationList[i].second.c_str());
		}
	}
}

string ConfigurationCore::GetStringVariable(string varName)
{
	for ( unsigned int i = 0; i < configurationList.size(); i++ )
	{
		if ( configurationList[i].first == varName )
		{
			return configurationList[i].second;
		}
	}
}

void ConfigurationCore::UpdateVars()
{
	configVars.snapThreshold = GetFloatVariable( "snapThreshold" );
	configVars.snapToPreviousLine = GetBoolVariable( "snapToPreviousLine" );
	configVars.traceLine_arm = GetBoolVariable( "traceLine_arm" );
	configVars.traceLine_body = GetBoolVariable( "traceLine_body" );
	configVars.traceLine_hat = GetBoolVariable( "traceLine_hat" );
	configVars.traceLine_head = GetBoolVariable( "traceLine_head" );
	configVars.traceLine_leg = GetBoolVariable( "traceLine_leg" );
	configVars.traceLine_sled = GetBoolVariable( "traceLine_sled" );
}

Vars ConfigurationCore::GetVars()
{
	return configVars;
}
