/*
  MeleeTower.hpp

  Purpose: A defensive tower unit that spawns actor units to fight enemy npc actors

  @author Andrew Katson
 */

#pragma once

#include "TowerInterface.hpp"
#include "MeleeUnit.hpp"
#include "Events/ActorCreatedEvent.hpp"
#include <memory>
#include <vector>
#include <chrono>
#include <math.h>
#include <memory>
#include <iostream>
#include <time.h>


using std::cerr;
using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::seconds;
using std::chrono::nanoseconds;
using std::chrono::seconds;
class MeleeTower : public TowerInterface{
protected:
  //the total number of units that a melee tower can have
  int totalUnits;
  //the speed that dead units will respawn
  int respawnSpeed;
  //vecotr that holds the measured time since the death of each of the units
  //at the corresponding index in currentUnits (set to 0 when they are alive);
  vector<long long> timeOfDeath;
  //the values used to determine if a float is equal
  float e;
  //the x coordinate of the rally point for this tower
  float xRally;
  //the y coordinate of the rally point for this tower
  float yRally;
  //the specific units that are fighitng for this tower
  vector<shared_ptr<MeleeUnit>> currentUnits;

  bool isEnemyPointingAtUnit = true;
  //whether we want to log the units made for this tower in the collision system
  bool logUnitsForCollisions;

public:
  MeleeTower(shared_ptr<EventManager> eventManager, shared_ptr<TextLoader> textLoader);
  ~MeleeTower();
  void update(float delta);
  void resetUnitPosition(shared_ptr<MeleeUnit> unit, int unitIndex, float delta = 1.0);
  bool withinRange(float x1, float y1, float x2, float y2);
  void calcAttackVector(shared_ptr<ActorInterface> meleeUnit, shared_ptr<ActorInterface> enemyInRange);

  void initSprite();

  //start game clock
  sf::Clock gameClock;
  void registerDelegates();
  void deregisterDelegates();

  virtual void upgrade();
  virtual void setUpUnits();
  void setUpUnitCoordinates(float x, float y);
  void setUpUnitTileSize(float x, float y);
  void setUpUnitPositions(int row, int col);
  void resetRallyPoint(float x, float y);
  float getRallyX(){return xRally;}
  float getRallyY(){return yRally;}
  vector<shared_ptr<MeleeUnit>>& getUnits(){return currentUnits;}

  /*
   * @return the price of the tower
   */
  int getPrice();

  string getType(){return typeID;}

  void setPos(intPair pos);
  void setPos(int row, int col);
  float getXCoordinate(){return xCoordinate;}
  float getYCoordinate(){return yCoordinate;}
  void setXCoordinate(float xCor){xCoordinate = xCor;}
  void setYCoordinate(float yCor){yCoordinate = yCor;}

  void setProjectile(){}

  void handleActorDestroyed(const EventInterface& event);

  void handleDeadUnit(int indexOfUnit);

  void respawnUnits(float delta);
  bool canAttack();
  void attack(shared_ptr<ActorInterface> enemyInRange, float delta);

  shared_ptr<vector<int>>  getStatistics();

  void logUnitsForCollisionManager();
  void verifyUnitPositions(float tileXSize, float tileYSize);

  //getters used by the upgrading system
  int getRespawnSpeed(){return respawnSpeed;}
  int getRadius(){return radius;}
  int getUnitHitpoints(){return currentUnits.at(0)->getMaxHitpoints();}
  int getUnitDamage(){return currentUnits.at(0)->getDamage();}
  int getUnitArmorPenetration(){currentUnits.at(0)->getArmorPenetration();}
  int getUnitArmor(){currentUnits.at(0)->getArmor();}
  int getUnitAttackRate(){currentUnits.at(0)->getAttackRate();}


  //setters used by the upgrading system
  void updateRespawnSpeed(int newRespawnSpeed){respawnSpeed = newRespawnSpeed;}
  void updateRadius(int newRadius){radius = newRadius;}
  void updateUnitHitpoints(int newMaxHitpoints);
  void updateUnitDamage(int newDamage);
  void updateUnitArmorPenetration(int newArmorPenetration);
  void updateUnitArmor(int newArmor);
  void updateUnitAttackRate(int newAttackRate);

};
