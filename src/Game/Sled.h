/*
 * src/Game/Sled.h
 *
 * Copyright (C) 2011 Wilson Tang.
 *
 * This file is part of Slysics and is free software, distributed,
 * and licensed under the GNU General Public License, version 3.
 *
 * You should have received a copy of the GNU General Public License.
 * If not, see <http://www.gnu.org/licenses/gpl-3.0.html>.
*/

#ifndef SLED_H
#define SLED_H

#include <Box2D/Box2D.h>
#include "../Core/Rendering/ImageObject.h"

class Sled
{
	public:
		Sled();
		~Sled();

		void SetVelocity( b2Vec2 vel, float angVel );

		void ApplyImpulse( b2Vec2 impulse );

		void SetPositions(float x, float y, float angle);

		void SetCrumpled( bool co );

		void InitializeSled();

	//private:
		b2Body* sledBody;
		b2BodyDef sledBodyDef;

		b2FixtureDef sledBottomFixtureDef;
        b2Fixture *sledBottomFixture;
        b2FixtureDef sledFrontFixtureDef;
        b2Fixture *sledFrontFixture;

		b2PolygonShape sledBottomShape;
		b2CircleShape sledFrontShape;

		ImageObject sledImage;
		ImageObject sledCrumpledImage;

		float spawnX;
		float spawnY;

		bool created;

		bool crumpled;

		int type;
};

#endif
