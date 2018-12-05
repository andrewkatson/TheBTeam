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


  //set the attack rate to 0 in case this is a projectile
  attackRate = 0;

  //set the sprite to face roughly in the direction the textures are drawn  in
  //sprite.setRotation(135.0f + 90.f);
  //rotate(225.0f);
}

ActorInterface::~ActorInterface(){

}

void ActorInterface::rotate(float degrees){
  sprite.rotate(degrees);
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
