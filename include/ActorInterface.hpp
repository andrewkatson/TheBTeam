/*
  ActorInterface.hpp

  Purpose: A template to be implemented by actor classes.

  @author Jeremy Elkayam
 */

#ifndef ACTORINTERFACE_H
#define ACTORINTERFACE_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "EventManager.hpp"
#include "TextLoader.hpp"
#include "TextureLoader.hpp"

using std::shared_ptr;
using std::addressof;
using std::vector;
class ActorInterface{

protected:
  //event manager (used to register, deregister from events, and create them)
  shared_ptr<EventManager> eventManager;

  //Store the textLoader to make requests for strings and constants
  shared_ptr<TextLoader> textLoader;

  //The unique identifier for the actor.
  long long  id;

  //the string identifier for the type of actor (specific to each type of actor)
  string actorTypeID;

  //The sprite corresponding to the actor.
  sf::Sprite sprite;

  //all the textures for this actor
  shared_ptr<vector<sf::Texture>> textures;

  //The actor's movement speed in [units]. [pixels per millisecond? microsecond?]
  float speed;

  //The actor's hispoints
  int hitpoints;

  //Used to reset the actor's hit points
  int maxHitpoints;

  //The actor's damage
  int damage;

  //The actor's armor
  int armor;

  //The actor's armor penetration
  int armorPenetration;

  //The rectangle corresponding to the object's dimensions.
  sf::FloatRect collisionBox;

  //The coordinates of the actor.
  double x,y;

  //Row and column of the actor on the world grid.
  int row,col;

public:

  ActorInterface();
  /*
    TODO - hash out the specifics of the interface's constructor. does it need a default implementation?
   */

  /*
   * Reset the hitpoints back to the max (for respawning allied units)
   */
  void resetHealth(){hitpoints = maxHitpoints;}

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
  virtual void move(float delta, float xmult = 0, float ymult = 0)=0;

  /*
    Determine whether or not the object's collision box is colliding with the
    given collision box. By default, this is determined by whether or not the
    wo collision boxes intersect.

    @return true if the actor's collision box is colliding with colliding_with,
            false otherwise.
   */
  bool isCollision(sf::FloatRect colliding_with);

  /*
   * Return actor type ID
   */
  string getType(){return actorTypeID;}

  /*
   * update the position, check if it hit its target
   */
  virtual void update(float delta)=0;
  /*
   * get the x coordinate of the actor
   */
  double getXCoordinate(){return x;}
  /*
   * get the y coordinate of the actor
   */
  double getYCoordinate(){return y;}
  /*
   * get the row of fthe actor
   */
  int getRow(){return row;}
  /*
   * get the col of the actor
   */
  int getCol(){return col;}
  /*
   * set the x coordinate of the actor
   */
  void setXCoordinate(double x){this -> x = x;}
  /*
   * set the y coordinate of the actor
   */
  void setYCoordinate(double y){this -> y = y;}
  /*
   * set the row of the actor
   */
  void setRow(int row){this -> row = row;}
  /*
   * set the col of the actor
   */
  void setCol(int col){this -> col = col;}

  float getSpeed(){return this->speed;}

  int getHitpoints(){return this->hitpoints;}

  int getDamage(){return this->damage;}

  int getArmor(){return this->armor;}

  int getArmorPenetration(){return this->armorPenetration;}

};

#endif
