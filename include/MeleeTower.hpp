/*
  MeleeTower.hpp

  Purpose: A defensive tower unit that spawns actor units to fight enemy npc actors

  @author Andrew Katson
 */

 #ifndef MELEETOWER_H
 #define MELEETOWER_H
#include "TowerInterface.hpp"
#include "MeleeUnit.hpp"
#include <memory>
#include <vector>
#include <chrono>

using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;
class MeleeTower : public TowerInterface{
protected:
  //the total number of units that a melee tower can have
  int totalUnits;
  //the speed that dead units will respawn
  int respawnSpeed;
  //vecotr that holds the measured time since the death of each of the units
  //at the corresponding index in currentUnits (set to 0 when they are alive);
  vector<float> timeOfDeath;
  //the values used to determine if a float is equal
  float e;
  //the x coordinate of the rally point for this tower
  int xRally;
  //the y coordinate of the rally point for this tower
  int yRally;
  //the specific units that are fighitng for this tower
  vector<shared_ptr<MeleeUnit>> currentUnits;

public:
  MeleeTower(shared_ptr<EventManager> eventManager, shared_ptr<TextLoader> textLoader);
  void update(float delta);

  void initSprite();

  void registerDelegates();

  virtual void upgrade();
  virtual void setUpUnits();
  void resetRallyPoint(int x, int y);
  /*
   * @return the price of the tower
   */
  int getPrice();

  string getType(){return towerTypeID;}

  void setPos(intPair pos);
  void setPos(int row, int col);
  int getXCoordinate(){return xCoordinate;}
  int getYCoordinate(){return yCoordinate;}
  void setXCoordinate(int xCor){xCoordinate = xCor;}
  void setYCoordinate(int yCor){yCoordinate = yCor;}

  void setProjectile(){}

  void handleActorDestroyed(const EventInterface& event);

  void handleDeadUnit(int indexOfUnit);

  void respawnUnits();
  bool canAttack();
  void attack(shared_ptr<ActorInterface> enemyInRange);

  shared_ptr<vector<int>>  getStatistics();
};

 #endif
