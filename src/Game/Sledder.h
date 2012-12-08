/*
 * src/Game/Sledder.h
 *
 * Copyright (C) 2011 Wilson Tang.
 *
 * This file is part of Slysics and is free software, distributed,
 * and licensed under the GNU General Public License, version 3.
 *
 * You should have received a copy of the GNU General Public License.
 * If not, see <http://www.gnu.org/licenses/gpl-3.0.html>.
*/

#ifndef SLEDDER_H
#define SLEDDER_H

#include <Box2D/Box2D.h>
#include "../Core/Rendering/ImageObject.h"

class Sledder
{
	public:
		Sledder();
		~Sledder();

		void SetVelocity( b2Vec2 vel, float angVel  );

		void SetPositions( float x, float y, float angle  );

		void SetVisibility( bool co );

		void InitializeSledder();

		//private:
		b2Body* sledderBodyBody;
		b2BodyDef sledderBodyBodyDef;
		b2PolygonShape sledderBodyShape;
		b2FixtureDef sledderBodyFixtureDef;
		b2Fixture *sledderBodyFixture;

		b2Body* sledderLegBody;
		b2BodyDef sledderLegBodyDef;
		b2PolygonShape sledderLegShape;
		b2FixtureDef sledderLegFixtureDef;
		b2Fixture *sledderLegFixture;

		b2Body* sledderArmBody;
		b2BodyDef sledderArmBodyDef;
		b2PolygonShape sledderArmShape;
		b2FixtureDef sledderArmFixtureDef;
		b2Fixture *sledderArmFixture;

		b2Body* sledderHeadBody;
		b2BodyDef sledderHeadBodyDef;
		b2PolygonShape sledderHeadShape;
		b2FixtureDef sledderHeadFixtureDef;
		b2Fixture *sledderHeadFixture;

		b2Body* sledderHatBody;
		b2BodyDef sledderHatBodyDef;
		b2PolygonShape sledderHatShape;
		b2FixtureDef sledderHatFixtureDef;
		b2Fixture *sledderHatFixture;


		b2RevoluteJointDef headToBodyJointDef;
		b2RevoluteJointDef armToBodyJointDef;
		b2RevoluteJointDef legToBodyJointDef;

		b2RevoluteJoint *headToBodyJoint;
		b2RevoluteJoint *armToBodyJoint;
		b2RevoluteJoint *legToBodyJoint;

		b2RevoluteJointDef hatToHeadJointDef;
		b2RevoluteJoint *hatToHeadJoint;


		b2RevoluteJointDef armToSledJointDef;
		b2RevoluteJointDef legToSledJointDef;
		b2RevoluteJointDef bodyToSledJointDef;
		b2RevoluteJoint *armToSledJoint;
		b2RevoluteJoint *legToSledJoint;
		b2RevoluteJoint *bodyToSledJoint;

		ImageObject bodyImage;
		ImageObject headImage;
		ImageObject legImage;
		ImageObject armImage;
		ImageObject hatImage;

		float spawnX;
		float spawnY;

		float headOffsetX;
		float headOffsetY;
		float headJointOffsetX;
		float headJointOffsetY;

		float armOffsetX;
		float armOffsetY;
		float armJointOffsetX;
		float armJointOffsetY;

		float hatOffsetX;
		float hatOffsetY;
		float hatJointOffsetX;
		float hatJointOffsetY;

		float legOffsetX;
		float legOffsetY;
		float legJointOffsetX;
		float legJointOffsetY;

		float armToSledJointOffsetX;
		float armToSledJointOffsetY;

		float legToSledJointOffsetX;
		float legToSledJointOffsetY;


		bool created;

		bool visible;

		int type;
};

#endif
