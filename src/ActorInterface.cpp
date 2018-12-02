/*
  ActorInterface.cpp

  Purpose: A template to be implemented by actor classes.

  @author Jeremy Elkayam
 */

#include "ActorInterface.hpp"
double ActorInterface::xScale;
double ActorInterface::yScale;

ActorInterface::ActorInterface(){
  //the id is the address of the current object
  id = (long long) this;

  //set the body to NULL in case we never set the world so the destructor does not try to destroy an unitialized body
  body = NULL;

  //set the sprite to face roughly in the direction the textures are drawn  in
  //sprite.setRotation(135.0f + 90.f);
  //rotate(225.0f);
}

ActorInterface::~ActorInterface(){

  if(body){
    world -> DestroyBody(body);
  }
}

void ActorInterface::rotate(float degrees){
  sprite.rotate(degrees);
}


void ActorInterface::setWorld(shared_ptr<b2World> world){
  //Box2D Info
  this -> world = world;

  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  bodyDef.position.Set(x,y);
  bodyDef.angle = 0;
  body = world -> CreateBody(&bodyDef);
  body ->SetUserData( this );

  //FIXTURES (moved to Projectile and MeleeUnit)
  // b2CircleShape circle;
  // circle.m_p.Set(0,0);
  // circle.m_radius = (float) this -> radius/30.f;
  // b2FixtureDef fixtureDef;
	// fixtureDef.density = 1.f;
	// fixtureDef.friction = 0.7f;
	// fixtureDef.shape = &circle;
	// fixtureDef.restitution = .5f;
	// this -> body -> CreateFixture(&fixtureDef);
	// this -> body -> SetAwake(1);
}

// void ActorInterface::updatePosition(){
// 	//Set body to awake in case of it being 0 velocity in both x and y direction to prevent
// 	//Freezing
// 	this -> body -> SetAwake(1);
//
// 	this -> x = this -> body -> GetPosition().x * 30.f;
// 	this -> y = this -> body -> GetPosition().y * 30.f;
//
// }

void ActorInterface::startContact(void* collidingWith){
  //collidingWith should be cast to a clas you can collide with ie Actors and Towers
  cout << "start Contact Actor Interface" << endl;
}

void ActorInterface::endContact(void* collidingWith){
  //look above
  cout << "end Contact Actor Interface" << endl;
}

double ActorInterface::getDirection() const {
  return direction;
}

void ActorInterface::setDirection(double direction) {
  this ->direction = direction;
}

void ActorInterface::setXScale(int windowX, int num_cols){
  double dx=windowX;
  double dc=num_cols;
  ActorInterface::xScale=dx/dc;
}

void ActorInterface::setYScale(int windowY, int num_rows){
  double dy=windowY;
  double dr=num_rows;

  ActorInterface::yScale=dy/dr;
}

double ActorInterface::getYScale(){
  return ActorInterface::yScale;
}

double ActorInterface::getXScale() {
  return ActorInterface::xScale;
}
