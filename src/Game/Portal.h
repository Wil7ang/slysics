#include "../Core/Rendering/TextLabel.h"
#include <Box2D/Box2D.h>
#include <vector>
#include "SDL/SDL.h"
#include "../Core/Rendering/ImageObject.h"
#include "../Core/Rendering/RenderingCore.h"

struct Portal
{
    public:
        Portal() {portalAngle = 0.0f; ident = -1;};
        Portal(int xLoc, int yLoc, float pAngle, int ID){portalAngle = pAngle; portalPosition.Set(xLoc,yLoc); ident = ID;}
        ~Portal(){}

        float portalAngle;
        b2Vec2 portalPosition;
        int ident;
};

class PortalManager
{
    public:
        PortalManager();
        ~PortalManager();

        int AddPortal(int xLoc, int yLoc, float angle);//Every third portal is unique.. use this function for both enter and exit portals
        void DelPortalAt( int mX, int mY, int srOx, int srOy ); //Also deletes the other portal in the group
        Portal GetPortalAt(int xLoc, int yLoc);
        Portal GetExitPortal(Portal enterPortal);
        void Initialize();

        void ClearPortals();

        void RenderPortals(RenderingCore *rCore, int srOx, int srOy);

        ImageObject pImage;

        vector <Portal> portalList;
};
