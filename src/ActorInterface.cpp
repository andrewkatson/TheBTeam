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

  //set the attack rate to 0 in case this is a projectile
  attackRate = 0;

  //set the sprite to face roughly in the direction the textures are drawn  in
  //sprite.setRotation(135.0f + 90.f);
  //rotate(225.0f);
}

ActorInterface::~ActorInterface(){

  if(body){
    cout << "destoryed " << endl;
    body -> DestroyFixture(fixture);
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


void ActorInterface::startContact(void* collidingWith){
  //collidingWith should be cast to a clas you can collide with ie Actors and Towers
  cout << "start Contact Actor Interface" << '\n'<<endl;
}

void ActorInterface::endContact(void* collidingWith){
  //look above
  cout << "end Contact Actor Interface" << '\n'<<endl;
}

double ActorInterface::getDirection() const {
  return direction;
}

void ActorInterface::setDirection(double direction) {
  sprite.setRotation(-180*direction/M_PI);
  this ->direction = direction;
}

void ActorInterface::setXScale(int num_cols){
  double dc=num_cols;
  ActorInterface::xScale=1.0/dc;
}

void ActorInterface::setYScale(int num_rows){
  double dr=num_rows;
  ActorInterface::yScale=1.0/dr;
}

double ActorInterface::getYScale(){
  return ActorInterface::yScale;
}

double ActorInterface::getXScale() {
  return ActorInterface::xScale;
}


void ActorInterface::setVector(float x, float y){
  this -> xVector = x;
  this -> yVector = y;
}

void ActorInterface::setTargetPos(float xPos, float yPos){
  this -> xTarget = xPos;
  this -> yTarget = yPos;
}
