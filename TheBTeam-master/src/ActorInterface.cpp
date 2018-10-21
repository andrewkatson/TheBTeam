/*
  ActorInterface.cpp
  
  Purpose: A template to be implemented by actor classes.
  
  @author Jeremy Elkayam
 */

#include "ActorInterface.hpp"

bool ActorInterface::isCollision(sf::FloatRect colliding_with)
{
  return this->collisionBox.intersects(colliding_with);
}
