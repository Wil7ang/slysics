/*
 * src/Core/Physics/PhysicsCore.cpp
 *
 * Copyright (C) 2011 Wilson Tang.
 *
 * This file is part of Slysics and is free software, distributed,
 * and licensed under the GNU General Public License, version 3.
 *
 * You should have received a copy of the GNU General Public License.
 * If not, see <http://www.gnu.org/licenses/gpl-3.0.html>.
*/

#include "PhysicsCore.h"

PhysicsCore::PhysicsCore()
{
	b2Vec2 gravity( 0.0f, 10.0f );
	world = new b2World( gravity );

	world->SetContactListener( &contactListener );


	timeStep = 1.0f / 20.0f;

	linesList = NULL;
}

PhysicsCore::~PhysicsCore()
{
	delete world;
	world = NULL;
	linesList = NULL;
}

void PhysicsCore::SetSimulationSpeed( float factor )
{
	timeStep = 1.0f / ( 15.0f * factor );
}

void PhysicsCore::StepTime()
{
	world->Step( timeStep, 15, 8 );
}

void PhysicsCore::DestroySled( Sled *sled, Sledder *sledder )
{
	DeleteJoint( sledder->bodyToSledJoint );
	DeleteJoint( sledder->legToSledJoint );
	DeleteJoint( sledder->armToSledJoint );

	DeleteJoint( sledder->legToBodyJoint );
	DeleteJoint( sledder->armToBodyJoint );
	DeleteJoint( sledder->headToBodyJoint );
	DeleteJoint( sledder->hatToHeadJoint );

	if(sledder->sledderArmBody)
		world->DestroyBody( sledder->sledderArmBody );
	if(sledder->sledderLegBody)
		world->DestroyBody( sledder->sledderLegBody );
	if(sledder->sledderHeadBody)
		world->DestroyBody( sledder->sledderHeadBody );
	if(sledder->sledderHatBody)
		world->DestroyBody( sledder->sledderHatBody );
	if(sledder->sledderBodyBody)
		world->DestroyBody( sledder->sledderBodyBody );
	if(sled->sledBody)
		world->DestroyBody( sled->sledBody );

	sledder->sledderArmBody = NULL;
	sledder->sledderLegBody = NULL;
	sledder->sledderHeadBody = NULL;
	sledder->sledderHatBody = NULL;
	sledder->sledderBodyBody = NULL;
	sled->sledBody = NULL;

	sledder->bodyToSledJoint = NULL;
	sledder->armToSledJoint = NULL;
	sledder->legToSledJoint = NULL;

	sledder->legToBodyJoint = NULL;
	sledder->armToBodyJoint = NULL;
	sledder->headToBodyJoint = NULL;
	sledder->hatToHeadJoint = NULL;

	sled->created = false;
	sledder->created = false;
}

