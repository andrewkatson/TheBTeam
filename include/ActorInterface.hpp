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
#include<iostream>
#include <cmath>

using namespace std;
using std::shared_ptr;
using std::addressof;
using std::vector;
class ActorInterface{

protected:
  //A reference to the unit that this unit is fighting.
  shared_ptr<ActorInterface> engagedUnit;

  //the scale of the unit when being drawn
  float xUnitScale;
  float yUnitScale;

  //whether the unit should be drawn or not (1=true, 0=false)
  float drawUnit=1;

  //the x of the vector of movement
  float xVector;
  //the y of the vector of movement
  float yVector;
  //the x coordinate of the taget
  float xTarget;
  //the y coordinate of the target
  float yTarget;

  //The actor's direction in RADIANS.
  double direction;

  //event manager (used to register, deregister from events, and create them)
  shared_ptr<EventManager> eventManager;

  //Store the textLoader to make requests for strings and constants
  shared_ptr<TextLoader> textLoader;

  //The unique identifier for the actor.
  long long  id;

  //The sprite corresponding to the actor.
  sf::Sprite sprite;

  //all the textures for this actor
  shared_ptr<vector<sf::Texture>> textures;

  //The actor's movement speed in [units]. [pixels per millisecond? microsecond?]
  float speed;

  //The actor's hitpoints
  float hitpoints;

  //Used to reset the actor's hit points
  float maxHitpoints;

  //The actor's damage
  int damage;

  //The actor's armor
  int armor;

  //The actor's armor penetration
  int armorPenetration;

  //The actor's attack rate (not applicable to projectiles)
  int attackRate;

  //The rectangle corresponding to the object's dimensions.
  sf::FloatRect collisionBox;

  //The coordinates of the actor.
  float x,y;

  //Row and column of the actor on the world grid.
  int row,col;

  sf::Color color;

  sf::CircleShape radiusCircle;

  //the size of a tile in the x and the y
  float xTileSize;
  float yTileSize;

  //the scale from the tower associated with this (ONLY APPLICABLE IF PROJECITLE)
  float xTowerScale;
  float yTowerScale;

  //the degree of error
  const float e = 0.001;

  //the area of effect for a projectile and the area of attack for a unit
  int radius;


  static double xScale;
  static double yScale;

  //whether this is a projectile or not
  bool isProjectile;
  //whether this is an allied unit or not
  bool isAlly;

public:
  bool isActor = true;
  bool isTower = false;
  static double getXScale();
  static double getYScale();

  static void setXScale(int num_cols);
  static void setYScale(int num_rows);
  //the string identifier for the type of actor (specific to each type of actor)
  string typeID;
  ActorInterface();
  ~ActorInterface();

  /*
   * Rotate the texture by the number of degrees
   * @param degrees:
   */
  void rotate(float degrees);


  /*
   * Reset the hitpoints back to the max (for respawning allied units)
   */
  void resetHealth(){hitpoints = maxHitpoints;}

  /*
    Returns the unique identifier for the actor.

    @return an integer representing the actor's identity
   */
  long long getID(){
    //cout << "id = "<< id << endl;
    return id;}

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
  virtual void move(float delta)=0;

  /*
   * Return actor type ID
   */
  string getType(){return typeID;}

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

  void setSpeed(float speed){this->speed=speed;}

  float getHitpoints(){return this->hitpoints;}
  int getMaxHitpoints(){return this->maxHitpoints;}
  int getDamage(){return this->damage;}
  int getArmor(){cout << "armor was " << armor << endl; return this->armor;}
  int getArmorPenetration(){return this->armorPenetration;}
  int getRadius(){return radius;}
  int getAttackRate(){return attackRate;}

  void updateHitpoints(float newHitpoints){this->hitpoints = newHitpoints;}
  void updateMaxHitpoints(float newMaxHitpoints){maxHitpoints = newMaxHitpoints;}
  void updateDamage(int newDamage){damage = newDamage;}
  void updateArmor(int newArmor){cout << "are we setting the armor? " << endl; armor = newArmor;}
  void updateArmorPenetration(int newArmorPenetration){armorPenetration = newArmorPenetration;}
  void updateRadius(int newRadius){radius = newRadius;}
  void updateAttackRate(int newAttackRate){attackRate = newAttackRate;}

  sf::CircleShape& getRadiusCircle(){return radiusCircle;}

  double getDirection() const;

  void setDirection(double direction);



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


  void attack() {
    engagedUnit->updateHitpoints(damage);
    //TODO - handle attacking animation with userview, initiate attack.
  }


  void setTileSize(float x, float y){this->xTileSize=x; this->yTileSize=y;}

  bool isAProjectile(){return isProjectile;}

  bool isAnAlly(){return isAlly;}


  void setTowerScale(float x, float y){xTowerScale = x; yTowerScale = y;}
  float getXTowerScale(){return xTowerScale;}
  float getYTowerScale(){return yTowerScale;}

  /*
   * set the vector for movement (defined by an x and y)
   * @param x: the x component of the vector
   * @param y: the y component of the vectors
   */
  void setVector(float x, float y);

  /*
   * set the positions for the target of the projectile
   * @param xpos: the x coordiante of the target of the projectile
   * @param ypos: the y coordinate of the target of the projectile
   */
  void setTargetPos(float x, float y);

  /*
   * flicker the unit by setting its draw unit variable to 0
   */
  void flickerUnit(){drawUnit = 0.0;}
  /*
   * @return float: the value of draw unit
   */
  float canDraw(){return drawUnit;}
  /*
   * increment draw unit (acts as a timer while the unit flickers)
   */
  void incrementDrawUnit(){drawUnit+=0.1;if(drawUnit>1.0){drawUnit=1.0;}}

  shared_ptr<ActorInterface> getEngagedUnit(){return engagedUnit;}
  /*
   * Set the engaged unit
   */
  void setEngagedUnit(shared_ptr<ActorInterface> unitToEngage){engagedUnit = unitToEngage;}

  float getXTarget(){return xTarget;}

  float getYTarget(){return yTarget;}

  float getXVector(){return xVector;}
  float getYVector(){return yVector;}

  //set sprite scale
  void setScaleForSprite(float x, float y){sprite.setScale(x,y);}
  //set sprite position
  void setSpritePosition(float x, float y){sprite.setPosition(x,y);}
  //set the unit scale used
  void setUnitScale(float x, float y){xUnitScale=x; yUnitScale = y;}
  float getUnitXScale(){return xUnitScale;}
  float getUnitYScale(){return yUnitScale;}
};

#endif
