/*
  ActorInterface.cpp

  Purpose: A template to be implemented by actor classes.

  @author Jeremy Elkayam
 */

#include "ActorInterface.hpp"

ActorInterface::ActorInterface(){

  void *address = this;
  
}
bool ActorInterface::isCollision(sf::FloatRect colliding_with)
{
  return this->collisionBox.intersects(colliding_with);
}

double ActorInterface::getX() const {
  return x;
}

void ActorInterface::setX(double x) {
  ActorInterface::x = x;
}

double ActorInterface::getY() const {
  return y;
}

void ActorInterface::setY(double y) {
  ActorInterface::y = y;
}

int ActorInterface::getRow() const {
  return row;
}

void ActorInterface::setRow(int row) {
  ActorInterface::row = row;
}

int ActorInterface::getCol() const {
  return col;
}

void ActorInterface::setCol(int col) {
  ActorInterface::col = col;
}
