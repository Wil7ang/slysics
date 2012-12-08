/*
 * src/Game/Sled.cpp
 *
 * Copyright (C) 2011 Wilson Tang.
 *
 * This file is part of Slysics and is free software, distributed,
 * and licensed under the GNU General Public License, version 3.
 *
 * You should have received a copy of the GNU General Public License.
 * If not, see <http://www.gnu.org/licenses/gpl-3.0.html>.
*/

#include "Sled.h"

Sled::Sled()
{
	created = false;
	spawnX = 0.0f;
	spawnY = 0.0f;
	sledBody = NULL;
	sledBodyDef.position.Set( spawnX, spawnY );
    sledBodyDef.type = b2_dynamicBody;


	b2Vec2 verticies[4];
	verticies[0].Set( -1.6f,  0.2f );
	verticies[1].Set(  1.25f, 0.2f );
	verticies[2].Set(  1.25f, 0.6f );
    verticies[3].Set( -2.0f,  0.6f );
    sledBottomShape.Set(verticies, 4);
    sledBottomFixtureDef.shape = &sledBottomShape;
    sledBottomFixtureDef.density = 1.0f;
    sledBottomFixtureDef.friction = 0.0f;
    sledBottomFixtureDef.filter.groupIndex = -1;
	type = 6;
	sledBottomFixtureDef.userData = (void*)type;
	//sledBottomShape.userData = (void*)type;

	sledFrontShape.m_radius = 0.6f;
	sledFrontShape.m_p.Set(1.25f, 0.0f);
	sledFrontFixtureDef.shape = &sledFrontShape;
	sledFrontFixtureDef.density = 1.0f;
	sledFrontFixtureDef.friction = 0.0f;
	sledFrontFixtureDef.filter.groupIndex = -1;
	type = 6;
	sledFrontFixtureDef.userData = (void*)type;
	//sledFrontShape.userData = (void*)type;

	crumpled = false;

}

Sled::~Sled()
{
	sledBody = NULL;
}

void Sled::SetPositions(float x, float y, float angle)
{
	spawnX = x;
	spawnY = y;
	sledBodyDef.position.Set( spawnX, spawnY );
	sledBodyDef.angle = angle;
}

void Sled::InitializeSled()
{
	sledImage.LoadImage("data/sled.png");
	sledCrumpledImage.LoadImage("data/sledCrumpled.png");
}

void Sled::SetVelocity( b2Vec2 vel, float angVel )
{
	sledBody->SetLinearVelocity( vel );
	sledBody->SetAngularVelocity( angVel );
}

void Sled::SetCrumpled( bool co )
{
	crumpled = co;
	sledImage.SetVisible(false);
	sledCrumpledImage.SetVisible( true );
}

void Sled::ApplyImpulse( b2Vec2 impulse )
{
	sledBody->ApplyLinearImpulse( impulse, sledBody->GetPosition() );
	//sledBody->ApplyForceToCenter(impulse);
	//sledBody->
}
