/*
  ActorInterface.cpp

  Purpose: A template to be implemented by actor classes.

  @author Jeremy Elkayam
 */

#include "ActorInterface.hpp"

ActorInterface::ActorInterface(){
  //the id is the address of the current object
  id = (long long) this;

  //set the sprite to face roughly in the direction the textures are drawn  in
  //sprite.setRotation(135.0f + 90.f);
  //rotate(225.0f);
}

void ActorInterface::rotate(float degrees){
  sprite.rotate(degrees);
}


void ActorInterface::setWorld(shared_ptr<b2World> world){
  //Box2D Info
  this -> world = world;

  b2BodyDef bodyDef;
  bodyDef.position = b2Vec2(this -> x/30.f, this -> y/30.f);
  bodyDef.type = b2_dynamicBody;
  b2Body* body = this -> world -> CreateBody(&bodyDef);

  b2CircleShape circle;
  circle.m_p.Set(0,0);
  circle.m_radius = (float) this -> radius/30.f;
  b2FixtureDef fixtureDef;
	fixtureDef.density = 1.f;
	fixtureDef.friction = 0.7f;
	fixtureDef.shape = &circle;
	fixtureDef.restitution = .5f;
	this -> body -> CreateFixture(&fixtureDef);
	this -> body -> SetAwake(1);
}

void ActorInterface::updatePosition(){
	//Set body to awake in case of it being 0 velocity in both x and y direction to prevent
	//Freezing
	this -> body -> SetAwake(1);

	this -> x = this -> body -> GetPosition().x * 30.f;
	this -> y = this -> body -> GetPosition().y * 30.f;

	/*Keeping this Debug information for now to keep track of b2World Objects
	for (b2Body* BodyIterator = this -> World -> GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
        {
		printf("Obj %i is at x:%f y:%f ", BodyIterator, BodyIterator -> GetPosition().x * SCALE, BodyIterator -> GetPosition().y * SCALE);
		printf(" is active %i\n", this -> Body -> IsActive());
	}
	printf("\n");
	*/

}
