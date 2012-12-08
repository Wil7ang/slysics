/*
 * src/Core/Physics/PhysicsCore.h
 *
 * Copyright (C) 2011 Wilson Tang.
 *
 * This file is part of Slysics and is free software, distributed,
 * and licensed under the GNU General Public License, version 3.
 *
 * You should have received a copy of the GNU General Public License.
 * If not, see <http://www.gnu.org/licenses/gpl-3.0.html>.
*/

#ifndef PHYSICSCORE_H
#define PHYSICSCORE_H

#include <Box2D/Box2D.h>
#include "../../Game/Sled.h"
#include "../../Game/Sledder.h"
#include "../../Game/Line.h"
#include <vector>

using std::vector;

class PhysicsCoreContactListener : public b2ContactListener
{
	public:
		PhysicsCoreContactListener() { sledAccelerate = false; sledDecelerate = false; sledderAccelerate = false; sledderDecelerate = false; }
        ~PhysicsCoreContactListener() {}


		void BeginContact ( b2Contact* contact );

		void EndContact( b2Contact* contact );

		void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {}

		void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {}

		bool sledAccelerate;
		bool sledDecelerate;
		bool sledderAccelerate;
		bool sledderDecelerate;
};

class PhysicsCore
{
	public:
		PhysicsCore();
		~PhysicsCore();

		void StepTime();

		void AddLineList( vector<Line> *lnList );
		void DeleteLine( int ID );
		void CreateLine();

		void CreateSled( Sled *sled, Sledder *sledder, float x, float y, float angle );
		void DestroySled( Sled *sled, Sledder *sledder );
		void DeleteJoint( b2Joint *joint );

		bool GetIfAccelerate(int type);
		bool GetIfDecelerate(int type);

		void DestroyBody(b2Body *bdy);

		void SetSimulationSpeed( float factor );
	private:
		b2World *world;

		PhysicsCoreContactListener contactListener;

		float32 timeStep;
		int32 iterations;

		vector<Line> *linesList;

		//b2BodyDef wallBodyDef[4];
		//b2Body* wallBody[4];
};

#endif
