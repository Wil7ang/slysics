/*
 * src/Game/Sledder.cpp
 *
 * Copyright (C) 2011 Wilson Tang.
 *
 * This file is part of Slysics and is free software, distributed,
 * and licensed under the GNU General Public License, version 3.
 *
 * You should have received a copy of the GNU General Public License.
 * If not, see <http://www.gnu.org/licenses/gpl-3.0.html>.
*/

#include "Sledder.h"

Sledder::Sledder()
{
	visible = true;
	created = false;
	spawnX = -0.3f;
	spawnY = -0.6f;

	sledderBodyBody = NULL;
	sledderBodyBodyDef.position.Set( spawnX, spawnY );
	sledderBodyBodyDef.type = b2_dynamicBody;
	sledderBodyShape.SetAsBox( 0.55f, 0.75f );
    sledderBodyFixtureDef.shape = &sledderBodyShape;
    sledderBodyFixtureDef.density = 1.0f;
    sledderBodyFixtureDef.friction = 0.5f;
	sledderBodyFixtureDef.filter.groupIndex = -1;
	type = 5;
	sledderBodyFixtureDef.userData = (void*)type;

	sledderHeadBody = NULL;
	sledderHeadBodyDef.position.Set( spawnX, spawnY - 1.1f );
	sledderHeadBodyDef.type = b2_dynamicBody;
	sledderHeadShape.SetAsBox( 0.4f, 0.4f );
	sledderHeadFixtureDef.shape = &sledderHeadShape;
	sledderHeadFixtureDef.density = 1.0f;
	sledderHeadFixtureDef.friction = 0.5f;
	sledderHeadFixtureDef.filter.groupIndex = -1;
	type = 5;
	sledderHeadFixtureDef.userData = (void*)type;

	sledderHatBody = NULL;
	sledderHatBodyDef.position.Set( spawnX, spawnY - 1.6f );
	sledderHatBodyDef.type = b2_dynamicBody;
	b2Vec2 verticies[3];
	verticies[0].Set(  0.0f, -0.3f );
	verticies[1].Set(  0.45f, 0.3f );
	verticies[2].Set( -0.45f, 0.3f );
	sledderHatShape.Set(verticies, 3);
	sledderHatFixtureDef.shape = &sledderHatShape;
	sledderHatFixtureDef.friction = 0.8f;
	sledderHatFixtureDef.density = 1.0f;
	type = 5;
	sledderHatFixtureDef.userData = (void*)type;

	sledderLegBody = NULL;
	sledderLegBodyDef.position.Set( spawnX + 0.15f, spawnY + 1.15f );
	sledderLegBodyDef.type = b2_dynamicBody;
	sledderLegShape.SetAsBox( 0.3f, 0.75f );
	sledderLegFixtureDef.shape = &sledderLegShape;
	sledderLegFixtureDef.density = 1.0f;
	sledderLegFixtureDef.friction = 0.5f;
	sledderLegFixtureDef.filter.groupIndex = -1;
	type = 5;
	sledderLegFixtureDef.userData = (void*)type;

	sledderArmBody = NULL;
	sledderArmBodyDef.position.Set( spawnX + 0.05f, spawnY + 0.3 );
	sledderArmBodyDef.type = b2_dynamicBody;
	sledderArmShape.SetAsBox( 0.15f, 0.65f );
	sledderArmFixtureDef.shape = &sledderArmShape;
	sledderArmFixtureDef.density = 1.0f;
	sledderArmFixtureDef.friction = 0.5f;
	sledderArmFixtureDef.filter.groupIndex = -1;
	type = 5;
	sledderArmFixtureDef.userData = (void*)type;

	hatToHeadJoint = NULL;
	headToBodyJoint = NULL;
	armToBodyJoint = NULL;
	legToBodyJoint = NULL;
	armToSledJoint = NULL;
	legToSledJoint = NULL;
}

