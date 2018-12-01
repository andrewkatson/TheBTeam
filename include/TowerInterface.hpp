
/*
  TowerInterface.hpp

  Purpose: A template to be implemented by the tower classes

  @author Andrew Katson
 */

#ifndef TOWERINTERFACE_H
#define TOWERINTERFACE_H
#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include <utility>
#include "TextLoader.hpp"
#include "TextureLoader.hpp"
#include "EventInterface.hpp"
#include "EventManager.hpp"
#include "ActorInterface.hpp"
#include "Events/ActorDestroyedEvent.hpp"
#include "Box2D/Box2D.h"

using std::string;
using std::make_shared;
using std::shared_ptr;
using std::pair;
class TowerInterface{
protected:
  //int pair (used to assocaite a row and col)
  typedef pair<int,int> intPair;
  //all the textures for this actor
  shared_ptr<vector<sf::Texture>> textures;
  //event manager (used to register, deregister from events, and create them)
  shared_ptr<EventManager> eventManager;
  //Store the textLoader to make requests for strings and constants
  shared_ptr<TextLoader> textLoader;
  //Store the textureLoader to get the textures for this tower and pass to
  //any dependent units or projectiles
  shared_ptr<TextureLoader> textureLoader;
  //The sprite corresponding to the tower.
  sf::Sprite sprite;
  //the tower type identifier that allows for its next upgrade to be pulled
  string towerTypeID;
  //the price of the tower (cost to remove in the case of an obstacle)
  int price;
  //the row in the grid this tower is located at
  int row;
  //the col in the grid this tower is located at
  int col;
  //the x coordinate on the map that the tower is located at (center of the tile on the grid it is at)
  float xCoordinate;
  //the y coordinate on the map that the tower is located at (center of the tile on the grid it is at)
  float yCoordinate;
  //the radius for the tower (if range then it is where it can fire, if melee it is where it can place a rally point)
  int radius;
  //the circle shape object to draw the radius, where collision detection happens
  sf::CircleShape radiusCircle;
  //whether the radius of shooting/spawning units is visible
  bool radiusVisible;
  //the degree of error
  const float e = 0.1;
  //Box2d World and Body
  shared_ptr<b2World> world;
  b2Body* body;

  //scale in the x direction applied to tower when drawing
  float xScale = 1.0;
  //scale in the y direction applied to tower when drawing
  float yScale = 1.0;

public:
  TowerInterface();
  ~TowerInterface();
  //boolean used to tell if this is a melee tower without casting
  bool isMelee;
  virtual void upgrade()=0;
  virtual int getPrice()=0;
  virtual string getType()=0;
  virtual void setProjectile()=0;
  virtual void setUpUnits()=0;
  virtual bool canAttack()=0;
  virtual void attack(shared_ptr<ActorInterface> enemyInRange)=0;
  virtual void setPos(int row, int col)=0;
  virtual void setPos(intPair pos)=0;
  virtual float getXCoordinate()=0;
  virtual float getYCoordinate()=0;
  virtual void setXCoordinate(float xCor)=0;
  virtual void setYCoordinate(float yCor)=0;
  virtual shared_ptr<vector<int>> getStatistics()=0;
  /*
   * update the position, check if it hit its target
   */
  virtual void update(float delta)=0;

  /*
    Returns the actor's sprite.

    @return the Sprite object that the interface contains.
   */
  sf::Sprite& getSprite(){return sprite;}//PEOPLE WHO KNOW MORE THAN ME: SHOULD THIS RETURN A REFERENCE?

  int getRadius(){return radius;}
  bool isRadiusVisible(){return radiusVisible;}
  void flipRadiusVisibility(){radiusVisible = radiusVisible==true ? false : true;}
  sf::CircleShape& getRadiusCircle(){return radiusCircle;}

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
    if (xCoordinate <= desiredXCor + e && xCoordinate >= desiredXCor - e){
      if(yCoordinate <= desiredYCor + e && yCoordinate >= desiredYCor -e){
        return true;
      }
    }
    return false;
  }

  /*
   * Set the center coordinates to the be equal to the middle of the object
   */
  void setToCenter(){

    sf::FloatRect boundsOfSprite = sprite.getGlobalBounds();
    /*
    sprite.setOrigin(boundsOfSprite.left + (boundsOfSprite.width)/2.0,
    boundsOfSprite.top + (boundsOfSprite.height)/2.0);
    */
  }

  void startContact(void* collidingWith){
    //collidingWith should be cast to a clas you can collide with ie Actors and Towers
  }

  void endContact(void* collidingWith){
    //look above
  }

  //gives actor access to the world to set physics body
  void setWorld(shared_ptr<b2World> world){
    this -> world = world;
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(xCoordinate,yCoordinate);
    bodyDef.angle = 0;
    body = world -> CreateBody(&bodyDef);

    //FIXTURES

  }

  void setXScale(float xScale){this->xScale = xScale;}
  void setYScale(float yScale){this->yScale = yScale;}
  float getXScale(){return xScale;}
  float getYScale(){return yScale;}

};

#endif
