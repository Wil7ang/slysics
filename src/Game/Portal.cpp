#include "Portal.h"
#include <sstream>

PortalManager::PortalManager()
{

}

PortalManager::~PortalManager()
{

}

void PortalManager::Initialize()
{
    pImage.LoadImage("data/portal.png");
}

int PortalManager::AddPortal(int xLoc, int yLoc, float angle)
{

    if(portalList.size()==0)
        portalList.push_back(Portal(xLoc, yLoc, angle, portalList.size()));
    else if(portalList.size()==1)
        portalList.push_back(Portal(xLoc, yLoc, angle, portalList.size()-1));
    else if(portalList.size()%2 == 0)
        portalList.push_back(Portal(xLoc, yLoc, angle, portalList.size()));
    else
        portalList.push_back(Portal(xLoc, yLoc, angle, portalList.size()-1));
}

Portal PortalManager::GetPortalAt(int xLoc, int yLoc)
{
    for(int i = 0;i<portalList.size();i++)
    {
        if(xLoc >= portalList[i].portalPosition.x-32 && xLoc <= portalList[i].portalPosition.x+32 && yLoc >= portalList[i].portalPosition.y-32 && yLoc <= portalList[i].portalPosition.y+32)
            return portalList[i];
    }

    return Portal(0, 0, 0, -1);
}

Portal PortalManager::GetExitPortal(Portal enterPortal)
{
    for(int i = 0; i<portalList.size();i++)
    {
        if(portalList[i].ident == enterPortal.ident && portalList[i].portalPosition.x != enterPortal.portalPosition.x)
            return portalList[i];
    }

    return Portal(0, 0, 0, -1);
}

void PortalManager::ClearPortals()
{
    portalList.clear();
}

void PortalManager::DelPortalAt( int mX, int mY, int srOx, int srOy )
{
    bool deletedFirst = false;
    int ident = -1;
    for(unsigned int i = 0; i<portalList.size();i++)
    {
        if(!deletedFirst)
        {
            float centerX = portalList[i].portalPosition.x + srOx;
            float centerY = portalList[i].portalPosition.y + srOy;

            if(centerX > mX-10 && centerX < mX+10 && centerY > mY-10 && centerY < mY+10)
            {

                ident = portalList[i].ident;
                portalList.erase(portalList.begin()+i);
                i = 0;

                if(portalList.size() == 1 || ident == 0)
                    i=-1;

                deletedFirst = true;
            }
        }
        else if(deletedFirst)
        {
            if(portalList[i].ident == ident)
            {
                portalList.erase(portalList.begin()+i);
                break;
            }
        }
    }
}

void PortalManager::RenderPortals(RenderingCore *rCore, int srOx, int srOy)
{
    for ( unsigned int i = 0; i < portalList.size(); i++ )
	{
	    SDL_Rect imageBox;
	    imageBox.w = 64+40;
	    imageBox.h = 64+40;
	    imageBox.x = portalList[i].portalPosition.x-104/2 + srOx-20;
	    imageBox.y = portalList[i].portalPosition.y-104/2 + srOy-20;
	    pImage.SetAngle(portalList[i].portalAngle);
		pImage.SetPosition(portalList[i].portalPosition.x + srOx, portalList[i].portalPosition.y + srOy);


		//if ( flagsList[i].sledPosition.x + srOx + 64 > 0 && flagsList[i].sledPosition.x + srOx < SCREEN_WIDTH && flagsList[i].sledPosition.y + srOy + 64 > 0 && flagsList[i].sledPosition.y + srOy < SCREEN_HEIGHT )
		{
			pImage.Render(rCore->ReturnScreenPointer());
			//rCore->AppendUpdateRect(imageBox);

			std::stringstream str;
			str << portalList[i].ident;
			stringRGBA( rCore->ReturnScreenPointer(), portalList[i].portalPosition.x-104/2 + srOx-20+42, portalList[i].portalPosition.y-104/2 + srOy-20+42, str.str().c_str(), 0, 0, 0, 255 );
		}
	}
}