void PhysicsCore::CreateSled( Sled *sled, Sledder *sledder, float x, float y, float angle )
{

	sledder->SetPositions( x, y, angle );
	sled->SetPositions( x, y, angle );

	sled->sledBody = world->CreateBody( &sled->sledBodyDef );
	sled->sledBottomFixture = sled->sledBody->CreateFixture(&sled->sledBottomFixtureDef);
	sled->sledBottomFixture->SetUserData((void*)sled->type);
	sled->sledFrontFixture = sled->sledBody->CreateFixture(&sled->sledFrontFixtureDef);
	sled->sledFrontFixture->SetUserData((void*)sled->type);

	sledder->sledderBodyBody = world->CreateBody( &sledder->sledderBodyBodyDef );
	sledder->sledderBodyFixture = sledder->sledderBodyBody->CreateFixture( &sledder->sledderBodyFixtureDef);
	//sledder->sledderBodyBody->SetMassFromShapes();

	sledder->sledderArmBody = world->CreateBody( &sledder->sledderArmBodyDef );
	sledder->sledderArmFixture = sledder->sledderArmBody->CreateFixture( &sledder->sledderArmFixtureDef );
	//sledder->sledderArmBody->SetMassFromShapes();

	sledder->sledderHeadBody = world->CreateBody( &sledder->sledderHeadBodyDef );
	sledder->sledderHeadFixture = sledder->sledderHeadBody->CreateFixture( &sledder->sledderHeadFixtureDef );
	//sledder->sledderHeadBody->SetMassFromShapes();

	sledder->sledderHatBody = world->CreateBody( &sledder->sledderHatBodyDef );
	sledder->sledderHatFixture = sledder->sledderHatBody->CreateFixture( &sledder->sledderHatFixtureDef );
	//sledder->sledderHatBody->SetMassFromShapes();

	sledder->sledderLegBody = world->CreateBody( &sledder->sledderLegBodyDef );
	sledder->sledderLegFixture = sledder->sledderLegBody->CreateFixture( &sledder->sledderLegFixtureDef );
	//sledder->sledderLegBody->SetMassFromShapes();

	sledder->headToBodyJointDef.Initialize( sledder->sledderHeadBody, sledder->sledderBodyBody, b2Vec2( sledder->headJointOffsetX, sledder->headJointOffsetY ) );
	sledder->headToBodyJointDef.lowerAngle = 0.0f;
	sledder->headToBodyJointDef.upperAngle = 0.1f;
	sledder->headToBodyJointDef.enableLimit = true;
	sledder->headToBodyJointDef.enableMotor = false;
	sledder->headToBodyJointDef.collideConnected = false;

	sledder->hatToHeadJointDef.Initialize( sledder->sledderHatBody, sledder->sledderHeadBody, b2Vec2( sledder->hatJointOffsetX, sledder->hatJointOffsetY ) );
	sledder->hatToHeadJointDef.lowerAngle = 0.0f;
	sledder->hatToHeadJointDef.upperAngle = 0.0f;
	sledder->hatToHeadJointDef.enableLimit = true;
	sledder->hatToHeadJointDef.enableMotor = false;
	sledder->hatToHeadJointDef.collideConnected = false;

	sledder->armToBodyJointDef.Initialize( sledder->sledderArmBody, sledder->sledderBodyBody, b2Vec2( sledder->armJointOffsetX, sledder->armJointOffsetY ) );
	sledder->armToBodyJointDef.lowerAngle = -b2_pi / 2.0f;
	sledder->armToBodyJointDef.upperAngle = b2_pi;
	sledder->armToBodyJointDef.enableLimit = true;
	sledder->armToBodyJointDef.enableMotor = false;
	sledder->armToBodyJointDef.collideConnected = false;

	sledder->legToBodyJointDef.Initialize( sledder->sledderLegBody, sledder->sledderBodyBody, b2Vec2( sledder->spawnX + 0.15f, sledder->spawnY + 0.40f ) );
	sledder->legToBodyJointDef.lowerAngle = -b2_pi / 2.0f;
	sledder->legToBodyJointDef.upperAngle = b2_pi / 2.0f;
	sledder->legToBodyJointDef.enableLimit = true;
	sledder->legToBodyJointDef.enableMotor = false;
	sledder->legToBodyJointDef.collideConnected = false;

	sledder->headToBodyJoint = ( b2RevoluteJoint* )world->CreateJoint( &sledder->headToBodyJointDef );
	sledder->hatToHeadJoint = ( b2RevoluteJoint* )world->CreateJoint( &sledder->hatToHeadJointDef );
	sledder->armToBodyJoint = ( b2RevoluteJoint* )world->CreateJoint( &sledder->armToBodyJointDef );
	sledder->legToBodyJoint = ( b2RevoluteJoint* )world->CreateJoint( &sledder->legToBodyJointDef );


	sledder->armToSledJointDef.Initialize( sledder->sledderArmBody, sled->sledBody, b2Vec2( sledder->armToSledJointOffsetX, sledder->armToSledJointOffsetY ) );
	sledder->armToSledJointDef.enableLimit = false;
	sledder->armToSledJointDef.enableMotor = false;
	sledder->armToSledJointDef.collideConnected = false;

	sledder->legToSledJointDef.Initialize( sledder->sledderLegBody, sled->sledBody, b2Vec2( sled->spawnX + 0.6f, sled->spawnY + 0.40f ) );
	sledder->legToSledJointDef.enableLimit = false;
	sledder->legToSledJointDef.enableMotor = false;
	sledder->legToSledJointDef.collideConnected = false;

	sledder->bodyToSledJointDef.Initialize( sledder->sledderBodyBody, sled->sledBody, b2Vec2( sled->spawnX, sled->spawnY ) );
	sledder->bodyToSledJointDef.upperAngle = b2_pi / 8.0f;
	sledder->bodyToSledJointDef.lowerAngle = -b2_pi;
	sledder->bodyToSledJointDef.enableLimit = true;
	sledder->bodyToSledJointDef.motorSpeed = -1.0f;
	sledder->bodyToSledJointDef.maxMotorTorque = 20.0f;
	sledder->bodyToSledJointDef.enableMotor = true;
	sledder->bodyToSledJointDef.collideConnected = false;

	sledder->bodyToSledJoint = ( b2RevoluteJoint* )world->CreateJoint( &sledder->bodyToSledJointDef );
	sledder->armToSledJoint = ( b2RevoluteJoint* )world->CreateJoint( &sledder->armToSledJointDef );
	sledder->legToSledJoint = ( b2RevoluteJoint* )world->CreateJoint( &sledder->legToSledJointDef );


	sled->created = true;
	sledder->created = true;
}

