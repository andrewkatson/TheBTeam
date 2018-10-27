/*
  ActorInterface.hpp

  Purpose: A template to be implemented by actor classes.

  @author Jeremy Elkayam
 */

#ifndef ACTORINTERFACE_H
#define ACTORINTERFACE_H

#include <SFML/Graphics.hpp>

class ActorInterface{

protected:
  //The unique identifier for the actor.
  int id;

  //The sprite corresponding to the actor.
  sf::Sprite sprite;

  //The actor's movement speed in [units]. [pixels per millisecond? microsecond?]
  float speed;

  //The actor's hispoints
  int hitpoints;

  //The actor's damage
  int damage;

  //The actor's armor
  int armor;

  //The actor's armor penetration
  int armorPenetration;

  //The rectangle corresponding to the object's dimensions.
  sf::FloatRect collisionBox;

public:

  /*
    TODO - hash out the specifics of the interface's constructor. does it need a default implementation?
   */

  /*
    Returns the unique identifier for the actor.

    @return an integer representing the actor's identity
   */
  int getID(){return id;}

  /*
    Returns the actor's sprite.

    @return the Sprite object that the interface contains.
   */
  sf::Sprite& getSprite(){return sprite;}//PEOPLE WHO KNOW MORE THAN ME: SHOULD THIS RETURN A REFERENCE?

  /*
    Move the actor according to its speed and the actor's innate properties.

    This must be implemented by extending classes, since different types of
    actors obviously have different movement patterns.
  */
  virtual void move(float deltaS)=0;

  /*
    Determine whether or not the object's collision box is colliding with the
    given collision box. By default, this is determined by whether or not the
    wo collision boxes intersect.

    @return true if the actor's collision box is colliding with colliding_with,
            false otherwise.
   */
  bool isCollision(sf::FloatRect colliding_with);

};

#endif
