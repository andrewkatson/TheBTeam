/*
  ActorInterface.hpp

  Purpose: A template to be implemented by actor classes.

  @author Jeremy Elkayam
 */

#ifndef ACTORINTERFACE_H
#define ACTORINTERFACE_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
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
  float x,y;

  //Row and column of the actor on the world grid.
  int row,col;

  sf::Color color;

  //the degree of error
  const float e = 0.001;

  //Box2d World and Body
  shared_ptr<b2World> world;
  shared_ptr<b2Body> body;

  //the area of effect for a projectile and the area of attack for a unit
  int radius;

public:

  ActorInterface();

  /*
   * Rotate the texture by the number of degrees
   * @param degrees:
   */
  void rotate(float degrees);

  /*
    TODO - hash out the specifics of the interface's constructor. does it need a default implementation?
   */

  void setWorld(shared_ptr<b2World> world);
  void updatePosition();

  /*
   * Reset the hitpoints back to the max (for respawning allied units)
   */
  void resetHealth(){hitpoints = maxHitpoints;}

  /*
    Returns the unique identifier for the actor.

    @return an integer representing the actor's identity
   */
  long long getID(){return id;}

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
  float getXCoordinate(){return x;}
  /*
   * get the y coordinate of the actor
   */
  float getYCoordinate(){return y;}
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
  void setXCoordinate(float x){this -> x = x;}
  /*
   * set the y coordinate of the actor
   */
  void setYCoordinate(float y){this -> y = y;}
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

  /*
   * @param xPos: the x of the bounding box
   * @param yPos: the y of the bounding box
   * @param xDim: the x of the bounding box dimensions
   * @param yDim: the y of the bounding box dimensions
   * @return true if the passed dimensions are not signficantly far away from the current
   * coordinates of the tower
   */
  bool withinBounds(float xPos, float yPos, float xDim, float yDim){
    float desiredXCor = xPos + xDim/2.0;
    float desiredYCor = yPos + yDim/2.0;
    if (x <= desiredXCor + e && x >= desiredXCor - e){
      if(y <= desiredYCor + e && y >= desiredYCor -e){
        return true;
      }
    }
    return false;
  }
};

#endif