void PhysicsCore::DeleteJoint( b2Joint *joint )
{
	if ( joint != NULL )
	{
		world->DestroyJoint( joint );
	}
}

void PhysicsCore::AddLineList( vector<Line> *lnList )
{
	linesList = lnList;
}

void PhysicsCore::DeleteLine( int ID )
{
	world->DestroyBody( linesList->at( ID ).lineBody );
	linesList->at( ID ).lineBody = NULL;
}

void PhysicsCore::CreateLine()
{
	linesList->at( linesList->size() - 1 ).lineBody = world->CreateBody( &linesList->at( linesList->size() - 1 ).lineBodyDef );
	linesList->at( linesList->size() - 1 ).lineFixture = linesList->at( linesList->size() - 1 ).lineBody->CreateFixture( &linesList->at( linesList->size() - 1 ).lineFixtureDef );
}

bool PhysicsCore::GetIfAccelerate( int type )
{
	if ( type == 0 )
		return contactListener.sledAccelerate;
	else if ( type == 1 )
		return contactListener.sledderAccelerate;
}

bool PhysicsCore::GetIfDecelerate( int type )
{
	if ( type == 0 )
		return contactListener.sledDecelerate;
	else if ( type == 1 )
		return contactListener.sledderDecelerate;
}

void PhysicsCoreContactListener::BeginContact( b2Contact* point )
{
	long long conv = reinterpret_cast<long long> ( point->GetFixtureA()->GetUserData() );
	int shape1 = static_cast<int>( conv );
	conv = reinterpret_cast<long long> ( point->GetFixtureB()->GetUserData() );
	int shape2 = static_cast<int>( conv );

	if ( shape1 == 6 || shape2 == 6 )
	{
		if ( shape1 == 1 || shape2 == 1 )
		{
			sledDecelerate = true;
			sledAccelerate = false;
		}
		else if ( shape1 == 2 || shape2 == 2 )
		{
			sledAccelerate = true;
			sledDecelerate = false;
		}
	}
	/*else if( shape1 == 5 || shape2 == 5)
	{
		if( shape1 == 1 || shape2 == 1)
		{
			sledderDecelerate = true;
			sledderAccelerate = false;
		}
		else if( shape1 == 2 || shape2 == 2)
		{
			sledderAccelerate = true;
			sledderDecelerate = false;
		}
	}*/
}

void PhysicsCoreContactListener::EndContact( b2Contact* point )
{
	long long conv = reinterpret_cast<long long> ( point->GetFixtureA()->GetUserData() );
	int shape1 = static_cast<int>( conv );
	conv = reinterpret_cast<long long> ( point->GetFixtureB()->GetUserData() );
	int shape2 = static_cast<int>( conv );

	if ( shape1 == 6 || shape2 == 6 )
	{
		if ( shape1 == 1 || shape2 == 1 )
		{
			sledDecelerate = false;
		}
		else if ( shape1 == 2 || shape2 == 2 )
		{
			sledAccelerate = false;
		}
	}

	/*if( shape1 == 5 || shape2 == 5)
	{
		if( shape1 == 1 || shape2 == 1)
		{
			sledderDecelerate = false;
		}
		else if( shape1 == 2 || shape2 == 2)
		{
			sledderDecelerate = false;
		}
	}*/
}

void PhysicsCore::DestroyBody(b2Body *bdy)
{
	world->DestroyBody(bdy);
}

