/*
  ActorInterface.hpp
  
  Purpose: A template to be implemented by actor classes.
  
  @author Jeremy Elkayam
 */

#ifndef ACTORINTERFACE_H
#define ACTORINTERFACE_H

#include <SFML/Graphics.hpp>

class ActorInterface{
  
private:
  
  int id;

  sf::Sprite sprite;

  float speed;

  sf::FloatRect collisionBox;

public:

  int getID(){return id;}

  sf::Sprite getSprite(){return sprite;}

  virtual void move()=0;

  bool isCollision(sf::FloatRect colliding_with);

};

#endif