void Sledder::SetPositions( float x, float y, float angle )
{
	//spawnX = x - 0.3f;
	//spawnY = y - 0.6f;

	spawnX = ( ( -0.3f * cos( angle ) ) - ( -0.6f * sin( angle ) ) ) + x;
	spawnY = ( ( -0.3f * sin( angle ) ) + ( -0.6f * cos( angle ) ) ) + y;

	sledderBodyBodyDef.position.Set( spawnX, spawnY );
	sledderBodyBodyDef.angle = angle;

	headOffsetX = ( ( -0.3f * cos( angle ) ) - ( ( -0.6f - 1.1f ) * sin( angle ) ) ) + x;
	headOffsetY = ( ( -0.3f * sin( angle ) ) + ( ( -0.6f - 1.1f ) * cos( angle ) ) ) + y;

	headJointOffsetX = ( ( -0.3f * cos( angle ) ) - ( ( -0.6f - 0.55f ) * sin( angle ) ) ) + x;
	headJointOffsetY = ( ( -0.3f * sin( angle ) ) + ( ( -0.6f - 0.55f ) * cos( angle ) ) ) + y;

	sledderHeadBodyDef.position.Set( headOffsetX, headOffsetY );
	sledderHeadBodyDef.angle = angle;


	hatOffsetX = ( ( -0.3f * cos( angle ) ) - ( ( -0.6f - 1.6f ) * sin( angle ) ) ) + x;
	hatOffsetY = ( ( -0.3f * sin( angle ) ) + ( ( -0.6f - 1.6f ) * cos( angle ) ) ) + y;

	hatJointOffsetX = ( ( -0.3f * cos( angle ) ) - ( ( -0.6f - 1.5f ) * sin( angle ) ) ) + x;
	hatJointOffsetY = ( ( -0.3f * sin( angle ) ) + ( ( -0.6f - 1.5f ) * cos( angle ) ) ) + y;

	sledderHatBodyDef.position.Set( hatOffsetX, hatOffsetY );
	sledderHatBodyDef.angle = angle;

	float armX = ( ( ( -0.3f + 0.2f ) * cos( angle ) ) - ( ( -0.6f - 0.2f ) * sin( angle ) ) ) + x;
	float armY = ( ( ( -0.3f + 0.2f ) * sin( angle ) ) + ( ( -0.6f - 0.2f ) * cos( angle ) ) ) + y;

	armOffsetX = ( ( ( 0.0f ) * cos( angle - b2_pi / 3.0f ) ) ) - ( ( 0.5f ) * sin( angle - b2_pi / 3.0f ) ) + armX;
	armOffsetY = ( ( ( 0.0f ) * sin( angle - b2_pi / 3.0f ) ) ) + ( ( 0.5f ) * cos( angle - b2_pi / 3.0f ) ) + armY;

	armJointOffsetX = ( ( ( -0.3f ) * cos( angle ) ) - ( ( -0.6f - 0.25f ) * sin( angle ) ) ) + x;
	armJointOffsetY = ( ( ( -0.3f ) * sin( angle ) ) + ( ( -0.6f - 0.25f ) * cos( angle ) ) ) + y;

	sledderArmBodyDef.position.Set( armOffsetX, armOffsetY );
	sledderArmBodyDef.angle = angle - b2_pi / 3.0f;


	float legX = ( ( ( -0.3f + 0.3f ) * cos( angle ) ) - ( ( -0.6f + 0.4f ) * sin( angle ) ) ) + x;
	float legY = ( ( ( -0.3f + 0.3f ) * sin( angle ) ) + ( ( -0.6f + 0.4f ) * cos( angle ) ) ) + y;

	legOffsetX = ( ( ( 0.0f ) * cos( angle - b2_pi / 2.5f ) ) ) - ( ( 0.5f ) * sin( angle - b2_pi / 2.5f ) ) + legX;
	legOffsetY = ( ( ( 0.0f ) * sin( angle - b2_pi / 2.5f ) ) ) + ( ( 0.5f ) * cos( angle - b2_pi / 2.5f ) ) + legY;

	legJointOffsetX = ( ( ( -0.3f ) * cos( angle ) ) - ( ( -0.6f + 0.5f ) * sin( angle ) ) ) + x;
	legJointOffsetY = ( ( ( -0.3f ) * sin( angle ) ) + ( ( -0.6f + 0.5f ) * cos( angle ) ) ) + y;

	sledderLegBodyDef.position.Set( legOffsetX, legOffsetY );
	sledderLegBodyDef.angle = angle - b2_pi / 2.5f;


	armToSledJointOffsetX = ( ( ( -0.3f + 0.7f ) * cos( angle ) ) - ( ( -0.6f + 0.9f ) * sin( angle ) ) ) + x;
	armToSledJointOffsetY = ( ( ( -0.3f + 0.7f ) * sin( angle ) ) + ( ( -0.6f + 0.9f ) * cos( angle ) ) ) + y;

	legToSledJointOffsetX = ( ( ( -0.3f + 0.9f ) * cos( angle ) ) - ( ( -0.6f + 0.9f ) * sin( angle ) ) ) + x;
	legToSledJointOffsetY = ( ( ( -0.3f + 0.9f ) * sin( angle ) ) + ( ( -0.6f + 0.9f ) * cos( angle ) ) ) + y;


}

Sledder::~Sledder()
{
	sledderBodyBody = NULL;
	sledderHeadBody = NULL;
	sledderHatBody = NULL;
	sledderLegBody = NULL;
	sledderArmBody = NULL;
	headToBodyJoint = NULL;
	hatToHeadJoint = NULL;
	armToBodyJoint = NULL;
	legToBodyJoint = NULL;
	armToSledJoint = NULL;
	legToSledJoint = NULL;
}

void Sledder::InitializeSledder()
{
	bodyImage.LoadImage( "data/body.png" );
	headImage.LoadImage( "data/head.png" );
	legImage.LoadImage( "data/leg.png" );
	armImage.LoadImage( "data/arm.png" );
	hatImage.LoadImage( "data/hat.png" );
}

void Sledder::SetVelocity(b2Vec2 vel, float angVel )
{
	sledderBodyBody->SetLinearVelocity( vel );
	sledderHeadBody->SetLinearVelocity( vel );
	sledderArmBody->SetLinearVelocity( vel );
	sledderLegBody->SetLinearVelocity( vel );
	sledderHatBody->SetLinearVelocity( vel );

	sledderBodyBody->SetAngularVelocity( angVel );
	sledderHatBody->SetAngularVelocity( angVel );
	sledderHeadBody->SetAngularVelocity( angVel );
	sledderArmBody->SetAngularVelocity( angVel );
	sledderLegBody->SetAngularVelocity( angVel );
}

void Sledder::SetVisibility( bool co )
{
	visible = co;
}
